// https://github.com/ThingPulse/esp8266-oled-ssd1306
//
#include <NTPClient.h>
#include "time.h"
#include <WiFiUdp.h>
#include "index.h"
#include <stdlib.h>
#include <WiFiManager.h>
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <SSD1306.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>

#define PIN D4
bool ledState = false;

// neopixel
#define NUM_LEDS 7
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(7, PIN, NEO_GRB + NEO_KHZ800);

// oled screen
SSD1306  display(0x3C, D2, D1, GEOMETRY_128_64);

// NTP / calendar / clock
void updateClock(int);
void updateTime();
int clockType = 2;
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = -18000;
const int   daylightOffset_sec = 3600;
bool bottomFullDate = true;
int lastDayUpdate = -1;
int currentSec, currentDay, currentMonth, currentYear;
String currentMonthName, currentDayName, currentDayAndMonth, currentDayAndMonthAndYear, currentTime, currentTimeNoSec;
String weekDays[7] = {"Dim", "Lun", "Mar", "Mer", "Jeu", "Ven", "Sam"};
String months[12] = {"Jan", "Fév", "Mar", "Avr", "Mai", "Juin", "Juil", "Août", "Sep", "Oct", "Nov", "Déc"};

WiFiManager wifiManager;

#include "httpServerConfig.h"

//The setup function is called once at startup of the sketch
void setup()
{
  Serial.begin(115200);
  while (!Serial) {
    yield();
  }
  Serial.println("Hello!");

  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, HIGH);
  ledState = true;

  // Oled display
  display.init();
  display.setFont(ArialMT_Plain_10);
  // display.invertDisplay();
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 0, "Hello Hello!");
  display.drawString(64, 12, "Connecting...");
  display.display();

  // Connect to WiFi
  wifiManager.setConnectTimeout(60);
  wifiManager.autoConnect("lamp");
  Serial.println("Connected!");

  ///////////////////////
  // NTP
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);


  display.clear();
  display.drawString(64, 0, "Connected!");
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, 10, "SSID: " + WiFi.SSID());
  display.drawString(0, 21, "IP: " + WiFi.localIP().toString());

  /*
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 45, ntpClient.getFormattedTime());
  display.display();
  */

  Serial.print("IP address:\t"); Serial.println(WiFi.localIP());

  // Start mDNS (to be reachable via "http://THING_NAME.local"
  if (!MDNS.begin(serverName)) {
    Serial.println("Error setting up MDNS responder!");
  } else {
    Serial.printf("mDNS responder started [%s.local]\n", serverName);
  }

  // Neopixel
  pixels.begin();

  pixels.setBrightness(32);
  for(int i = 0; i < 7; i++) {
    pixels.setPixelColor(0, 0, 0, 0);
    pixels.show();
    /*
    for(int j = 0; j < 256; j++) {
      pixels.setPixelColor(i, j, 0, 0);
      pixels.show();
      delay(3);
    }
    */
  }

  // Setup REST Web Server
  configureAndStartWebServer();
}

///////////////////////////////////////////////////////////
// LOOP
///////////////////////////////////////////////////////////
void loop()
{
  server.handleClient();
  MDNS.update();

  if(millis() % 1000 < 10) {
    // updateClock(48);
    updateClock(0);
  }
}

void updateTime() {
  time_t rawtime;
  struct tm *timeinfo;
  time (&rawtime);
  timeinfo = localtime (&rawtime);

  if (timeinfo) {
    currentDay = timeinfo->tm_mday;
    if (lastDayUpdate != currentDay) {
      lastDayUpdate = currentDay;

      currentMonth = timeinfo->tm_mon;
      currentYear = timeinfo->tm_year + 1900;
      currentDayName = weekDays[timeinfo->tm_wday];
      currentMonthName = months[currentMonth];
      currentDayAndMonth = currentDayName + " " + String(currentDay) + " " + currentMonthName;
      currentDayAndMonthAndYear = currentDayName + " " + String(currentDay) + " " + currentMonthName + " " + String(currentYear);

      if (bottomFullDate) {
        display.setColor(BLACK);
        display.fillRect(0, 47, 128, 18);
        display.setColor(WHITE);
        display.setTextAlignment(TEXT_ALIGN_CENTER);
        display.setFont(ArialMT_Plain_16);
        display.drawString(64, 47, currentDayAndMonthAndYear);
      }
    }

    char hours[3], mins[3], secs[3];
    sprintf(hours, "%02i", timeinfo->tm_hour);
    sprintf(mins, "%02i", timeinfo->tm_min);
    sprintf(secs, "%02i", timeinfo->tm_sec);

    currentTime = String(hours) + ":" + mins + ":" + secs;
    currentTimeNoSec = String(hours) + ":" + mins;
    currentSec = timeinfo->tm_sec;
  }
}

void updateClock(int y) {
  updateTime();

  display.setColor(BLACK);

  if (clockType == 0) {
    display.fillRect(0,y,128,18);
    display.setColor(WHITE);

    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, y + 4, currentDayAndMonth);

    display.setTextAlignment(TEXT_ALIGN_RIGHT);
    display.setFont(ArialMT_Plain_16);
    display.drawString(127, y, currentTime);

  } else if (clockType == 1) {
    display.fillRect(0, y, 128, 24);
    display.setColor(WHITE);
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(ArialMT_Plain_24);
    display.drawString(64, y, currentTime);
  } else if (clockType == 2) {
    display.fillRect(0, y - 2, 128, 46);
    display.setColor(WHITE);
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(Roboto_46);
    display.drawString(64, y, currentTimeNoSec);

    const char margin = 4;
    const char thickness = 3;
    const char newY = y + 44 + 0; // Y pour la barre de secondes

    if (currentSec == 0) {
      display.setColor(BLACK);
      display.fillRect(margin, newY, 60 * 2, thickness + 1);
      display.setColor(WHITE);
    }

    display.drawLine(margin + currentSec * 2, newY, margin + currentSec * 2, newY + thickness);
  }

  display.display();
}

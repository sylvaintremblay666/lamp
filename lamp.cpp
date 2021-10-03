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

const char *serverName = "lampserver";
const short serverPort = 80;

bool ledState = false;

// neopixel
#define NUM_LEDS 7
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(7, PIN, NEO_GRB + NEO_KHZ800);

//CRGB leds[NUM_LEDS];

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
// WiFiUDP ntpUDP;
// NTPClient ntpClient(ntpUDP, ntpServer, gmtOffset_sec);


WiFiManager wifiManager;
ESP8266WebServer server;


void handleRoot();
void handleNotFound();

void handleLedON();
void handleLedOFF();
void handleLedToggle();
void handleLedStatus();
void handleColorUpdate();

void send200(String);

String openHeadAndBody();
String closeBodyAndHtml();
String makeRedirectButton(String text, String url);

String getWiFiInfos();

void woohoo();
void woohoo2();

const String serverPageTitle = "Welcome to " + String(serverName) + "!";
const String tdStyle         = "style=\"border: 1px solid black;padding-right: 10px;padding-left: 10px\"";

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

  /*
  ntpClient.begin();
  ntpClient.update();
  */


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

  /*
  FastLED.addLeds<NEOPIXEL, D4>(leds, NUM_LEDS);
  FastLED.setBrightness(64);
  for(int i = 0; i <= 7; i++) {
    leds[i] = CRGB::Yellow;
    FastLED.show();
    delay(500);
    leds[i] = CRGB::Black;
    FastLED.show();
  };
  leds[0] = 0x00ff00;

  FastLED.show();
  */

  // Setup REST server
  server.on("/", HTTP_GET, handleRoot);

  server.on("/led", HTTP_GET, handleLedStatus);
  server.on("/led/on", HTTP_GET, handleLedON);
  server.on("/led/off", HTTP_GET, handleLedOFF);
  server.on("/led/toggle", HTTP_GET, handleLedToggle);
  server.on("/led/color", HTTP_GET, handleColorUpdate);

  server.onNotFound(handleNotFound);
  server.begin(serverPort);

}

///////////////////////////////////////////////////////////
// LOOP
///////////////////////////////////////////////////////////
void loop()
{
  // Serial.println("In loop! delay 2000...");
  // delay(2000);
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

void woohoo2() {
  uint32_t i = 0;
  /*
  leds[0].setRGB(0, 0, 0);
  leds[1].setRGB(0, 0, 0);
  leds[2].setRGB(0, 0, 0);
  leds[3].setRGB(0, 0, 0);
  leds[4].setRGB(0, 0, 0);
  leds[5].setRGB(0, 0, 0);
  leds[6].setRGB(0, 0, 0);
  FastLED.show();
*/
  for(i = 0; i < 255; i++){
    //leds[1].setColorCode(i);
    //leds[0].setRGB(i, 0, 0);
    delay(50);
    //FastLED.show();
  }

  /*
  for(; i < 256; i++){
      leds[2] = i;
      delay(100);
      FastLED.show();
    }
  for(; i >= 0; i--){
    leds[2] = i;
    delay(100);
    FastLED.show();
  }
  */
}

void woohoo() {
  for(int i = 0; i < 7; i++){
    for(int j = 0; j < 256; j++) {
      /*
      leds[i].setRGB(j, 0, 0);
      FastLED.show();*/
      delay(10);
    }
    /*
    for(int j = 255; j >= 0; j++) {
      leds[i].setRGB(j, 0, 0);
      FastLED.show();
      delay(10);
    }
    for(int j = 0; j < 256; j++) {
      leds[i].setRGB(0, j, 0);
      FastLED.show();
      delay(10);
    }
    for(int j = 255; j >= 0; j++) {
      leds[i].setRGB(0, j, 0);
      FastLED.show();
      delay(10);
    }
    for(int j = 0; j < 256; j++) {
      leds[i].setRGB(0, 0, j);
      FastLED.show();
      delay(10);
    }
    for(int j = 255; j >= 0; j++) {
      leds[i].setRGB(0, 0, j);
      FastLED.show();
      delay(10);
    }
    */
  }
}

void handleRoot() {
  String s = MAIN_page;
  s.replace("{{ServerName}}", serverName);
  s.replace("${this.ServerUrl}", WiFi.localIP().toString());

  // server.sendHeader("Access-Control-Allow-Origin", "*");
  // server.send(200, "text/html", s);
  send200(s);
	/*
	String content = openHeadAndBody();

    content += getWiFiInfos();

	// View config button
    // content += "<BR><a href=\"";
    // content += CONFIG_VIEW_URL;
	// content += "\"><button type=\"button\">View configuration</button></a>";

    content += closeBodyAndHtml();

	server.send(200, "text/html", content);
	*/
}

void handleLedON() {
  digitalWrite(BUILTIN_LED, LOW);
  ledState = true;
  send200("LedON Ok");
  // server.sendHeader("Access-Control-Allow-Origin", "*");
  // server.send(200, "text/plain", "LedON Ok");
}

void handleLedOFF() {
  digitalWrite(BUILTIN_LED, HIGH);
  ledState = false;
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "LedOFF Ok");
}

void handleLedToggle() {
  ledState ? digitalWrite(BUILTIN_LED, HIGH) : digitalWrite(BUILTIN_LED, LOW);
  ledState = !ledState;
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/plain", "LedToggle Ok");
}

void handleLedStatus() {
  String ledStatus = ledState ? "On" : "Off";
  ledStatus = String("{ \"ledState\": \"") + ledStatus + String("\" }");
  Serial.println("-> handleLedStatus - Response: " + ledStatus);
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "application/json", ledStatus);
}

void handleColorUpdate() {
  Serial.println("-> handleColorUpdate");
  //Serial.println("server.args: " + server.args());
  //String color = server.arg("color");
  uint8_t red = server.arg("red").toInt();
  uint8_t green = server.arg("green").toInt();
  uint8_t blue = server.arg("blue").toInt();
  Serial.printf("color: %i %i %i\n", red, green, blue);

  for(int i = 0; i < NUM_LEDS; i++) {
    pixels.setPixelColor(i, red, green, blue);
  }
  pixels.show();
  //if (color != "") {
  /*
    leds[0].setRGB(red, green, blue);

    leds[1].setRGB(red, green, blue);
    leds[2].setRGB(red, green, blue);
    leds[3].setRGB(red, green, blue);
*/
    // delay(50);
    // leds[2].setRGB(red, green, blue);
    /*
	leds[1].setRGB(255,0,0);
	leds[2].setRGB(0,255,0);
	leds[3].setRGB(0,0,255);
	*/
    //FastLED.show();
  //}
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(201, "text/plain", "Modified");
  //woohoo2();
}

void handleNotFound() {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(404, "text/plain", "404: Not found");
}

//////////////////////////////

void send200(String payload) {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "text/html", payload);
}
String openHeadAndBody() {
    String content = "";
	content += "<!DOCTYPE html><html>";
    content += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
    content += "<link rel=\"icon\" href=\"data:,\">";
    content += "<body>";
    content += "<h1>" + serverPageTitle + "</h1>";

    return content;
}

String closeBodyAndHtml() {
	return String("</body></html>");
}

String makeRedirectButton(String text, String url) {
	return String("<a href=\"" + url + "\"><button type=\"button\">" + text + "</button></a>");
}

String getWiFiInfos() {
	String content = "";

	content += "<H2>WiFi Connection</H2>";
	content +="<table>";
	content +="<tr>";
	content +="<td " + tdStyle + ">WiFi SSID</td>";
	content +="<td " + tdStyle + ">" + WiFi.SSID() + "</td>";
	content +="</tr>";
	content += "<td " + tdStyle + ">IP Address</td>";
	content +="<td "  + tdStyle + ">" + WiFi.localIP().toString() + "</td>";
	content +="</tr>";
	content +="</table>";

	return content;
}

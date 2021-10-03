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

// NTP / calendar / clock options
bool bottomFullDate = true;
int clockType = 2;
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = -18000;
const int   daylightOffset_sec = 3600;


WiFiManager wifiManager;

#include "httpServerConfig.h"
#include "clock.h"

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


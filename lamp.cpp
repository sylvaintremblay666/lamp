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



bool ledState = false;

#define PIN D4 // NeoPixels
#define NUM_LEDS 8
int currentBrightness = 50;
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

struct LampPixels {
  boolean on = true;
  uint8_t r = 0, g = 0, b = 0;
} lampPixels[NUM_LEDS];

SSD1306  display(0x3C, D2, D1, GEOMETRY_128_64); // OLED Screen
int clockPos = 0;

WiFiManager wifiManager;
const char *wifiAPname = "lamp";

String getBrightnessJson();
String getPixelsStatusJson();
void updatePixels();
void fadeInPixels(int r = 0, int g = 0, int b = 0, int loopDelay = 15, int interval = 1);
void fadeOutPixels(int r = 0, int g = 0, int b = 0, int loopDelay = 15, int interval = 1);

//----------------------------------
#include "clock.h"
#include "httpServerConfig.h"


//The setup function is called once at startup of the sketch
void setup()
{
  // Serial console
  Serial.begin(115200);
  while (!Serial) {
    yield();
  }
  Serial.println("Hello!");

  // Builtin LED
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, HIGH);
  ledState = false;

  // OLED display
  display.init();
  display.setFont(ArialMT_Plain_10);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 0, "Hello Hello!");
  display.drawString(64, 12, "Connecting...");
  display.display();

  // Connect to WiFi
  wifiManager.setConnectTimeout(60);
  wifiManager.autoConnect(wifiAPname);
  Serial.println("Connected!");
  Serial.print("IP address:\t"); Serial.println(WiFi.localIP());

  display.clear();
  display.drawString(64, 0, "Connected!");
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.drawString(0, 10, "SSID: " + WiFi.SSID());
  display.drawString(0, 21, "IP: " + WiFi.localIP().toString());

  // NTP
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  // Start mDNS (to be reachable via "http://THING_NAME.local"
  if (!MDNS.begin(serverName)) {
    Serial.println("Error setting up MDNS responder!");
  } else {
    Serial.printf("mDNS responder started [%s.local]\n", serverName);
  }

  // Neopixel
  pixels.begin();
  pixels.setBrightness(currentBrightness);
  for(int i = 0; i < NUM_LEDS; i++) {
    pixels.setPixelColor(i, 0, 0, 0);
    pixels.show();
  }

  // Little light show
  fadeInPixels(0, 1, 0, 10, 2);
  fadeOutPixels(0, 1, 0, 10, 2);

  // Setup REST Web Server
  configureAndStartWebServer();

  Serial.println(getClockTypesJson());
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
    updateClock(clockPos);
  }
}

String getBrightnessJson() {
  String json = "{ \"brightness\": " + String(currentBrightness) + " }";
  return json;
}

String getPixelsStatusJson() {
  String json = "{ \"pixels\":";
  json += "[";

  for (int i = 0; i < NUM_LEDS; i++) {
    json += "{";
    json += "\"on\":";
    json += lampPixels[i].on ? "true" : "false";
    json += ",";
    json += "\"r\":" + String(lampPixels[i].r) + ",";
    json += "\"g\":" + String(lampPixels[i].g) + ",";
    json += "\"b\":" + String(lampPixels[i].b);
    json += "}";
    json += i == NUM_LEDS - 1 ? "" : ",";
  }
  json += "]}";

  return json;
}

void updatePixels() {
  for(int i = 0; i < NUM_LEDS; i++) {
    if (lampPixels[i].on) {
      pixels.setPixelColor(i, lampPixels[i].r, lampPixels[i].g, lampPixels[i].b);
    } else {
      pixels.setPixelColor(i, 0, 0, 0);
    }
  }
  pixels.show();
}

void fadeInPixels(int r, int g, int b, int loopDelay, int interval) {
  for (int i = 0; i < 256; i += interval) {
    for (int j = 0; j < 8; j++) {
      lampPixels[j].r = r * i;
      lampPixels[j].g = g * i;
      lampPixels[j].b = b * i;
    }
    updatePixels();
    delay(loopDelay);
  }
}

void fadeOutPixels(int r, int g, int b, int loopDelay, int interval) {
  for (int i = 255; i >= 0; i -= interval) {
    for (int j = 0; j < 8; j++) {
      lampPixels[j].r = r * i;
      lampPixels[j].g = g * i;
      lampPixels[j].b = b * i;
    }
    updatePixels();
    delay(loopDelay);
  }
  for (int j = 0; j < 8; j++) {
    lampPixels[j].on = false;
  }
  updatePixels();
}

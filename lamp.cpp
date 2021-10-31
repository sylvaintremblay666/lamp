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
#include <SparkFun_APDS9960.h>
#include <Adafruit_NeoPixel.h>


// Rotary encoder
#define CLK D6
#define DT D7
#define SW D5

int counter = 0;
int currentStateCLK;
int lastStateCLK;
String currentDir ="";
unsigned long lastButtonPress = 0;

// Gesture sensor
#define APDS9960_SDA    D2
#define APDS9960_SCL    D1
// const byte APDS9960_INT  = D6;
SparkFun_APDS9960 apds = SparkFun_APDS9960();
volatile bool isr_flag = 0;
void ICACHE_RAM_ATTR interruptRoutine ();
void handleGesture();

// reset button
int prevButtonVal = 0;

bool ledState = false;
uint16_t lastSecUpdate = 0;

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

  // Rotary encoder
  pinMode(CLK,INPUT);
  pinMode(DT,INPUT);
  pinMode(SW, INPUT_PULLUP);

  // Read the initial state of CLK
  lastStateCLK = digitalRead(CLK);

  // Gesture sensor
  //Start I2C with pins defined above
  Wire.begin(APDS9960_SDA,APDS9960_SCL);

  // Set interrupt pin as input
  // pinMode(APDS9960_INT, INPUT);
  // pinMode(digitalPinToInterrupt(APDS9960_INT), INPUT);

  // Initialize Serial port
  Serial.begin(115200);
  // Serial.println(F("--------------------------------"));

  // Initialize interrupt service routine
  // attachInterrupt(digitalPinToInterrupt(APDS9960_INT), interruptRoutine, FALLING);

  // Initialize APDS-9960 (configure I2C and initial values)
  if ( apds.init() ) {
   Serial.println(F("APDS-9960 initialization complete"));
  } else {
   Serial.println(F("Something went wrong during APDS-9960 init!"));
  }

  // Start running the APDS-9960 gesture sensor engine
  if ( apds.enableGestureSensor(true) ) {
   Serial.println(F("Gesture sensor is now running"));
  } else {
   Serial.println(F("Something went wrong during gesture sensor init!"));
  }

  // Initialize interrupt service routine
  // attachInterrupt(digitalPinToInterrupt(APDS9960_INT), interruptRoutine, FALLING);

  // reset button
  pinMode(D0, INPUT_PULLDOWN_16);
  prevButtonVal = digitalRead(D0);

  // Builtin LED
  digitalWrite(BUILTIN_LED, HIGH);
  ledState = false;
}

///////////////////////////////////////////////////////////
// LOOP
///////////////////////////////////////////////////////////
void loop()
{
  server.handleClient();
  MDNS.update();

  uint16_t curSecs = millis() / 1000;
  if (curSecs != lastSecUpdate) {
    lastSecUpdate = curSecs;
    updateClock(clockPos);
  }

  int buttonVal = digitalRead(D0);
  if (prevButtonVal != buttonVal) {
    Serial.println("Button val changed!");
    Serial.println(buttonVal);
    prevButtonVal = buttonVal;
  }

  // Read the current state of CLK
  currentStateCLK = digitalRead(CLK);

  // If last and current state of CLK are different, then pulse occurred
  // React to only 1 state change to avoid double count
  if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){

      // If the DT state is different than the CLK state then
      // the encoder is rotating CCW so decrement
      if (digitalRead(DT) != currentStateCLK) {
          counter --;
          currentDir ="CCW";
      } else {
          // Encoder is rotating CW so increment
          counter ++;
          currentDir ="CW";
      }

      Serial.print("Direction: ");
      Serial.print(currentDir);
      Serial.print(" | Counter: ");
      Serial.println(counter);
  }

  // Remember last CLK state
  lastStateCLK = currentStateCLK;

  // Read the button state
  int btnState = digitalRead(SW);


  //If we detect LOW signal, button is pressed
  if (btnState == LOW) {
      //if 50ms have passed since last LOW pulse, it means that the
      //button has been pressed, released and pressed again
      if (millis() - lastButtonPress > 50) {
          Serial.println("Button pressed!");
      }

      // Remember last button press event
      lastButtonPress = millis();
  }


  /*
  if(millis() % 1000 < 10) {
    // updateClock(48);
    updateClock(clockPos);
  }*/

  /*
  if( isr_flag == 1 ) {
    detachInterrupt(digitalPinToInterrupt(APDS9960_INT));
    handleGesture();
    isr_flag = 0;
    attachInterrupt(digitalPinToInterrupt(APDS9960_INT), interruptRoutine, FALLING);
  }
  */
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

void interruptRoutine() {
  // Serial.println("Interrupt!");
  isr_flag = 1;
}

void handleGesture() {
    Serial.println("handleGesture!");
    if ( apds.isGestureAvailable() ) {
      Serial.println("available!");
    switch ( apds.readGesture() ) {
      case DIR_UP:
        Serial.println("UP");
        break;
      case DIR_DOWN:
        Serial.println("DOWN");
        break;
      case DIR_LEFT:
        Serial.println("LEFT");
        break;
      case DIR_RIGHT:
        Serial.println("RIGHT");
        break;
      case DIR_NEAR:
        Serial.println("NEAR");
        break;
      case DIR_FAR:
        Serial.println("FAR");
        break;
      default:
        Serial.println("NONE");
    }
  } else {
    Serial.println('NotAvail');
  }
  Serial.println("handleGesture end");
}

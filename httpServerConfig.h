
#ifndef HTTP_SERVER_CONFIG_H_
#define HTTP_SERVER_CONFIG_H_

#include "Arduino.h"

void configureAndStartWebServer();

void handleRoot();
void handleNotFound();

void handleLedON();
void handleLedOFF();
void handleLedToggle();
void handleLedStatus();

void handleColorUpdate();
void handleSetBrightness();
void handleGetBrightness();
void handleSetPixel();

void handleGetPixelsStatus();
void handleGetClockTypes();
void handleSelectClock();

void send200(String);
void send200Json(String payload);

String getWiFiInfos();

void woohoo();
void woohoo2();

String openHeadAndBody();
String closeBodyAndHtml();
String makeRedirectButton(String text, String url);


const char *serverName = "lampserver";
const short serverPort = 80;

const String serverPageTitle = "Welcome to " + String(serverName) + "!";
const String tdStyle         = "style=\"border: 1px solid black;padding-right: 10px;padding-left: 10px\"";

ESP8266WebServer server;

void configureAndStartWebServer() {
  server.on("/", HTTP_GET, handleRoot);

  server.on("/led", HTTP_GET, handleLedStatus);
  server.on("/led/on", HTTP_GET, handleLedON);
  server.on("/led/off", HTTP_GET, handleLedOFF);
  server.on("/led/toggle", HTTP_GET, handleLedToggle);
  server.on("/led/color", HTTP_GET, handleColorUpdate);

  server.on("/lamp/brightness/set", HTTP_GET, handleSetBrightness);
  server.on("/lamp/brightness", HTTP_GET, handleGetBrightness);
  server.on("/pixels/status", HTTP_GET, handleGetPixelsStatus);
  server.on("/pixel/set", HTTP_GET, handleSetPixel);

  server.on("/clocks", HTTP_GET, handleGetClockTypes);
  server.on("/clock/select", HTTP_GET, handleSelectClock);

  server.onNotFound(handleNotFound);
  server.begin(serverPort);
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
    //pixels.setPixelColor(i, red, green, blue);
    lampPixels[i].on = true;
    lampPixels[i].r = red;
    lampPixels[i].g = green;
    lampPixels[i].b = blue;
  }
  updatePixels();
  //pixels.show();
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(201, "text/plain", "Modified");
}

void handleSetPixel() {
  Serial.println("-> handleSetPixel");
  //Serial.println("server.args: " + server.args());
  //String color = server.arg("color");
  uint8_t pixelId = server.arg("pixelId").toInt();
  uint8_t r = server.arg("r").toInt();
  uint8_t g = server.arg("g").toInt();
  uint8_t b = server.arg("b").toInt();
  Serial.println(server.arg("on"));
  boolean on = server.arg("on") == "true";
  Serial.printf("setPixel: %i %i %i %i\n", pixelId, r, g, b, on);

  lampPixels[pixelId].on = on;
  if (on) {
    lampPixels[pixelId].r = r;
    lampPixels[pixelId].g = g;
    lampPixels[pixelId].b = b;
  } else {
    lampPixels[pixelId].r = 0;
    lampPixels[pixelId].g = 0;
    lampPixels[pixelId].b = 0;
  }
  updatePixels();

  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(201, "text/plain", "Modified");
}

void handleGetPixelsStatus() {
  send200Json(getPixelsStatusJson());
}

void handleGetClockTypes() {
  send200Json(getClockTypesJson());
}

void handleSelectClock() {
  Serial.println("-> handleSelectClock");
  int clockTypeArg = server.arg("clockId").toInt();
  currentClockType = (ClockType) clockTypeArg;
  display.clear();
  lastDayUpdate = 0;
  updateClock(clockPos);
  send200("Ok");
}

void handleSetBrightness() {
  Serial.println("-> handleSetBrightness");
  int newBrightnessValue = server.arg("value").toInt();
  newBrightnessValue = newBrightnessValue > 150 ? 150 : newBrightnessValue;
  pixels.setBrightness(newBrightnessValue);
  pixels.show();
  send200("Ok");
}

void handleGetBrightness() {
  send200Json(getBrightnessJson());
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

void send200Json(String payload) {
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "application/json", payload);
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


#endif // HTTP_SERVER_CONFIG_CPP_

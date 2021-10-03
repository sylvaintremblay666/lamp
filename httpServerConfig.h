
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

void send200(String);

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

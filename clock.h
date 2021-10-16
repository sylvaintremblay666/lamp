/*
 * clock.h
 *
 *  Created on: Oct 3, 2021
 *      Author: stremblay
 */

#ifndef CLOCK_H_
#define CLOCK_H_

#include "Arduino.h"

enum ClockType {
  dateAndTime_18,
  timeCentered_24,
  bigDigital_46,
};

bool bigDigital_bottomFullDate = true;
ClockType currentClockType = bigDigital_46;
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = -18000;
const int   daylightOffset_sec = 3600;

void updateClock(int);
void updateTime();
String getClockTypesJson();

int lastDayUpdate = -1;
int currentSec, currentDay, currentMonth, currentYear;
String currentMonthName, currentDayName, currentDayAndMonth, currentDayAndMonthAndYear, currentTime, currentTimeNoSec;
String weekDays[7] = {"Dim", "Lun", "Mar", "Mer", "Jeu", "Ven", "Sam"};
String months[12] = {"Jan", "Fév", "Mar", "Avr", "Mai", "Juin", "Juil", "Août", "Sep", "Oct", "Nov", "Déc"};

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

      if (currentClockType == bigDigital_46 && bigDigital_bottomFullDate) {
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

  if (currentClockType == dateAndTime_18) {
    display.fillRect(0,y,128,18);
    display.setColor(WHITE);

    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);
    display.drawString(0, y + 4, currentDayAndMonth);

    display.setTextAlignment(TEXT_ALIGN_RIGHT);
    display.setFont(ArialMT_Plain_16);
    display.drawString(127, y, currentTime);

  } else if (currentClockType == timeCentered_24) {
    display.fillRect(0, y, 128, 24);
    display.setColor(WHITE);
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.setFont(ArialMT_Plain_24);
    display.drawString(64, y, currentTime);

  } else if (currentClockType == bigDigital_46) {
    display.fillRect(0, y - 3, 128, 46);
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

String getClockTypesJson() {
  String json = "{ \"clockTypes\": [";
  json += "\"Small DateTimeSec [18px]\",";
  json += "\"Medium TimeSec [24px]\",";
  json += "\"Fullscreen TimeSecDate[46px]\"";
  json += "],";
  json += "\"selectedClock\": " + String(int(currentClockType));
  json += "}";

  return json;
}
#endif /* CLOCK_H_ */

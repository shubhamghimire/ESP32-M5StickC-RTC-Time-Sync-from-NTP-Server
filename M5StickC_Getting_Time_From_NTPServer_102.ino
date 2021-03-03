#include "WiFi.h"
#include <M5StickC.h>
#include "time.h"

// Network Credentials
const char* ssid = "tkwtic24";
const char* password =  "20191002";

// NTP Server credentials
const char* ntpServer = "ntp.jst.mfeed.ad.jp";
const long  gmtOffset_sec = 9 * 3600;           // Japan's time is GMT +9
const int daylightOffset_sec = 0;

struct tm timeinfo;

void printLocalTime(){
  
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo,"%Y/%m/%d %a %H:%M:%S");
}

void printM5Lcd(){
  M5.Axp.ScreenBreath(9);
  M5.Lcd.setRotation(3);
  M5.Lcd.setCursor(15, 10);
  M5.Lcd.setTextColor(RED, BLACK);
  M5.Lcd.setTextSize(2);
  M5.Lcd.println(&timeinfo,"%Y/%m/%d \n");
  M5.Lcd.setTextColor(GREEN, BLACK);
  M5.Lcd.setTextSize(3);
  M5.Lcd.println(&timeinfo,"%H:%M:%S");
}

void setup(){
  Serial.begin(115200);
  M5.begin();
  
  //connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" CONNECTED");

  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void loop(){
  delay(1000);
  printLocalTime();
  printM5Lcd();
}

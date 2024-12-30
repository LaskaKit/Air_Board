/*
* Example code for AirBoard and SDS011
* The measuread values (PM10) are send to 
* Serial Monitor and to TMEP.cz or TMEP.eu
* This example creates SoftwareSerial where is SDS011 connected
* IO5 - RX connect to TX of SDS011
* IO4 - TX connect to RX of SDS011
*
* Libraries:
* Library for SoftwareSerial
* https://github.com/plerup/espsoftwareserial
* Library for SDS011
* https://github.com/lewapek/sds-dust-sensors-arduino-library/
*
* Hardware:
* SDS011 - https://www.laskakit.cz/nova-pm-sds011-opticky-senzor-kvality-ovzdusi-pm2-5-pm10/
* Air board - https://www.laskakit.cz/laskakit-airboard-8266-deska-pro-mereni-kvality-vzduchu/
* Cable for SDS011 and Air board - https://www.laskakit.cz/laskakit-airboard-propojovaci-kabel-pro-nova-pm-sds011-opticky-senzor-kvality-ovzdusi/
*
* laskakit 2024
*/

#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include "SdsDustSensor.h"

SoftwareSerial SDS_Serial(5, 4); // RX | TX
SdsDustSensor sds(SDS_Serial);

unsigned int waitTime = 60000; // in ms

/* -------------- Wi-Fi --------------- */
const char* ssid     = "SSID";
const char* password = "PASSWORD";
const char* host = "HOSTNAME.tmep.cz"; // or HOSTNAME.tmep.eu

void setup() 
{
  Serial.begin(115200); // Serial for output to the Arduino Serial Monitor
  
  /* -------------- SDS011 --------------- */
  sds.begin();  // SDS011 Serial begin (replaced by SoftwareSerial)
  /* -------------- END SDS011 ---------------- */

  /* -------------- Wi-Fi --------------- */
  WiFi.begin(ssid, password);
  unsigned int numberOfConnections= 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    numberOfConnections++;

    Serial.println("Number Of Connections:");
    Serial.println(numberOfConnections);

    // if ESP8266 can't connect to WiFi -> go to deep.sleep
    if (numberOfConnections > 10)
    {
        //if you want to use deep sleep, connect RST with GPIO16 (16) on header
        //ESP.deepSleep(waitTime/1000 * 1000000, WAKE_RF_DEFAULT);
        delay(waitTime);
        return;
    }
  }
  /* -------------- END Wi-Fi ---------------- */

}

void loop() 
{
  /* -------------- SDS011 --------------- */
  PmResult pm = sds.queryPm();  // read the values
  if (pm.isOk()) // check if the measurement is valid and print to Serial Monitor
  {
    Serial.print("PM2.5 = ");
    Serial.print(pm.pm25);
    Serial.print(", PM10 = ");
    Serial.println(pm.pm10);

    /* -------------- Wi-Fi --------------- */
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) 
    {
      Serial.println("connection failed");
      return;
    }
  
    // We now create a URI for the request
    String url = "/index.php?";
  
    Serial.print("Requesting URL: ");
    Serial.println(url);
  
    // This will send the request to the server, the GUID is "pm"
    client.print(String("GET ") + url + "pm=" + String(pm.pm10) + " HTTP/1.1\r\n" +
              "Host: " + host + "\r\n" + 
              "Connection: close\r\n\r\n");
  
    delay(10);
  
    while(client.available())
    {
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
    /* -------------- END Wi-Fi ---------------- */
    
  } 
  else 
  {
    Serial.print("Could not read values from sensor, reason: ");
    Serial.println(pm.statusToString());
  }
  /* -------------- END SDS011 ---------------- */
  
  //if you want to use deep sleep, connect RST with GPIO16 (16) on header
  //ESP.deepSleep(waitTime/10000 * 1000000, WAKE_RF_DEFAULT);
  delay(waitTime);

}

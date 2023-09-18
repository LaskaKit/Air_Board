/*
* Example code for AirBoard and SDS011
* The measuread values are send to 
* Serial Monitor.
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
* laskakit 2023
*/
#include <SoftwareSerial.h>
#include "SdsDustSensor.h"

SoftwareSerial SDS_Serial(5, 4); // RX | TX
SdsDustSensor sds(SDS_Serial);

void setup() 
{
  Serial.begin(115200); // Serial for output to the Arduino Serial Monitor
  sds.begin();  // SDS011 Serial begin (replaced by SoftwareSerial)

}

void loop() 
{
  PmResult pm = sds.queryPm();  // read the values
  if (pm.isOk()) // check if the measurement is valid and print to Serial Monitor
  {
    Serial.print("PM2.5 = ");
    Serial.print(pm.pm25);
    Serial.print(", PM10 = ");
    Serial.println(pm.pm10);
  } 
  else 
  {
    Serial.print("Could not read values from sensor, reason: ");
    Serial.println(pm.statusToString());
  }

  delay(10000);

}

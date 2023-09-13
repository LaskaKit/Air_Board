/*
* Example code for AirBoard and SEN5x
* The measuread values are send to 
* Serial Monitor and to TMEP.cz (TMEP.eu)
* If you want to use deep sleep function, short the RST with IO16 (16) on header of AirBoard.
*
* Libraries:
* https://github.com/Sensirion/arduino-i2c-sen5x
*
* laskakit 2023
*/

#include <ESP8266WiFi.h>
#include <SensirionI2CSen5x.h>
#include <Wire.h>

unsigned int waitTime = 60000;

/* -------------- SEN5x --------------- */
SensirionI2CSen5x sen5x;

uint16_t error;
char errorMessage[256];

/* -------------- Wi-Fi --------------- */
const char* ssid     = "SSID";
const char* password = "PASSWORD";
const char* host = "HOSTNAME.tmep.cz"; // or HOSTNAME.tmep.eu


void setup() 
{
  Serial.begin(115200);
  Wire.begin(0, 2);

  /* -------------- SEN5x --------------- */
  sen5x.begin(Wire);
  float tempOffset = 0.0;
  error = sen5x.setTemperatureOffsetSimple(tempOffset);
  if (error)
  {
    Serial.print("Error trying to execute setTemperatureOffsetSimple(): ");
    errorToString(error, errorMessage, 256);
    Serial.println(errorMessage);
  } 
  else 
  {
    Serial.print("Temperature Offset set to ");
    Serial.print(tempOffset);
    Serial.println(" deg. Celsius (SEN54/SEN55 only)");
  }

  // Start Measurement
  error = sen5x.startMeasurement();
  if (error) 
  {
    Serial.print("Error trying to execute startMeasurement(): ");
    errorToString(error, errorMessage, 256);
    Serial.println(errorMessage);
  }
  /* -------------- END SEN5x ---------------- */

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
        //ESP.deepSleep(waitTime * 1000000, WAKE_RF_DEFAULT);
        delay(waitTime);
        return;
    }
  }
}

void loop() 
{
  /* -------------- SEN5x --------------- */
  // Read Measurement
  float massConcentrationPm1p0;
  float massConcentrationPm2p5;
  float massConcentrationPm4p0;
  float massConcentrationPm10p0;
  float ambientHumidity;
  float ambientTemperature;
  float vocIndex;
  float noxIndex;

  error = sen5x.readMeasuredValues(
        massConcentrationPm1p0, massConcentrationPm2p5, massConcentrationPm4p0,
        massConcentrationPm10p0, ambientHumidity, ambientTemperature, vocIndex,
        noxIndex);

  if (error) 
  {
    Serial.print("Error trying to execute readMeasuredValues(): ");
    errorToString(error, errorMessage, 256);
    Serial.println(errorMessage);
  } 
  
  else 
  {
    Serial.print("MassConcentrationPm1p0:");
    Serial.print(massConcentrationPm1p0);
    Serial.print("\t");
    Serial.print("MassConcentrationPm2p5:");
    Serial.print(massConcentrationPm2p5);
    Serial.print("\t");
    Serial.print("MassConcentrationPm4p0:");
    Serial.print(massConcentrationPm4p0);
    Serial.print("\t");
    Serial.print("MassConcentrationPm10p0:");
    Serial.print(massConcentrationPm10p0);
    Serial.print("\t");
    Serial.print("AmbientHumidity:");
    if (isnan(ambientHumidity)) 
    {
      Serial.print("n/a");
    } 
    else 
    {
      Serial.print(ambientHumidity);
    }
    Serial.print("\t");
    Serial.print("AmbientTemperature:");
    if (isnan(ambientTemperature)) 
    {
      Serial.print("n/a");
    } 
    else 
    {
      Serial.print(ambientTemperature);
    }
    Serial.print("\t");
    Serial.print("VocIndex:");
    if (isnan(vocIndex)) 
    {
      Serial.print("n/a");
    } 
    else 
    {
      Serial.print(vocIndex);
    }
    Serial.print("\t");
    Serial.print("NoxIndex:");
    if (isnan(noxIndex)) 
    {
      Serial.println("n/a");
    } 
    else 
    {
      Serial.println(noxIndex);
    }
  }
  /* -------------- END SEN5x ---------------- */

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
  client.print(String("GET ") + url + "pm=" + String(massConcentrationPm2p5) + " HTTP/1.1\r\n" +
            "Host: " + host + "\r\n" + 
            "Connection: close\r\n\r\n");

  delay(10);

  while(client.available())
  {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  //if you want to use deep sleep, connect RST with GPIO16 (16) on header
  //ESP.deepSleep(waitTime * 1000000, WAKE_RF_DEFAULT);
  delay(waitTime);
}

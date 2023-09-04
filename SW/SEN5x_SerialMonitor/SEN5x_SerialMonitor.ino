/*
* Example code for AirBoard and SEN5x
* The measuread values are send to 
* Serial Monitor.
*
* Libraries:
* https://github.com/Sensirion/arduino-i2c-sen5x
*
* laskakit 2023
*/

#include <SensirionI2CSen5x.h>
#include <Wire.h>

SensirionI2CSen5x sen5x;

uint16_t error;
char errorMessage[256];

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

  delay(10000);

}

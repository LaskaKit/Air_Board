/*
* Example code for AirBoard with deepsleep
* In Arduino choose ESPino board
*
* Email:podpora@laskakit.cz
* Web:laskakit.cz
*/

#define BOOST_EN_PIN 12 
 
void setup() {
  Serial.begin(115200);

  // Turn on boost
  // To use this future need to cut jumper "BOOST_5V" on the back side board first and then solder right side of the jumper
  pinMode(BOOST_EN_PIN, OUTPUT);
  digitalWrite(BOOST_EN_PIN, HIGH);
  delay(3000);
  // Wait for serial to initialize.
  while(!Serial) { }
  
  // Deep sleep mode for 30 seconds, the ESP8266 wakes up by itself when GPIO 16 is connected to the RESET pin
  Serial.println("I'm awake, but I'm going into deep sleep mode for 5 seconds");
  // Turn off boost
  digitalWrite(BOOST_EN_PIN, LOW);
  ESP.deepSleep(30e6); 
}

void loop() {
}
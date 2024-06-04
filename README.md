![Airboard - TOP](https://github.com/LaskaKit/Air_Board/blob/main/img/LaskaKit-airboard-8266-2.jpg)

# LaskaKit AirBoard ESP8266 

The quality of the air we breathe is very important but unfortunately neglected. Thanks to a close cooperation with [sensorvzduchu.cz](https://www.senzorvzduchu.cz/) we have developed a board fully compatible with https://sensor.community/. This is one of the largest services for storing and visualizing data from home and semi-professional metestanice. 

Of course, it is not necessary to use Airboard only with sensor.community. You can use it with another popular service [TMEP.eu](https://tmep.eu/). Or you can send the data to your own server, where you can run HomeAssistant or Grafana. 

We have fully respected the demands and requirements of the sensor.community during development so that the LaskaKit AirBoard is fully compatible. No obstacles, just improvements over the normal NodeMCU wiring. </br>
And the result? The basis is a fully supported module with ESP8266. To this you can easily connect I2C sensors (SDA - GPIO0, SCL - GPIO2) via two [uSup connectors(what is it?)](https://blog.laskakit.cz/predstavujeme-univerzalni-konektor-pro-propojeni-modulu-a-cidel-%ce%bcsup/). With this connector compatible with SparkFun Qwiic and Adafruit STEMMA, you can connect dozens of different I2C sensors. </br>
Which on? For example [BME688 - Pressure, Temperature, Humidity and Air Quality Sensor](https://www.laskakit.cz/laskakit-bme688-senzor-tlaku--teploty--vlhkosti-a-kvalitu-vzduchu/), [SGP41 - VOC and Nox Air Quality Sensor](https://www.laskakit.cz/laskakit-sgp41-voc-a-nox-senzor-kvality-ovzdusi/) and you can display all that data on the [1.3" OLED display](https://www.laskakit.cz/laskakit-oled-displej-128x64-1-3--i2c/?variantId=11903), [SCD41 for measurement of CO2, temperature and humidity](https://www.laskakit.cz/laskakit-scd41-senzor-co2--teploty-a-vlhkosti-vzduchu/), sensor SHT41 [temperature and humidity](https://www.laskakit.cz/laskakit-sht40-senzor-teploty-a-vlhkosti-vzduchu/) and [sensor of pressure, temperature, humidity BME280](https://www.laskakit.cz/arduino-senzor-tlaku--teploty-a-vlhkosti-bme280/), [RTC - Real Time Clock](https://www.laskakit.cz/laskakit-ds3231-orig--rtc-hodiny-realneho-casu/) with DS323.

The UART is connected to RX (GPIO5), TX (GPIO4) pins, the ADC input from the voltage divider connected to the battery is connected to the single ADC input of the ESP8266.
And that's certainly not all.

![Airboard - pinout](https://github.com/LaskaKit/Air_Board/blob/main/img/Airboard_pinout.jpg)

You can also connect particulate sensors to the AirBoard very easily - there is a 7-pin connector on the board with I2C interface and UART interface and of course power supply. </br>
How and what to connect where we wrote in https://github.com/LaskaKit/Air_Board/blob/main/input/sensors.xlsx</br>
Some sensors need a 5V power supply, usually because of the fan or laser. We also kept this in mind during the design - we added a step-up converter to the board. With this you can power sensors that also need 5V power.

Fro version 1.2, it is now possible to choose whether the 5V output voltage for the connected sensors will be permanently on, or whether it can be switched on/off as needed using GPIO pin IO12.

If you're asking if you can connect a 5V powered sensor to the ESP8266, overwhelmingly yes. The sensors are indeed 5V powered, but the output is 3.3V compatible (but always confirm this in the sensor datasheet).

And what else can you find on the board? Three-pin connector for high-quality connection of temperature sensor DS18B20 (1-wire bus, contains 4k7 pull-up), connector for solar panel (we recommend 6V) and connector for connecting the accumulator.

You don't need a programmer. It is built-in on the board itself. Just plug in the USB-C cable to your laptop and upload your code. 

## This board is available on https://www.laskakit.cz/laskakit-airboard-8266-deska-pro-mereni-kvality-vzduchu/

![Airboard - TOP](https://github.com/LaskaKit/Air_Board/blob/main/img/LaskaKit-airboard-8266-3.jpg)

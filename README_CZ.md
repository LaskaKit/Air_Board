![Airboard - TOP](https://github.com/LaskaKit/Air_Board/blob/main/img/Air_Board_1.jpg)

# LaskaKit AirBoard ESP8266 
Kvalita vzduchu, který dýcháme, je velmi důležitá ale bohužel opomíjená. Díky úzké spolupráci se [senzorvzduchu.cz](https://www.senzorvzduchu.cz/) jsme společně vyvinuli desku plně kompatibilní se https://sensor.community/cz/. To je jedna z největších služeb pro ukládání a vizualizaci dat z domácích a poloprofesionálních metestanice. 

Airboard samozřejmě nemusíš použít jenom se sensor.community. Můžeš jej využít s další populární službou [TMEP.cz](https://tmep.cz/). Nebo si můžeš posílat data na svůj server, kde ti třeba běží HomeAssistant nebo Grafana. 

Plně jsme při vývoji respektovali nároky a požadavky sensor.community tak, aby deska LaskaKit AirBoard byla plně kompatibilní. Žádné překážky, jenom vylepšení oproti běžnému zapojení s NodeMCU. </br>
A výsledek? Základem je plně podporovaný modul s ESP8266. K tomu lze snadno připojit I2C čidla (SDA - GPIO0, SCL - GPIO2) přes dva [uŠup konektory(co to je?)](https://blog.laskakit.cz/predstavujeme-univerzalni-konektor-pro-propojeni-modulu-a-cidel-%ce%bcsup/). Díky tomuto konektoru kompatibilním se SparkFun Qwiic a Adafruit STEMMA, můžeš připojit desítky nejrůznějších I2C čidel. 
UART je připojen na piny RX (GPIO5), TX (GPIO4), ADC vstup z děliče napětí připojeného na akumulátor je připojen na jediný ADC vstup ESP8266.
A to rozhodně není všechno.

![Airboard - pinout](https://github.com/LaskaKit/Air_Board/blob/main/img/Airboard_pinout.jpg)

K AirBoard můžeš velmi jednoduše připojit i čidla pevných částic - na desce je 7pinový konektor s I2C rozhraním i UART rozhraním a samozřejmě napájením. Díky tomuto konektoru můžeš připojit nejméně 6 typů senzorů pevných částic. Některé moduly navíc obsahují i čidlo teploty a vlhkosti, například SEN5x.</br>
Jak a co kam připojit jsme sepsali v https://github.com/LaskaKit/Air_Board/blob/main/input/sensors.xlsx</br>
Některá čidla potřebují 5V napájení, většinou kvůli ventilátoru nebo laseru. I na toto jsme při návrhu mysleli - na desku jsme přidali step-up (zvyšující) měnič na 5V. Tím můžeš napájet čidla, která potřebují i 5V napájení.

Pokud se ptáš, jestli můžeš 5V napájené čidlo připojit k ESP8266, tak v drtivé většině ano. Čidla jsou totiž sice napájená 5V, ale výstup je 3.3V kompatibilní (tohle si ale raději vždy potvrď v katalogovém listu čidla).

A co na desce ještě najdeš? Třípinový konektor pro kvalitní připojení čidla teploty DS18B20 (1-wire sběrnice, obsahuje 4k7 pull-up), konektor pro solární panel (ten doporučujeme 6V) a konektor pro připojení akumulátoru. </br>
Ten je napájený z čipu TP4054 a na desce najdeš pájecí most, kterým si zvolíš nabíjecí proud - 260mA nebo 400mA.

K programování budeš potřebovat náš programátor díky kterému AirBoard desku naprogramuješ https://www.laskakit.cz/laskakit-ch9102-programmer-usb-c--microusb--uart/

![Airboard - TOP](https://github.com/LaskaKit/Air_Board/blob/main/img/Air_Board_4.jpg)

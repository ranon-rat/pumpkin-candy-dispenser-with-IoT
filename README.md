# pumkin candy dispenser 

its a really simple candy dispenser that it works with a esp32 ai thinker.

I made it for a school project and idk it looks cool and I like it

![img](https://media.discordapp.net/attachments/663080678623150118/903858258501042217/unknown.png?width=484&height=860)

## list of materials
- [esp32 camera ai thinker model](https://www.amazon.com/-/es/Aideepen-ESP32-CAM-Bluetooth-ESP32-CAM-MB-Arduino/dp/B08P2578LV/ref=sr_1_3?__mk_es_US=%C3%85M%C3%85%C5%BD%C3%95%C3%91&dchild=1&keywords=esp32+cam&qid=1635571237&sr=8-3)
- [micro servo](https://www.amazon.com/-/es/unids-0-32-servos-helic%C3%B3ptero-controles/dp/B07MLR1498/ref=sr_1_5?__mk_es_US=%C3%85M%C3%85%C5%BD%C3%95%C3%91&dchild=1&keywords=micro+servo&qid=1635571279&sr=8-5)
- and then you need a battery (thats your choice)
## how to make it 
for upload the program you only need to connect the ftdi module and the esp32, something like this:

![img](https://i1.wp.com/randomnerdtutorials.com/wp-content/uploads/2019/12/ESP32-CAM-FTDI-programmer-5V-supply.png?resize=750%2C333&quality=100&strip=all&ssl=1)
you only need to conect the signal pin of the servomotor to the pin number 2 and then  connect the gnd and vcc pins of the servomotor to gnd and 3v.

the battery you only need to connect gnd to gnd and vcc to 5v 

(Im a little bit lazy right now so im not going to made a schematic or something like that , maybe later  i will)

## how to upload the program

you only need to use platformio and click in the upload button , and thats all
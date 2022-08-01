# good-micros USB multitap  
This projects goal is to add USB functionality up to four of our retro style joysticks.  

## programming  
download and install the joystick library (https://github.com/MHeironimus/ArduinoJoystickLibrary)
 to the Arduino IDE and upload to an "arduino leonardo".  

## Linux config  
https://superuser.com/questions/104887/usb-joystick-with-linux-only-works-when-i-disconnected-and-reconnected-its  
https://mheironimus.blogspot.com/2015/09/linux-support-for-arduino-leonardo.html  

## ATmega32U4 GPIO pinout  
The device multiplexes each joystick via their GND and updates their status as separate USB HID devices.  

| port |  pin  |
|------|-------|
| PB1  | up    |
| PB2  | down  |
| PB3  | left  |
| PB4  | right |
| PB5  | A     |
| PB6  | B     |
| PF4  | GND 1 |
| PF5  | GND 2 |
| PF6  | GND 3 |
| PF7  | GND 4 |

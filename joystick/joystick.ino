/*
good-micros multiple joystick USB adapter
https://github.com/goodmicros/multitap
*/

// https://github.com/MHeironimus/ArduinoJoystickLibrary
#include "Joystick.h"

//four joysticks with two buttons and axis
Joystick_ Joystick[] = {
    Joystick_(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_JOYSTICK, 2, 0, true, true, false, false, false, false, false, false, false, false, false),
    Joystick_(JOYSTICK_DEFAULT_REPORT_ID+1,JOYSTICK_TYPE_JOYSTICK, 2, 0, true, true, false, false, false, false, false, false, false, false, false),
    Joystick_(JOYSTICK_DEFAULT_REPORT_ID+2,JOYSTICK_TYPE_JOYSTICK, 2, 0, true, true, false, false, false, false, false, false, false, false, false),
    Joystick_(JOYSTICK_DEFAULT_REPORT_ID+3,JOYSTICK_TYPE_JOYSTICK, 2, 0, true, true, false, false, false, false, false, false, false, false, false)
};

// button order
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define FIREA 4
#define FIREB 5

void setup() {
    //joystick mux config (PF4-7)
    DDRF  &= ~( 0b1111 << 4); //input in order to get them high-z
    PORTF &= ~( 0b1111 << 4); //high-z

    //joystick input config (PB1-6)
    DDRB  &= ~(0b111111 << 1); //input
    PORTB |= 0b111111 << 1; //pull-up

    //configure usb joysticks
    for( int i = 0; i < 4; i++){
        Joystick[i].setXAxisRange( -1, 1);
        Joystick[i].setYAxisRange( -1, 1);
        Joystick[i].begin(false);
    }
}

void loop() {
    //update one joystick per loop
    static uint8_t inputCounter = 0;
    inputCounter = ( inputCounter + 1) & 0b11; //count only to 3

    //set mux on selected joystick as output GND and rest to high-z
    DDRF &= 0x0f; //set PF4-7 as input
    DDRF |= ( 1 << ( inputCounter + 4)); //set selected as output
  
    //read input with pressed as 1
    uint8_t input = ~PINB >> 1 & 0b111111; //read and mask PB1-5

    //write to hid
    Joystick[inputCounter].setXAxis( (( input >> RIGHT) & 1) - (( input >> LEFT) & 1));
    Joystick[inputCounter].setYAxis( (( input >> DOWN) & 1) - (( input >> UP) & 1));
    Joystick[inputCounter].setButton( 0, ( input >> FIREA) & 1);
    Joystick[inputCounter].setButton( 1, ( input >> FIREB) & 1);
    Joystick[inputCounter].sendState();
}

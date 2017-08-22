#include <SPI.h>
#include "RF24.h"
#include <Wire.h>
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;

byte addresses[][6] = {"1Node","2Node"};


/****************** User Config ***************************/
/***      Set this radio as radio number 0 or 1         ***/
bool radioNumber = 1;

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(7,8);
/**********************************************************/



/**
* Create a data structure for transmitting and receiving data
* This allows many variables to be easily sent and received in a single transmission
* See http://www.cplusplus.com/doc/tutorial/structures/
*/
struct dataStruct{
  unsigned long _micros;
  float alt;
  float voltage;
}myData;

void setup() {

  bmp.begin();
  Serial.begin(115200);
  Serial.println(F("RF24/examples/GettingStarted_HandlingData"));
  Serial.println(F("*** PRESS 'T' to begin transmitting to the other node"));
  pinMode(13,OUTPUT);
  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
 // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_MAX);
  
  // Open a writing and reading pipe on each radio, with opposite addresses
  if(radioNumber){
    radio.openWritingPipe(addresses[1]);
    radio.openReadingPipe(1,addresses[0]);
  }else{
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1,addresses[1]);
  }
  
  myData.alt = 0;
}

void loop() {
  

    Serial.println(F("Now sending"));
    myData.alt = bmp.readAltitude()-0;
    //Voltage Divider AnalogRead->MeasuredVoltage->Convert to Battery Voltage
    myData.voltage= (analogRead(A2)*(5.0/1023.0))*(147.0/47.0);
    Serial.println(myData.alt);
    Serial.println(myData.voltage);
    myData._micros = micros();
     if (!radio.write( &myData, sizeof(myData) )){
       Serial.println(F("failed"));
     }
    delay(10);
} // Loop

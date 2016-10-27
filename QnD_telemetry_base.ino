
/*
* Getting Started example sketch for nRF24L01+ radios
* This is an example of how to send data from one node to another using data structures
* Updated: Dec 2014 by TMRh20
*/

#include <SPI.h>
#include "RF24.h"

byte addresses[][6] = {"1Node","2Node"};


/****************** User Config ***************************/
/***      Set this radio as radio number 0 or 1         ***/
bool radioNumber = 0;

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(7,8);
/**********************************************************/


// Used to control whether this node is sending or receiving
bool role = 0;

/**
* Create a data structure for transmitting and receiving data
* This allows many variables to be easily sent and received in a single transmission
* See http://www.cplusplus.com/doc/tutorial/structures/
*/
struct dataStruct{
  unsigned long _micros;
  float value;
  float voltage;
}myData;

float maxalt= 0;
void setup() {

  Serial.begin(115200);
  //Serial.println(F("RF24/examples/GettingStarted_HandlingData"));
  //Serial.println(F("*** PRESS 'T' to begin transmitting to the other node"));
  
  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
 // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_LOW);
  
  // Open a writing and reading pipe on each radio, with opposite addresses
  if(radioNumber){
    radio.openWritingPipe(addresses[1]);
    radio.openReadingPipe(1,addresses[0]);
  }else{
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1,addresses[1]);
  }
  
  myData.value = 1.22;
  // Start the radio listening for data
  radio.startListening();
}




void loop() {
  
  

/****************** Pong Back Role ***************************/

  if ( role == 0 )
  {
    //Serial.println("hello");
    if( radio.available()){
                                                           // Variable for the received timestamp
      while (radio.available()) {                          // While there is data ready
        radio.read( &myData, sizeof(myData) );             // Get the payload
      }
     
      if (myData.value > maxalt){
        maxalt=myData.value;
      }
      //Serial.print(F("Meters"));
      Serial.print(myData.value*3.28,0);
      Serial.print(',');
      Serial.print(myData.voltage);
      Serial.print(',');
      Serial.println(myData._micros);
      //Serial.println(" feet");
      //Serial.print("  Max Alt: ");
      //Serial.println(maxalt);
   }
 }




/****************** Change Roles via Serial Commands ***************************/




} // Loop

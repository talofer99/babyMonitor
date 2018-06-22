#include <SPI.h>
#include "RF24.h"

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(7, 8);
/**********************************************************/
byte addresses[][6] = {"1Node", "2Node"};

//RGB LED PINS
byte redLedPin = 3;
byte greenLedPin = 5;
byte blueLedPin = 6;

void setup() {
  Serial.begin(115200);
  Serial.println(F("Parent unit started"));


  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);

  testLeds();
  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_LOW);


  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1, addresses[1]);


  // Start the radio listening for data
  radio.startListening();
}

void loop() {




  unsigned long got_time;

  if ( radio.available()) {
    // Variable for the received timestamp
    while (radio.available()) {                                   // While there is data ready
      radio.read( &got_time, sizeof(unsigned long) );             // Get the payload
    }

    radio.stopListening();                                        // First, stop listening so we can talk
    radio.write( &got_time, sizeof(unsigned long) );              // Send the final one back.
    radio.startListening();                                       // Now, resume listening so we catch the next packets.
    Serial.print(F("Sent response "));
    Serial.println(got_time);
  }
} // Loop

void testLeds() {
  digitalWrite(redLedPin, HIGH);
  delay(150);
  digitalWrite(redLedPin, LOW);

  digitalWrite(greenLedPin, HIGH);
  delay(150);
  digitalWrite(greenLedPin, LOW);

  digitalWrite(blueLedPin, HIGH);
  delay(150);
  digitalWrite(blueLedPin, LOW);
}


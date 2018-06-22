#include <SPI.h>
#include "RF24.h"


/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(7, 8);
/**********************************************************/
byte addresses[][6] = {"1Node", "2Node"};
#define WAITFORPONG 200000L

#define pingEvrey 6000
unsigned long lastPingAttemptTime;
unsigned long lastSuccessPingTime;
unsigned long totalPingsAttempt;
unsigned long totalSuccessPings;

//RGB LED PINS
byte redLedPin = 3;
byte greenLedPin = 5;
byte blueLedPin = 6;




void setup() {
  //start serial
  Serial.begin(115200);
  Serial.println(F("Baby unit started"));

  // set pin output
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);

  testLeds();

  // start radio
  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_LOW);

  // set in/out ports
  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1, addresses[1]);


  // Start the radio listening for data
  radio.startListening();
}

void loop() {


  if (lastPingAttemptTime + pingEvrey < millis()) {
    Serial.println(F("Sending Ping"));
    lastPingAttemptTime = millis();
    totalPingsAttempt++;
    pingAndWaitForPong();
  } //end if

  if (lastSuccessPingTime + (pingEvrey * 2) < millis()) {
    Serial.println(F("Lost communication"));
    delay(100);
  } //end if

} // Loop


void pingAndWaitForPong() {
  // First, stop listening so we can talk.
  radio.stopListening();

  // Take the time, and send it.  This will block until complete
  unsigned long start_time = micros();
  if (!radio.write( &start_time, sizeof(unsigned long) )) {
    Serial.println(F("failed to write - wait for retry"));
    // set leisten again
    radio.startListening();
  } else {
    // set leisting
    radio.startListening();

    unsigned long started_waiting_at = micros();               // Set up a timeout period, get the current microseconds
    boolean timeout = false;                                   // Set up a variable to indicate if a response was received or not

    while ( ! radio.available() ) {                            // While nothing is received
      if (micros() - started_waiting_at > WAITFORPONG ) {           // If waited longer than 200ms, indicate timeout and exit while loop
        timeout = true;
        break;
      }
    }

    if ( timeout ) {                                            // Describe the results
      Serial.println(F("Failed, response timed out."));
    } else {
      unsigned long got_time;                                 // Grab the response, compare, and send to debugging spew
      radio.read( &got_time, sizeof(unsigned long) );
      unsigned long end_time = micros();

      lastSuccessPingTime = millis();
      totalSuccessPings++;
      Serial.println(F("Recived ping verefication"));
      Serial.print(F("Total Pings Attempts - "));
      Serial.println(totalPingsAttempt);

      Serial.print(F("Total Success Pings - "));
      Serial.println(totalSuccessPings);

      // Spew it
      Serial.print(F("Sent "));
      Serial.print(start_time);
      Serial.print(F(", Got response "));
      Serial.print(got_time);
      Serial.print(F(", Round-trip delay "));
      Serial.print(end_time - start_time);
      Serial.println(F(" microseconds"));
    }//end if
  } //end if
}//end void



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

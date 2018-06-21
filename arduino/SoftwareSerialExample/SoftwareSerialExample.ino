#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.println("System started");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);

}

unsigned long lastTransmition;


void loop() { // run over and over
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
<<<<<<< HEAD
//  if (lastTransmition + 2000 < millis()) {
=======
  //if (lastTransmition + 2000 < millis()) {
>>>>>>> 9b4f21f73cf3eff79ba043b743328131967c1350
  //    mySerial.println("Hello, world?");
//    }
}


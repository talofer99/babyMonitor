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
  if (lastTransmition + 2000 < millis()) {
  //    mySerial.println("Hello, world?");
  //  }
}


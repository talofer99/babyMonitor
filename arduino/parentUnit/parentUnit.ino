#include "pinOut.h"
// software serial
#include <SoftwareSerial.h>
SoftwareSerial mySerial(RX_PIN, TX_PIN); // RX, TX


#define pingEvrey 6000
unsigned long lastPingTime;
unsigned long totalPings;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.println("System started");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);

  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);

  testLeds();
}


void loop() { // run over and over
  handleSerialCommunication();


  if (lastPingTime + (2 * pingEvrey) < millis()) {
    Serial.println("Lost communication");
    delay(100);
  }
}

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




void handleSerialCommunication() {
  if (mySerial.available()) {
    char readSerial = mySerial.read();
    Serial.print("Recived :");
    Serial.println(readSerial);
    switch (readSerial) {
      case 'P':
        Serial.println("Recived ping request");
        delay(200);
        mySerial.print("P");
        lastPingTime = millis();
        totalPings++;
        break;
      default:
        break;
    } //end switch
  } //end if
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}


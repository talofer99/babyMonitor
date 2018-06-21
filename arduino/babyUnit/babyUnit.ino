#include "pinOut.h"
// software serial
#include <SoftwareSerial.h>
SoftwareSerial mySerial(RX_PIN, TX_PIN); // RX, TX

#define pingEvrey 6000
unsigned long lastPingAttemptTime;
unsigned long lastSuccessPingTime;
unsigned long totalPingsAttempt;
unsigned long totalSuccessPings;


void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.println(F("System started"));

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);

  // set pin output
  pinMode(redLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);


  testLeds();
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

void loop() { // run over and over
  handleSerialCommunication();


  if (lastPingAttemptTime + pingEvrey < millis()) {
    Serial.println(F("Sending Ping"));
    mySerial.print(F("P"));
    lastPingAttemptTime = millis();
    totalPingsAttempt++;
  }

  if (lastSuccessPingTime + (pingEvrey * 2) < millis()) {
    Serial.println(F("Lost communication"));
    delay(100);
  }

}




void handleSerialCommunication() {
  if (mySerial.available()) {
    char readSerial = mySerial.read();
    Serial.print(F("Recived :"));
    Serial.println(readSerial);
    switch (readSerial) {
      case 'P':
        lastSuccessPingTime = millis();
        totalSuccessPings++;
        Serial.println(F("Recived ping verefication"));
        Serial.print(F("Total Pings Attempts - "));
        Serial.println(totalPingsAttempt);

        Serial.print(F("Total Success Pings - "));
        Serial.println(totalSuccessPings);

        break;
      default:
        break;
    } //end switch
  } //end if
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}


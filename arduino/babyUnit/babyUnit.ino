// software serial
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // RX, TX


#define pingEvrey 3000
unsigned long lastPingAttemptTime;
unsigned long lastSuccessPingTime;
unsigned long totalPingsAttempt;
unsigned long totalSuccessPings;


void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.println("System started");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);

}


void loop() { // run over and over
  handleSerialCommunication();


  if (lastPingAttemptTime + pingEvrey < millis()) {
    Serial.println("Sending Ping");
    mySerial.print("P");
    lastPingAttemptTime = millis();
    totalPingsAttempt++;
  }

  if (lastSuccessPingTime + pingEvrey < millis()) {
    Serial.println("Lost communication");
    delay(100);
  }

}




void handleSerialCommunication() {
  if (mySerial.available()) {
    char readSerial = mySerial.read();
    Serial.print("Recived :");
    Serial.println(readSerial);
    switch (readSerial) {
      case 'P':
        Serial.println("Recived ping verefication");
        lastSuccessPingTime = millis();
        totalSuccessPings++;
        break;
      default:
        break;
    } //end switch
  } //end if
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}


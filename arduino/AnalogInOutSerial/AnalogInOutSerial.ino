// These constants won't change. They're used to give names to the pins used:
const int analogInPin[2] = {A0, A1}; // Analog input pin that the potentiometer is attached to


void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(115200);
  analogReference(EXTERNAL);
}

void loop() {
  Serial.print(0);
  Serial.print("\t");
  Serial.print(1024);
  Serial.print("\t");
  Serial.print(analogRead(analogInPin[0]));
  Serial.print("\t");
  Serial.print(analogRead(analogInPin[1]));
  Serial.print("\n");

  // wait 2 milliseconds before the next loop for the analog-to-digital
  // converter to settle after the last reading:
  delay(50);
}

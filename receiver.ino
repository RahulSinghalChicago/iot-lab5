void setup() {
  Serial.begin(9600);
  Serial.println( "Hello Arduino!" ); 
}
void loop() {
  Serial.println("loop start");
  if (Serial.availableMessage() != 0) {
      string mystr = Serial.readMessage();
      Serial.println("Printed by receiver: " + mystr);
  }
  delay(2000);
}
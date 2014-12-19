void setup() {
  for (int i = 0; i < 24; i++)
    pinMode(i, OUTPUT);
}

void loop() {
  for (int i = 18; i < 22; i++) {
    for (int i = 0; i < 24; i++)
     digitalWrite(i, LOW);
    digitalWrite(i, HIGH);
    for (int i = 0; i < 14; i++) {
      digitalWrite(i, HIGH);
      delay(100);
    }
    digitalWrite(23, HIGH);
    delay(100);
    digitalWrite(22, HIGH);
    delay(100);
  }
}


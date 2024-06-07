void BTConnBeep() {
  tone(BuzzPin, NOTE_BTCONN_LOW, 120);
  delay(150);
  tone(BuzzPin, NOTE_BTCONN_HIGH, 120);
  delay(150);
  noTone(BuzzPin);
  Serial.println("BTConnected");
}

void BTDisconnBeep() {
  tone(BuzzPin, NOTE_BTCONN_HIGH, 120);
  delay(150);
  tone(BuzzPin, NOTE_BTCONN_LOW, 120);
  delay(150);
  noTone(BuzzPin);
  Serial.println("BTDisConnected");
}

void WaterWarnBeep() {
  bool isEmpty  = !VerifyWaterVol();
  if (isEmpty) {
    tone(BuzzPin, NOTE_WATER, 120);
    delay(300);
    tone(BuzzPin, NOTE_WATER, 120);
    delay(300);
    noTone(BuzzPin);
    Serial.println("WaterWarnBeep");
  }
}

void TimeModeStartBeep() {
  tone(BuzzPin, NOTE_TIME_MODE_START, 200);
  delay(300);
  noTone(BuzzPin);
  Serial.println(" TimeModeStartBeep");
}

void NormalEnd() {
  tone(BuzzPin, NOTE_TIME_MODE_END, 800);
  delay(1300);
  noTone(BuzzPin);
  Serial.println("NormalEndBeep");
}

void TempHighBeep() {
  tone(BuzzPin, NOTE_TIME_MODE_END, 200);
  delay(300);
  noTone(BuzzPin);
  tone(BuzzPin, NOTE_TIME_MODE_END, 200);
  delay(300);
  noTone(BuzzPin);
  tone(BuzzPin, NOTE_TIME_MODE_END, 200);
  delay(300);
  noTone(BuzzPin);
  Serial.println("TempHighBeep");
}

void TimeModeEndBeep(bool isException) {
  if (isException) {
    TempHighBeep();
  } else if (!isException) {
    NormalEnd();
  }
}

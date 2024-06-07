void FanCtrl() {
  if (D1Flag != 0 || D2Flag != 0 || D3Flag != 0) {
    digitalWrite(FanRelay, LOW);
    FanOn = true;
  }
  else if (FanOn) {
    digitalWrite(FanRelay, HIGH);
    FanOn = false;
  }
}

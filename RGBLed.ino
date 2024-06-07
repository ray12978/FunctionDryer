void initLed() {
  BTRgbCtrl('D');
  WVRgbCtrl('D');
}

void BTRgbCtrl (char led) { //Bluetooth Rgb Control
  switch (led) {
    case 'R':
      BTLedOutput(1, 0, 0);
      break;
    case 'G':
      BTLedOutput(0, 1, 0);
      break;
    case 'B':
      BTLedOutput(0, 0, 1);
      break;
    case 'D': //disable
      BTLedOutput(0, 0, 0);
      break;
  }
}

void BTLedOutput(bool r, bool g, bool b) {
  digitalWrite(LedRPin_1 , !r);
  digitalWrite(LedGPin_1 , !g);
  digitalWrite(LedBPin_1 , !b);
}

void WVRgbCtrl(char led) { //Water Volume Rgb Control
  switch (led) {
    case 'R':
      WVLedOutput(1, 0, 0);
      break;
    case 'G':
      WVLedOutput(0, 1, 0);
      break;
    case 'B':
      WVLedOutput(0, 0, 1);
      break;
    case 'D': //disable
      WVLedOutput(0, 0, 0);
      break;
  }
}

void WVLedOutput(bool r, bool g, bool b) {
  digitalWrite(LedRPin_2 , !r);
  digitalWrite(LedGPin_2 , !g);
  digitalWrite(LedBPin_2 , !b);
}

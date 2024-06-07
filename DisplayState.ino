void DisplayWVState(bool isrun) {
  bool WaterAva = VerifyWaterVol();
  if (WaterAva) WVRgbCtrl('G');
  else if (!WaterAva) {
    WVRgbCtrl('R');
    if (isrun) WaterWarnBeep();
  }
}

void DisplayBTState() {
  if (isBTConnected) BTRgbCtrl('G');
  else if (!isBTConnected) {
    BTLedOn = !BTLedOn;
    if (BTLedOn) BTRgbCtrl('B');
    else BTRgbCtrl('D');
  }
}

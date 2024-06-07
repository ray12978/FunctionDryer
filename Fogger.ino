void FoggerBtn() {
  bool FogSta = digitalRead(FogBtn);
  if (FogBtnTmp && FogSta) {
    FoggerCtrl(true);
    FogBtnTmp = false;
    Serial.println("Fogger Presd");
  }
  else if (!FogBtnTmp && !FogSta) {
    FogBtnTmp = true;
    FoggerCtrl(false);
  }
}

void FoggerCtrl(bool stap) {
  bool WaterAva = VerifyWaterVol();
  DisplayWVState(stap);
  if (stap && WaterAva) {
    digitalWrite(FogRelay, LOW);
  } else if (!stap || !WaterAva) {
    digitalWrite(FogRelay, HIGH);
  }
}

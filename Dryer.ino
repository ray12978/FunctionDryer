void DryerControl(byte D1, byte D2, byte D3) {
  bool isTempHigh = !getEmi();
  if (!isTempHigh) {
    RelayCtrl(D1, D2, D3);
    isRun = true;
    if(D1 == 0 && D2 == 0 && D3 == 0) isRun = false;
    delay(200);
  } else if (isTempHigh) {
    Serial.println("Temp High");
  }
  FanCtrl();
}
void RelayCtrl(byte D1, byte D2, byte D3) {
  if (D1 == 0) {
    RelayOutput(DryRelayS_1, DryRelayB_1, 0, 0);
  }
  else if (D1 == 1) {
    RelayOutput(DryRelayS_1, DryRelayB_1, 1, 0);
  }

  if (D2 == 0) {
    RelayOutput(DryRelayS_2, DryRelayB_2, 0, 0);
  }
  else if (D2 == 2) {
    RelayOutput(DryRelayS_2, DryRelayB_2, 1, 0);
  }
  else if (D2 == 1) {
    RelayOutput(DryRelayS_2, DryRelayB_2, 0, 1);
  }

  if (D3 == 0) {
    RelayOutput(DryRelayS_3, DryRelayB_3, 0, 0);
  }
  else if (D3 == 2) {
    RelayOutput(DryRelayS_3, DryRelayB_3, 1, 0);
  }
  else if (D3 == 1) {
    RelayOutput(DryRelayS_3, DryRelayB_3, 0, 1);
  }
}

void RelayOutput(byte pin1, byte pin2, bool SMode, bool BMode) { //Dryer1,Dryer2,小風,大風
  digitalWrite(pin1, !SMode); //繼電器Low動作 反旗標方便閱讀
  digitalWrite(pin2, !BMode);
}

void setDryerState() {
  bool SwSta = digitalRead(MicroSw);
  if (!getAllCtrlSta()) {
    if (digitalRead(DryBtn_1) && DryerTmp_1) {
      D1Flag = 1;
      DryerTmp_1 = false;
      Serial.println("11");
      DryerControl(D1Flag, D2Flag, D3Flag);
    }
    else if (!digitalRead(DryBtn_1) && !DryerTmp_1) {
      D1Flag = 0;
      DryerTmp_1 = true;
      Serial.println("10");
      DryerControl(D1Flag, D2Flag, D3Flag);
    }
    if (!SwSta) {
      if (digitalRead(DryBtn_2) && DryerTmp_2) {
        D2Flag = PreD2Flag;
        D2Flag++;
        if (D2Flag == 3 || D3Flag == 2) D2Flag = 1;
        DryerTmp_2 = false;
        Serial.println("21");
        DryerControl(D1Flag, D2Flag, D3Flag);
      }
      else if (!digitalRead(DryBtn_2) && !DryerTmp_2) {
        PreD2Flag = D2Flag;
        D2Flag = 0;
        DryerTmp_2 = true;
        Serial.println("20");
        DryerControl(D1Flag, D2Flag, D3Flag);
      }
      if (digitalRead(DryBtn_3) && DryerTmp_3) {
        D3Flag = PreD3Flag;
        D3Flag++;
        if (D3Flag == 3 || D2Flag == 2) D3Flag = 1;
        DryerTmp_3 = false;
        Serial.println("31");
        DryerControl(D1Flag, D2Flag, D3Flag);
      }
      else if (!digitalRead(DryBtn_3) && !DryerTmp_3) {
        PreD3Flag = D3Flag;
        D3Flag = 0;
        DryerTmp_3 = true;
        Serial.println("30");
        DryerControl(D1Flag, D2Flag, D3Flag);
      }
    }
  }
}

void ShutdownAll(bool isNeedBeep, bool exception) {
  digitalWrite(DryRelayS_1, HIGH);
  digitalWrite(DryRelayB_1, HIGH);
  digitalWrite(DryRelayS_2, HIGH);
  digitalWrite(DryRelayB_2, HIGH);
  digitalWrite(DryRelayS_3, HIGH);
  digitalWrite(DryRelayB_3, HIGH);
  digitalWrite(FanRelay, HIGH);
  digitalWrite(FogRelay, HIGH);
  D1Flag = 0;
  D2Flag = 0;
  D3Flag = 0;
  DryerTmp_1 = false;
  DryerTmp_2 = false;
  DryerTmp_3 = false;
  isBTControl = false;
  Serial.println("End");
  if (isNeedBeep) {
    PreD2Flag = 0;
    PreD3Flag = 0;
    TimeModeEndBeep(exception);
  }
}

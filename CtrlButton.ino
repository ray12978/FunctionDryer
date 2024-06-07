void AllCtrlBtnListener() {
  bool SwSta = digitalRead(AllCtrlBtn);
  bool MicroSta = digitalRead(MicroSw);
  if (!MicroSta) {
    if (AllCtrlBtnTmp && digitalRead(AllCtrlBtn) && isTimeOver) {
      Serial.println("Ctrl pressed");
      BtnFlag = PreBtnFlag;
      BtnFlag++;
      if (BtnFlag == 3) BtnFlag = 1;
      AllCtrlBtnTmp = false;

      if (BtnFlag == 1) {
        isStaChg = true;
        D1Flag = 1;
        D2Flag = 1;
        D3Flag = 1;
        DryerControl(1, 1, 1);
        Serial.println("Btn1");
      }
      else if (BtnFlag == 2) {
        isStaChg = true;
        
        D1Flag = 1;
        D2Flag = 2;
        D3Flag = 1;
        DryerControl(1, 2, 1);
        Serial.println("Btn2");
      }
    }
    else if (!digitalRead(AllCtrlBtn) && !AllCtrlBtnTmp) {
      PreBtnFlag = BtnFlag;
      BtnFlag = 0;
      isStaChg = true;
      D1Flag = 0;
      D2Flag = 0;
      D3Flag = 0;
      DryerControl(0, 0, 0);
      AllCtrlBtnTmp = true;
      Serial.println("Btn0");
    }
  }
}

bool getAllCtrlSta() {
  return digitalRead(AllCtrlBtn);
}

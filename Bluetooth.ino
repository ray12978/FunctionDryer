void BTListener() {
  CmdSaver = "";
  while (BT.available()) {
    val = BT.read();
    //while (mTimer(10));
    delay(20);
    ScanCmd(val);
    //Serial.print("val:");
    //Serial.println(val);
  }
}

void ScanCmd(char c) {
  if (c == '$' || c == '+') StrSav = true;
  if (StrSav) {
    //while (mTimer(5));
    delay(5);
    CmdSaver += c;
    CmdSaver.trim();
  }
  //Serial.println(CmdSaver);
  if (CmdSaver.length() > STR_LEN - 1 && CmdSaver.charAt(0) == '$') {
    CmdProcess(CmdSaver);
    CmdSaver = "";
    StrSav = false;
  }
  Serial.println(CmdSaver);
  if (CmdSaver.length() > 9 && CmdSaver.charAt(0) == '+') {
    if (CmdSaver.equals("+CONNECTED")) {
      Serial.println("Connected");
      isBTConnected = true;
      BTConnBeep();
    }
    if (CmdSaver.equals("+DISC:SUCC")) {
      Serial.println("DisConnected");
      isBTConnected = false;
      BTDisconnBeep();
    }
    CmdSaver = "";
    StrSav = false;
  }
}

bool CancelListen() {
  CmdSaver = "";
  while (BT.available()) {
    val = BT.read();
    //while (mTimer(10));
    delay(10);
    if (val == '$') StrSav = true;
    if (StrSav) {
      //while (mTimer(5));
      delay(5);
      CmdSaver += val;
      CmdSaver.trim();
    }
    Serial.println(CmdSaver);
    if (CmdSaver.length() > STR_LEN - 10 && CmdSaver.charAt(0) == '$') {
      StrSav = false;
      if (CmdSaver.charAt(1) == 'N') {
        CmdSaver = "";
        isCanceled = true;
        return false;
      }
      CmdSaver = "";
    }
  }
  return true;
}

void BTRespond() {
  //Serial.println("Res");
  if (isBTConnected) {
    int WaterVal = getWaterVol();
    int temp = getTemp();
    char rStr[8] = {};
    rStr[0] = 'M';
    rStr[1] = temp % 100 / 10 + '0';
    rStr[2] = temp % 10 + '0';
    rStr[3] = WaterVal / 100 + '0';
    rStr[4] = WaterVal % 100 / 10 + '0';
    rStr[5] = WaterVal % 10 + '0';
    rStr[6] = 'O';
    rStr[7] = '\0';
    BT.write(rStr);
    Serial.println("Res");
  }
}

void SendStartState() {
  char res[4] = "MTS\0";
  BT.write(res);
  Serial.println("Time Start");
}

void SendOverState() {
  char res[4] = "MTN\0";
  bool isTempHigh = !getEmi();
  bool AllCtrlSta = getAllCtrlSta();
  if (isCanceled || AllCtrlSta) {
    res[2] = 'C';
    BT.write(res);
    isCanceled = false;
  }
  else if (isTempHigh) {
    res[2] = 'T';
    BT.write(res);
  } else BT.write(res);

  isTimeOver = true;
}

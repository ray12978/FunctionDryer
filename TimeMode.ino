void CmdProcess(String Str) {
  STR_INDEX = 0;
  bool FogOn;
  bool isTempHigh = !getEmi();
  if (Str.charAt(STR_INDEX) == '$') {//0 起始位元
    STR_INDEX++;

    if (Str.charAt(STR_INDEX) == 'Y') {//1 總開關
      STR_INDEX++;
      isBTControl = true;

      if (Str.charAt(STR_INDEX) == 'Y') {//2 水霧旗標
        FogOn = true;
      } else FogOn = false;
      STR_INDEX++;

      if (Str.charAt(STR_INDEX) == 'D') {//3 風扇段數起始位元
        STR_INDEX++;
        BTDryFlag_1 = Str.charAt(STR_INDEX) - '0'; //4 風扇1段數
        STR_INDEX++;
        BTDryFlag_2 = Str.charAt(STR_INDEX) - '0'; //5 風扇2段數
        STR_INDEX++;
        BTDryFlag_3 = Str.charAt(STR_INDEX) - '0'; //6 風扇3段數
        STR_INDEX++;

        if (BTDryFlag_2 == 2 && BTDryFlag_3 == 2) BTDryFlag_3 = 1; //不可同時開啟2段風
        if (Str.charAt(STR_INDEX) == 'Y') { //7 計時旗標
          STR_INDEX++;
          isTimeOver = false;
          while (STR_INDEX < STR_LEN - 1) {// 8 計時秒數 共三位數
            TimeVal[STR_INDEX - 8] = Str.charAt(STR_INDEX) - '0'; //計時秒數
            STR_INDEX++;
          }

          unsigned long time1 = TimeVal[0] * 100 + TimeVal[1] * 10 + TimeVal[2];
          time1 = time1 * 1000 + millis();
          TimeModeSec = time1;
          Serial.print("Time:");
          Serial.println(time1);
          SendStartState();
          TimeModeStartBeep();
          DryerControl(BTDryFlag_1, BTDryFlag_2, BTDryFlag_3);
          FoggerCtrl(FogOn);
          while (Timer(time1)/*TimeModeSec != 0*/ && CancelListen() && getEmi() /*&& !getAllCtrlSta()*/) { // Timing mode
            isTimeMode = true;
            isStaChg = true;

            wdt_reset();
            //Serial.print("Count:");
            //Serial.println(TimeModeSec);
          }


          FogOn = false;
          isTimeMode = false;
          FoggerCtrl(FogOn);
          ShutdownAll(true, isTempHigh);
          SendOverState();
        } else if (Str.charAt(STR_INDEX) == 'N') {
          TimeModeStartBeep();
          isTimeOver = false;
          SendStartState();
          DryerControl(BTDryFlag_1, BTDryFlag_2, BTDryFlag_3);
          FoggerCtrl(FogOn);
          while (CancelListen() && getEmi()/* && !getAllCtrlSta()*/) {
            isTimeMode = true;
            isStaChg = true;
            wdt_reset();
          }

          //bool isTempHigh = !getEmi();
          FogOn = false;
          isTimeMode = false;
          FoggerCtrl(FogOn);
          ShutdownAll(true, isTempHigh);
          SendOverState();
        }
      }
    } else if (Str.charAt(STR_INDEX) == 'N') {
      ShutdownAll(false, false);
      FogOn = false;
      FoggerCtrl(FogOn);
    }
  }
}

bool Timer(unsigned long sec) {
  unsigned long curTime = millis();
  if (curTime > sec) {
    /*Serial.print("sec: ");
    Serial.println(sec);
    Serial.print("pre: ");
    Serial.println(preTime);
    Serial.print("cur: ");
    Serial.println(curTime);*/
    preTime = curTime;
    return false;
  } else {
    /*Serial.print("sec: ");
    Serial.println(sec);
    Serial.print("pre: ");
    Serial.println(preTime);
    Serial.print("cur: ");
    Serial.println(curTime);*/
    return true;
  }
}

bool mTimer(long mills) {
  unsigned long curTime = millis();
  if (curTime - preTime >= mills) {
    preTime = curTime;
    return false;
  } else return true;
}

void InterruptTimer() {
  static unsigned int count = 0;
  ++count;
  if (count % BTCOUNT_EVENT_TIME == 0) {
    TimeModeCD();
  }
  if ( count % BTRESPOND_EVENT_TIME == 0) BTRespond();
  if ( count % BTLED_EVENT_TIME == 0) DisplayBTState();
}

bool timer(int secondint) {
  arduinoTimeValue = millis();
  
  if (target < arduinoTimeValue) {
    arduinoTimeValue = 0;
    target = 0;
    Serial.println("YES");
    return false;
  }
  else {
    arduinoTimeValue = millis();
    target = arduinoTimeValue + (secondint * 1000);
    return true;
  }



}

void TimeModeCD() {
  if (TimeModeSec != 0)--TimeModeSec;
}

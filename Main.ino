void setup() {
  DhtInit();
  pinMode(LedRPin_1 , OUTPUT);
  pinMode(LedGPin_1 , OUTPUT);
  pinMode(LedBPin_1 , OUTPUT);
  pinMode(LedRPin_2 , OUTPUT);
  pinMode(LedGPin_2 , OUTPUT);
  pinMode(LedBPin_2 , OUTPUT);
  pinMode(WATER_PIN , INPUT);
  pinMode(DryBtn_1 , INPUT);
  pinMode(DryBtn_2 , INPUT);
  pinMode(DryBtn_3 , INPUT);
  pinMode(DryRelayB_1 , OUTPUT);
  pinMode(DryRelayS_1 , OUTPUT);
  pinMode(DryRelayB_2 , OUTPUT);
  pinMode(DryRelayS_2 , OUTPUT);
  pinMode(DryRelayB_3 , OUTPUT);
  pinMode(DryRelayS_3 , OUTPUT);
  pinMode(FogRelay, OUTPUT);
  pinMode(FanRelay, OUTPUT);
  pinMode(FogBtn, INPUT);
  pinMode(AllCtrlBtn , INPUT);
  pinMode(MicroSw, INPUT);
  Serial.begin(9600);
  BT.begin(9600);
  MsTimer2::set(INTERVAL, InterruptTimer); // INTERVAL ms
  MsTimer2::start( );
  initLed();
  wdt_enable(WDTO_8S);
  //wdt_disable();
  Serial.println("Start");
  ShutdownAll(false, false);
}

void loop() {
  wdt_reset();
  DisplayWVState(false);
  BTListener();
  //noTone(BuzzPin);
  if (!isBTControl) { //藍芽沒有控制才做
    wdt_reset();
    FoggerBtn();
    AllCtrlBtnListener();
    setDryerState();
    if (!getEmi() && isRun) {
      ShutdownAll(true, true);
      isRun = false;
    }
    MicroCtrl();
  }
}

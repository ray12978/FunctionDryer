void MicroCtrl() {
  bool SwSta = digitalRead(MicroSw);
  if (SwSta && !ClotheFlag && isTimeOver) {
    bool isTempHigh = !getEmi();
    if (!isTempHigh) {
      D2Flag = 1;
      D3Flag = 1;
      DryerControl(D1Flag, D2Flag, D3Flag);
      ClotheTmp = true;
      ClotheFlag = true;
      isStaChg = true;
    }
  }
  else if (!SwSta && ClotheTmp) {
    D2Flag = 0;
    D3Flag = 0;
    DryerControl(D1Flag, D2Flag, D3Flag);
    isStaChg = true;
    ClotheFlag = false;
    ClotheTmp = false;
  }
}

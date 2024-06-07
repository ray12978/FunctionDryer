#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <SoftwareSerial.h>
#include <avr/wdt.h>
#include "pitches.h"
#include <MsTimer2.h>

/****************Pin Init******************/
//Relay 5v 低電位動作
const byte DryRelayB_1 = 23; //Dryer One Relay Big Fan
const byte DryRelayS_1 = 25; //Dryer One Relay Small Fan
const byte DryRelayB_2 = 27;
const byte DryRelayS_2 = 29;
const byte DryRelayB_3 = 31;
const byte DryRelayS_3 = 33;
const byte FogRelay = 35;
const byte FanRelay = 37;

//Control Button
const byte FogBtn = 53;
const byte AllCtrlBtn = 52;
const byte MicroSw = 39;

//Dryer Button
const byte DryBtn_1 = 43;
const byte DryBtn_2 = 49;
const byte DryBtn_3 = 51;

//DHT22
const byte DhtPin = 41;
DHT_Unified dht(DhtPin, DHT22);
uint32_t delayMS;

//Water Sensor
#define WATER_PIN A5

//RGBLed 共陽 電阻220~330
//For bluetooth module
const byte LedGPin_1 = 9;
const byte LedBPin_1 = 10;
const byte LedRPin_1 = 8;

//For water volume state
const byte LedGPin_2 = 19;
const byte LedBPin_2 = 18;
const byte LedRPin_2 = 20;

//Bluetooth  BC04-B
SoftwareSerial BT(11, 12); // BC04-B模組傳送腳TX, 接收腳RX

//Buzzer 無源蜂鳴器
const byte BuzzPin = 17;

/****************控制旗標****************/
//Fogger
bool FogBtnTmp = false;
byte FogFlag = 0;

//Control Button
bool AllCtrlBtnTmp = false;
byte BtnFlag = 0;
byte PreBtnFlag = 0;

//Dryer
byte D1Flag = 0;
byte D2Flag = 0;
byte D3Flag = 0;
byte PreD2Flag = 0;
byte PreD3Flag = 0;
bool DryerTmp_1 = false;
bool DryerTmp_2 = false;
bool DryerTmp_3 = false;
bool isStaChg = false;
bool isRun = false;

//Fan
bool FanOn = false;

//Clothe Micro
bool ClotheFlag = false;
bool ClotheTmp = true;

//EMI Flag
volatile bool Emi = true;

//BT 資料處理
String CmdSaver;
char val;  // 儲存接收資料的變數
byte STR_INDEX = 0;
const byte STR_LEN = 12;

int BTDryFlag_1 = 0;
int BTDryFlag_2 = 0;
int BTDryFlag_3 = 0;
char TimeVal[3];
bool StrSav = false;

//Timer
unsigned long preTime = 0;
const int BTCOUNT_EVENT_TIME = 1000;  //每 1000 ms 做一次 myJobOne
const int BTRESPOND_EVENT_TIME = 3000;  //每 3000 ms 做一次 myJobOne
const int BTLED_EVENT_TIME = 800;  //每 800 ms 做一次 myJobOne
const int INTERVAL = 1;
static unsigned int TimeModeSec = 0;
long arduinoTimeValue = millis();
long target  = 0;



//BT Flag
bool isBTConnected = false;
bool ATCheck = false;
bool isCanceled = false;
bool isBTControl = false;
bool isTimeOver = true;

//RGB Blink Flag
bool BTLedOn = false;
bool WVLedOn = false;

//Buzzer
bool isTimeMode = false;

void InterruptTimer();

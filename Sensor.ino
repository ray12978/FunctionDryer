void DhtInit() {
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000;
}

int getTemp() {
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    return 0;
  }
  else {
    int t = event.temperature;
    return t;
  }
}

float getHumi() {
  sensors_event_t event;
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    return 0;
  }
  else {
    float h = event.relative_humidity;
    return h;
  }
}

bool getEmi() {
  //Serial.print("Temp: ");
 // Serial.println(getTemp());
  if (getTemp() >= 40) return false;

  else return true;
  //return true;
}

bool VerifyWaterVol() {
  if (getWaterVol() >= 100) return true;

  else return false;
  //return true;
}

int getWaterVol() {
  return analogRead(WATER_PIN);
}

#include "03_CamBienDong.h"

Adafruit_INA219 ina219;

void CamBienDong::begin(void) {
  Wire.begin(_PIN_SDA, _PIN_SCL);
  ina219.begin();
}

void CamBienDong::readData(void) {
  current_mA = ina219.getCurrent_mA();
}
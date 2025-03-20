#ifndef CAMBIENDONG_H
#define CAMBIENDONG_H

#include <Adafruit_INA219.h>
#include <Wire.h>

#define _PIN_SDA 18
#define _PIN_SCL 19

class CamBienDong {
public:
  float current_mA;
  void begin(void);
  void readData(void);
};

#endif
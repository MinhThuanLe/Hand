#ifndef DC_MOTOR_H
#define DC_MOTOR_H

#include <Arduino.h>
#include <esp32-hal-ledc.h>

#define _QuayThuan 1
#define _QuayNghich 0
#define _Dung 2

#define _pinDIR1 4
#define _pinDIR2 16
#define _pinPWM 17
#define _kenhPWM 1

class Motor {
  public:
  void begin(void);
  void DieuKhien(int pwm, int dir);
};

#endif
#include "01_DCMotor.h"

void Motor::begin() {
  ledcSetup(_kenhPWM, 1000, 15);
  ledcAttachPin(_pinPWM, _kenhPWM);
  pinMode(_pinDIR1, OUTPUT);
  pinMode(_pinDIR2, OUTPUT);
  
  DieuKhien(0, _Dung);
}

void Motor::DieuKhien(int pwm, int dir) {

  uint32_t duty = ((100-pwm) * 32767) / 100;

  ledcWrite(_kenhPWM, duty);
  if (dir == _QuayThuan) {
    digitalWrite(_pinDIR1, HIGH);
    digitalWrite(_pinDIR2, LOW);
  } else if (dir == _QuayNghich) {
    digitalWrite(_pinDIR1, LOW);
    digitalWrite(_pinDIR2, HIGH);
  } else if (dir == _Dung) {
    digitalWrite(_pinDIR1, LOW);
    digitalWrite(_pinDIR2, LOW);
  }
}
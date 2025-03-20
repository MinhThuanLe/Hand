#include "00_ChuongTrinhChinh.h"

Motor _motor;
FSR402 _sensor;
CamBienDong _myINA;

//Biến toàn cục
volatile int sensor_value1 = 0;
volatile int sensor_value2 = 0;
volatile int setpoint = 0;

//Tao task cho sensor
void SensorTask(void *pvParameters) {
  while (1) {
    _sensor.readSensor();
    setpoint = _sensor.MA2_output_Sensor2 - _sensor.MA1_output_Sensor2;
    Serial.println(setpoint);
    vTaskDelay(pdMS_TO_TICKS(100));  // Đọc cảm biến sau mỗi 100ms
  }
}

// Tạo task cho Motor
void MotorTask(void *pvParameters) {
  while (1) {
    if (setpoint > 1500) {
      _motor.DieuKhien(45, _QuayThuan);
    } else if (setpoint < -1000) {
      _motor.DieuKhien(80, _QuayNghich);
    }
    // _motor.DieuKhien(30, _QuayNghich);
    vTaskDelay(pdMS_TO_TICKS(100));

    // _motor.DieuKhien(1000, _QuayNghich);
    // vTaskDelay(pdMS_TO_TICKS(2000));

    // _motor.DieuKhien(0, _Dung);
    // vTaskDelay(pdMS_TO_TICKS(2000));
  }
}

void KhoiTao() {
  Serial.begin(9600);
  _motor.begin();
  _sensor.begin();

  xTaskCreate(MotorTask, "Motor Task", 2048, NULL, 1, NULL);
  xTaskCreate(SensorTask, "Sensor Task", 2048, NULL, 1, NULL);
}

void ChuongTrinhChinh() {
}

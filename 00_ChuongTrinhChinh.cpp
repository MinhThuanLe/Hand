#include "00_ChuongTrinhChinh.h"

Motor _motor;
FSR402 _sensor;

//Biến toàn cục
volatile int sensor_value1 = 0;
volatile int sensor_value2 = 0;

//Tao task cho sensor
void SensorTask(void *pvParameters) {
  while (1) {
    _sensor.readSensor();
    sensor_value1 = _sensor.sensorValue1;

    Serial.print("Sensor 1: ");
    Serial.println(sensor_value1);

    vTaskDelay(pdMS_TO_TICKS(100));  // Đọc cảm biến sau mỗi 100ms
  }
}

void MotorTask(void *pvParameters) {
  while (1) {
    if (sensor_value1 < 300) {
      _motor.DieuKhien(45, _QuayThuan);
    } else if (sensor_value1 > 600) {
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

#ifndef FSR402_H
#define FSR402_H

#include <Arduino.h>

//Chọn chân kết nối cảm biến
#define Sensor_1 35
#define Sensor_2 34



class FSR402 {
private:
  // analogRead value

  int sensorValue1_p;
  int sensorValue2_p;

  int MA1_width = 10;
  int MA2_width = 30;
  double MA1_Value_Sensor1[10];
  double MA1_Value_Sensor2[30];
  double MA2_Value_Sensor1[10];
  double MA2_Value_Sensor2[30];

  float sqetvalue;
  int count = 0;

  float deltaMA1, deltaMA2;

  double Threshold_Close = 20;
  double Threshold_Open = -20;

  int upperThreshold, lowerThreshold, Threshold;
  int X1, X2;
  float delta1, delta2;

public:
  int sensorValue1;
  int sensorValue2;
  double MA1_output_Sensor1;
  double MA1_output_Sensor2;
  double MA2_output_Sensor1;
  double MA2_output_Sensor2;
public:
  void begin(void);
  void readSensor(void);
  void MovingAverage(void);
};
#endif
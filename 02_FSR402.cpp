#include "02_FSR402.h"

void FSR402::begin() {
    pinMode(Sensor_1, INPUT);
    pinMode(Sensor_2, INPUT);
    vTaskDelay(pdMS_TO_TICKS(100));

    if (this->MA1_width > this->MA2_width) {
        for (int i = 0; i < this->MA1_width; i++) {
            sensorValue1 = 1023 - analogRead(Sensor_1);
            sensorValue2 = 1023 - analogRead(Sensor_2);
            MA1_Value_Sensor1[i] = MA1_Value_Sensor1[i] + sensorValue1;
            MA1_Value_Sensor2[i] = MA1_Value_Sensor2[i] + sensorValue2;
            if (i < this->MA2_width) {
                MA2_Value_Sensor1[i] = MA2_Value_Sensor1[i] + sensorValue1;
                MA2_Value_Sensor2[i] = MA2_Value_Sensor2[i] + sensorValue2;
            }
        }
    }
    else if (this->MA1_width < this->MA2_width) {
        for (int i = 0; i < this->MA2_width; i++) {
            sensorValue1 = 1023 - analogRead(Sensor_1);
            sensorValue2 = 1023 - analogRead(Sensor_2);
            MA2_Value_Sensor1[i] = MA2_Value_Sensor1[i] + sensorValue1;
            MA2_Value_Sensor2[i] = MA2_Value_Sensor2[i] + sensorValue2;
            if (i < this->MA1_width) {
                MA1_Value_Sensor1[i] = MA1_Value_Sensor1[i] + sensorValue1;
                MA1_Value_Sensor2[i] = MA1_Value_Sensor2[i] + sensorValue2;
            }
        }
    }
}


void FSR402::readSensor() {
    this->sensorValue1 = 1023 - analogRead(Sensor_1);
    this->sensorValue2 = 1023 - analogRead(Sensor_2);

    this->MovingAverage(); // Gọi hàm thành viên

    if (count > 10) {
        this->X1 = this->sensorValue1;
        this->X2 = this->sensorValue2;
        count = 0;
    }
    else {
        count++;
    }
    
    this->delta1 = this->sensorValue1 - this->sensorValue1_p;
    this->delta2 = this->sensorValue2 - this->sensorValue2_p;

    this->sensorValue1_p = this->sensorValue1;
    this->sensorValue2_p = this->sensorValue2;

    if (((this->delta1) * (this->delta1) + (this->delta2) * (this->delta2)) > 0) {
        this->sqetvalue = (this->delta1) * (this->delta1) + (this->delta2) * (this->delta2);
    }
    else {
        this->sqetvalue = 0;
    }
}


void FSR402::MovingAverage() {
    this->MA1_output_Sensor1 = 0; this->MA1_output_Sensor2 = 0;
    this->MA2_output_Sensor1 = 0; this->MA2_output_Sensor2 = 0;

    for (int i = 0; i < this->MA1_width - 1; i++) {
        this->MA1_Value_Sensor1[i] = this->MA1_Value_Sensor1[i+1];
        this->MA1_Value_Sensor2[i] = this->MA1_Value_Sensor2[i+1];
        this->MA1_output_Sensor1 += this->MA1_Value_Sensor1[i];
        this->MA1_output_Sensor2 += this->MA1_Value_Sensor2[i];
    }
    this->MA1_Value_Sensor1[this->MA1_width - 1] = this->sensorValue1;
    this->MA1_Value_Sensor2[this->MA1_width - 1] = this->sensorValue2;
    this->MA1_output_Sensor1 += this->sensorValue1;
    this->MA1_output_Sensor2 += this->sensorValue2;
    this->MA1_output_Sensor1 /= this->MA1_width;
    this->MA1_output_Sensor2 /= this->MA1_width;

    for (int i = 0; i < this->MA2_width - 1; i++) {
        this->MA2_Value_Sensor1[i] = this->MA2_Value_Sensor1[i+1];
        this->MA2_Value_Sensor2[i] = this->MA2_Value_Sensor2[i+1];
        this->MA2_output_Sensor1 += this->MA2_Value_Sensor1[i];
        this->MA2_output_Sensor2 += this->MA2_Value_Sensor2[i];
    }
    this->MA2_Value_Sensor1[this->MA2_width - 1] = this->sensorValue1;
    this->MA2_Value_Sensor2[this->MA2_width - 1] = this->sensorValue2;
    this->MA2_output_Sensor1 += this->sensorValue1;
    this->MA2_output_Sensor2 += this->sensorValue2;
    this->MA2_output_Sensor1 /= this->MA2_width;
    this->MA2_output_Sensor2 /= this->MA2_width;

    this->deltaMA1 = this->MA1_output_Sensor1 - this->MA2_output_Sensor1;
    this->deltaMA2 = this->MA1_output_Sensor2 - this->MA2_output_Sensor2;
}

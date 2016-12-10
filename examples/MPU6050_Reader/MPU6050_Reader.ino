/*
 * MPU6050_Reader.ino - A library for using the MPU-6050 with Arduino.
 * Written by MrTijn/Tijndagamer
 * Copyright (c) 2016 MrTijn/Tijndagamer
 * Released under the MIT license.
 */

#include <Wire.h>
#include <Arduino.h>
#include <MPU6050.h>

MPU6050 mpu6050;

void setup() {
    Serial.begin(9600);
    if (mpu6050.wakeup()) {
        Serial.println("wakeup succes");
    } else {
        Serial.println("wakeup failed");
    }
    Serial.println("Starting mpu6050 example...");
    Serial.println(mpu6050.readTemp());
}

void loop() {
    Serial.print("Accelerometer:");
    Serial.print("\t");
    Serial.print(mpu6050.readAccelX());
    Serial.print("\t");
    Serial.print(mpu6050.readAccelY());
    Serial.print("\t");
    Serial.print(mpu6050.readAccelZ());
    Serial.println();
    Serial.print("Gyroscope:");
    Serial.print("\t");
    Serial.print(mpu6050.readGyroX());
    Serial.print("\t");
    Serial.print(mpu6050.readGyroY());
    Serial.print("\t");
    Serial.print(mpu6050.readGyroZ());
    Serial.println();
    delay(1000);
}

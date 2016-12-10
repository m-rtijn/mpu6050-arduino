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
    Serial.println(mpu6050.readAccelY());
    Serial.println(mpu6050.readGyroX());
    Serial.println(mpu6050.readGyroY());
}

void loop() {
}

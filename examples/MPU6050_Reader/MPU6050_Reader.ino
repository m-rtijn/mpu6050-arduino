/*
 * MPU6050_Reader.ino - A library for using the MPU-6050 with Arduino.
 * Written by MrTijn/Tijndagamer
 * Copyright (c) 2016 MrTijn/Tijndagamer
 * Released under the MIT license.
 */

#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu6050(0x68);

void setup() {
    Serial.begin(9600);
    Serial.println("Starting mpu6050 example...");
}

void loop() {
    Serial.println("Temp: ");
    Serial.println(mpu6050.readTemp());
    delay(1000);
}

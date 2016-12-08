/*
 * MPU6050.cpp - A library for using the MPU-6050 with Arduino.
 * Written by MrTijn/Tijndagamer
 * Copyright (c) 2016 MrTijn/Tijndagamer
 * Released under the MIT license.
 */

#include "Arduino.h"
#include "MPU6050.h"
#include "Wire.h"

MPU6050::MPU6050(uint8_t address) {
    this.address = address;

    // Wakeup the device
    Wire.begin();
    Wire.beginTransmission(address);
    Wire.write(PWR_MGMT_1);
    Wire.write(0);
    Wire.endTransmission();
}

int16_t MPU6050::read_i2c_word(uint8_t register_msb) {
    Wire.beginTransmission(this.address);
    Wire.write(register_msb);
    // Don't release the bus to be able to read multiple values in one go
    Wire.endTransmission(false);
    Wire.requestFrom(this.address, 2, true);

    int msb = Wire.read();
    int lsb = Wire.read();

    int16_t val = (msb << 8) + lsb;
    if (val >= 0x8000) {
        return -((65536 - val) + 1);
    } else {
        return val;
    }
}

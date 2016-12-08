/*
 * MPU6050.cpp - A library for using the MPU-6050 with Arduino.
 * Written by MrTijn/Tijndagamer
 * Copyright (c) 2016 MrTijn/Tijndagamer
 * Released under the MIT license.
 */

#include "Arduino.h"
#include "MPU6050.h"
#include "Wire.h"

MPU6050::MPU6050(uint8_t new_address) {
    address =nNew_address;

    // Wakeup the device
    Wire.begin();
    Wire.beginTransmission(address);
    Wire.write(PWR_MGMT_1);
    Wire.write(0);
    Wire.endTransmission();
}

/* Read a 16-bit signed value from the device by combining two following 1-byte registers*/ 
private int16_t MPU6050::read_i2c_word(uint8_t register_msb) {
    Wire.beginTransmission(address);
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

/* Write one byte to a specified register on the i2c device */
private void write_i2c_byte(uint8_t i2c_register, uint8_t cmd) {
    Wire.beginTransmission(address);
    Wire.write(i2c_register);
    Wire.write(cmd);
    Wire.endTransmission();
}

/* Read raw temperature and calculate real temperature in degrees Celcius */
public float readTemp() {
    int16_t rawTemp = read_i2c_word(TEMP_OUT0);
    return (rawTemp / 340) + 36.53;
}

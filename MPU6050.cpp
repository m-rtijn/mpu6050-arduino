/*
 * MPU6050.cpp - A library for using the MPU-6050 with Arduino.
 * Written by MrTijn/Tijndagamer
 * Copyright (c) 2016 MrTijn/Tijndagamer
 * Released under the MIT license.
 */

#include "MPU6050.h"

MPU6050::MPU6050(int address) {
    _address = address;
}

/* Resets the MPU-6050 to wake it up
 * Checks for succes by reading the PWR_MGMT_1 register and returns accordingly
 */
bool MPU6050::wakeup() {
    write_i2c_byte(PWR_MGMT_1, 0x00);

    if (read_i2c_byte(PWR_MGMT_1) == 0x00) {
        return true;
    } else {
        return false;
    }
}

/* Put the MPU-6050 into low power sleep mode
 * Checks for succes by reading the PWR_MGMT_1 register and returns accordingly
 */
bool MPU6050::sleep() {
    write_i2c_byte(PWR_MGMT_1, 0x20);

    if (read_i2c_byte(PWR_MGMT_1) == 0x20) {
        return true;
    } else {
        return false;
    }
}

/* Read a 16-bit signed value from the device by combining two following 1-byte registers */
int16_t MPU6050::read_i2c_word(uint8_t register_msb) {
    Wire.beginTransmission(_address);
    Wire.write(register_msb);
    // Don't release the bus to be able to read multiple values in one go
    Wire.endTransmission(false);
    Wire.requestFrom(_address, 2, true);

    int msb = Wire.read();
    int lsb = Wire.read();

    int16_t val = (msb << 8) + lsb;
    if (val >= 0x8000) {
        return -((65536 - val) + 1);
    } else {
        return val;
    }
}

int8_t MPU6050::read_i2c_byte(uint8_t i2c_register) {
    Wire.beginTransmission(_address);
    Wire.write(i2c_register);
    // Don't release the bus
    Wire.endTransmission(false);
    Wire.requestFrom(_address, 1, true);

    int8_t val = Wire.read();
    return val;
}

/* Write one byte to a specified register on the i2c device */
void MPU6050::write_i2c_byte(uint8_t i2c_register, uint8_t cmd) {
    Wire.beginTransmission(_address);
    Wire.write(i2c_register);
    Wire.write(cmd);
    Wire.endTransmission();
}

/* Read raw temperature and calculate real temperature in degrees Celcius */
float MPU6050::readTemp() {
    int16_t rawTemp = read_i2c_word(TEMP_OUT0);
    return (rawTemp / 340) + 36.53;
}

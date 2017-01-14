/*
 * MPU6050.cpp - A library for using the MPU-6050 with Arduino.
 * Written by MrTijn/Tijndagamer
 * Copyright (c) 2016 MrTijn/Tijndagamer
 * Released under the MIT license.
 */

#include "MPU6050.h"

MPU6050::MPU6050(int address) {
    _address = address;
    Wire.begin();
}

/*
 * General i2c methods
 */

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

/* Reads a signed 8-bit value from the device from the given register */
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

/*
 * Control methods
 */

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

/* Reset all used configuration registers */
void MPU6050::reset() {
    write_i2c_byte(ACCEL_CONFIG, 0x00);
    write_i2c_byte(GYRO_CONFIG, 0x00);
    write_i2c_byte(PWR_MGMT_1, 0x00);
}

/* Read raw temperature and calculate real temperature in degrees Celcius */
float MPU6050::readTemp() {
    int16_t rawTemp = read_i2c_word(TEMP_OUT0);
    return (rawTemp / 340) + 36.53;
}

/*
 * Accelerometer methods
 */

bool MPU6050::setAccelRange(uint8_t range) {
    write_i2c_byte(ACCEL_CONFIG, range);

    if (read_i2c_byte(ACCEL_CONFIG) == range) {
        return true;
    } else {
        return false;
    }
}

uint8_t MPU6050::getAccelRange() {
    return read_i2c_byte(ACCEL_CONFIG);
}

/* Returns the measured acceleration on the given axis in m/s^2
 * Returns -1 if an error occurred
 */
float MPU6050::readAccelAxis(char axis) {
    uint8_t i2c_register_msb = NULL;
    switch (axis) {
        case 'X':
            i2c_register_msb = ACCEL_XOUT0;
            break;
        case 'Y':
            i2c_register_msb = ACCEL_YOUT0;
            break;
        case 'Z':
            i2c_register_msb = ACCEL_ZOUT0;
            break;
        default:
            return -1;
    }

    float scale_modifier;
    uint8_t range = getAccelRange();
    switch (range) {
        case ACCEL_RANGE_2G:
            scale_modifier = ACCEL_SCALE_MODIFIER_2G;
            break;
        case ACCEL_RANGE_4G:
            scale_modifier = ACCEL_SCALE_MODIFIER_4G;
            break;
        case ACCEL_RANGE_8G:
            scale_modifier = ACCEL_SCALE_MODIFIER_8G;
            break;
        case ACCEL_RANGE_16G:
            scale_modifier = ACCEL_SCALE_MODIFIER_16G;
        default:
            return -1;
    }

    int16_t raw_data = read_i2c_word(i2c_register_msb);
    float acceleration = (raw_data / scale_modifier) * GRAVITY_MS2;
    return acceleration;
}

float MPU6050::readAccelX() {
    return readAccelAxis('X');
}

float MPU6050::readAccelY() {
    return readAccelAxis('Y');
}

float MPU6050::readAccelZ() {
    return readAccelAxis('Z');
}

/*
 * Gyroscope methods
 */

bool MPU6050::setGyroRange(uint8_t range) {
    write_i2c_byte(GYRO_CONFIG, range);

    if (read_i2c_byte(GYRO_CONFIG) == range) {
        return true;
    } else {
        return false;
    }
}

uint8_t MPU6050::getGyroRange() {
    return read_i2c_byte(GYRO_CONFIG);
}

/* Reads data from the gyroscope from the specified axis
 * Returns -1 if an error occured
 */
float MPU6050::readGyroAxis(char axis) {
    uint8_t i2c_register_msb = NULL;
    switch (axis) {
        case 'X':
            i2c_register_msb = GYRO_XOUT0;
            break;
        case 'Y':
            i2c_register_msb = GYRO_YOUT0;
            break;
        case 'Z':
            i2c_register_msb = GYRO_ZOUT0;
            break;
        default:
            return -1;
    }

    float scale_modifier;
    uint8_t range = getGyroRange();
    switch (range) {
        case GYRO_RANGE_250DEG:
            scale_modifier = GYRO_SCALE_MODIFIER_250DEG;
            break;
        case GYRO_RANGE_500DEG:
            scale_modifier = GYRO_SCALE_MODIFIER_500DEG;
            break;
        case GYRO_RANGE_1000DEG:
            scale_modifier = GYRO_SCALE_MODIFIER_1000DEG;
            break;
        case GYRO_RANGE_2000DEG:
            scale_modifier = GYRO_SCALE_MODIFIER_2000DEG;
            break;
        default:
            return -1;
    }

    int16_t raw_data = read_i2c_word(i2c_register_msb);
    float value = (raw_data / scale_modifier) * GRAVITY_MS2;
    return value;
}

float MPU6050::readGyroX() {
    return readGyroAxis('X');
}

float MPU6050::readGyroY() {
    return readGyroAxis('Y');
}

float MPU6050::readGyroZ() {
    return readGyroAxis('Z');
}

/*
 * MPU6050.h - A library for using the MPU-6050 with arduino.
 * Written by MrTijn/Tijndagamer
 * Copyright (c) 2016 MrTijn/Tijndagamer
 * Released under the MIT license
 */

#ifndef MPU6050_h
#define MPU6050_h

#include <Wire.h>
#include <Arduino.h>

class MPU6050 {
    public:
        MPU6050(int address = 0x68);

        // Control methods
        bool wakeup();
        bool sleep();
        void reset();

        // Configuration methods
        bool setAccelRange(uint8_t range);
        bool setGyroRange(uint8_t range);

        // Read methods
        float readTemp();

        float readAccelX();
        float readAccelY();
        float readAccelZ();

        float readGyroX();
        float readGyroY();
        float readGyroZ();

        uint8_t getAccelRange();
        uint8_t getGyroRange();

        // Ranges
        const uint8_t ACCEL_RANGE_2G = 0x00;
        const uint8_t ACCEL_RANGE_4G = 0x08;
        const uint8_t ACCEL_RANGE_8G = 0x10;
        const uint8_t ACCEL_RANGE_16G = 0x18;

        const uint8_t GYRO_RANGE_250DEG = 0x00;
        const uint8_t GYRO_RANGE_500DEG = 0x08;
        const uint8_t GYRO_RANGE_1000DEG = 0x10;
        const uint8_t GYRO_RANGE_2000DEG = 0x18;
    private:
        // Constants
        const float GRAVITY_MS2 = 9.80665;
        int _address;

        // Registers
        const uint8_t PWR_MGMT_1 = 0x6B;
        const uint8_t PWR_MGMT_2 = 0x6C;
        const uint8_t ACCEL_CONFIG = 0x1C;
        const uint8_t GYRO_CONFIG = 0x1B;

        const uint8_t ACCEL_XOUT0 = 0x3B;
        const uint8_t ACCEL_YOUT0 = 0x3D;
        const uint8_t ACCEL_ZOUT0 = 0x3F;

        const uint8_t GYRO_XOUT0 = 0x43;
        const uint8_t GYRO_YOUT0 = 0x45;
        const uint8_t GYRO_ZOUT0 = 0x48;

        const uint8_t TEMP_OUT0 = 0x41;

        // Scale modifiers
        const float ACCEL_SCALE_MODIFIER_2G = 16384.0;
        const float ACCEL_SCALE_MODIFIER_4G = 8192.0;
        const float ACCEL_SCALE_MODIFIER_8G = 4096.0;
        const float ACCEL_SCALE_MODIFIER_16G = 2048.0;

        const float GYRO_SCALE_MODIFIER_250DEG = 131.0;
        const float GYRO_SCALE_MODIFIER_500DEG = 65.5;
        const float GYRO_SCALE_MODIFIER_1000DEG = 32.8;
        const float GYRO_SCALE_MODIFIER_2000DEG = 16.4;

        // Internal methods
        int16_t read_i2c_word(uint8_t register_msb);
        int8_t read_i2c_byte(uint8_t i2c_register);
        void write_i2c_byte(uint8_t i2c_register, uint8_t cmd);
        float readAccelAxis(char axis);
        float readGyroAxis(char axis);
};

#endif

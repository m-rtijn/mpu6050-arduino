# mpu6050-arduino

A library for using the MPU-6050 digital accelerometer and gyroscope using Arduino-compatible devices.

# Usage

Before you can use this library in your Arduino project, you need to download and place this
repository in the library folder of your Arduino IDE. The location of the library folder depends on your system,
examples are `~/.arduino/libraries` and `~/.arduino17/libraries`.

To download the repository, use:
```
git clone https://github.com/Tijndagamer/mpu6050-arduino.git
```

Then move it to the correct folder. Now start your Arduino IDE and check if you can select "MPU6050" under
Sketch > Include Library > Contributed libraries. If you can't find the library, something went wrong during
the installation of the library. Check if you put the repository in the right folder to solve this issue.

To use the library in your project, include the library (Using the GUI or by adding `#include <MPU6050.h>` in
the source code) and declare an MPU6050 object outside all other code, like this:

```c
// Include statements

MPU6050 mpu6050;

void setup() {
    ...
```

The MPU6050 class allows for easy access to the sensor using the following seven methods:

```c
readTemp()
readAccelX()
readAccelY()
readAccelZ()
readGyroX()
readGyroY()
readGyroZ()
```

# Todo

Implement the more advanced features of the MPU-6050 sensor, such as changing the ranges of the accelerometer
and gyroscope.

# License

This repository is published under the MIT license. For more information, please refer to the LICENSE file.

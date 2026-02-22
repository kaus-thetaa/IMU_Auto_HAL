#ifndef MPU6050_H
#define MPU6050_H

#include "GenericIMU.h"
#include <Wire.h>

class MPU6050 : public GenericIMU {
  private:
    const uint8_t I2C_ADDR = 0x68;     // Default MPU6050 address, got it from the .h file
    const uint8_t PWR_MGMT_1 = 0x6B;   // Wake-up register, uthoooo
    const uint8_t ACCEL_OUT = 0x3B;    // Start of X, Y, Z data, the start bit, the other 5 bits for x,y,z will be followed by this one, so we can read all 6 bytes in one go.

  public:
    void begin() override;
    ImuData read() override;
};

#endif
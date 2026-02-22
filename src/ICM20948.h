#ifndef ICM20948_H
#define ICM20948_H

#include "GenericIMU.h"
#include <Wire.h>

class ICM20948 : public GenericIMU {
  private:
    const uint8_t I2C_ADDR = 0x69;      // Typical ICM-20948 address
    const uint8_t PWR_MGMT_1 = 0x06;    // Wake-up register
    const uint8_t ACCEL_XOUT_H = 0x2D;  // Start of X, Y, Z data

  public:
    void begin() override;
    ImuData read() override;
};

#endif
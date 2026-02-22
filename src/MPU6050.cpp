#include "MPU6050.h"

void MPU6050::begin() {
  Wire.beginTransmission(I2C_ADDR);
  Wire.write(PWR_MGMT_1);
  Wire.write(0x00); 
  Wire.endTransmission(true);
  delay(50);
}

ImuData MPU6050::read() {
  ImuData data;
  
  Wire.beginTransmission(I2C_ADDR);
  Wire.write(ACCEL_OUT); 
  Wire.endTransmission(false);
  Wire.requestFrom((uint8_t)I2C_ADDR, (uint8_t)6, (uint8_t)true);
  
  // 1. Get the raw 16-bit integer
  int16_t rawX = (Wire.read() << 8) | Wire.read();
  int16_t rawY = (Wire.read() << 8) | Wire.read();
  int16_t rawZ = (Wire.read() << 8) | Wire.read();
  
  // 2. Scale it! (Default +/- 2G range means 1G = 16384 ticks)
  // Dividing by a float (16384.0) turns the integer into a decimal
  data.x = rawX / 16384.0;
  data.y = rawY / 16384.0;
  data.z = rawZ / 16384.0;
  
  return data;
}
#include "ICM20948.h"

void ICM20948::begin() {
  Wire.beginTransmission(I2C_ADDR);
  Wire.write(PWR_MGMT_1);
  Wire.write(0x01); 
  Wire.endTransmission(true);
  delay(50);
}

ImuData ICM20948::read() {
  ImuData data;
  
  Wire.beginTransmission(I2C_ADDR);
  Wire.write(ACCEL_XOUT_H); 
  Wire.endTransmission(false);
  Wire.requestFrom((uint8_t)I2C_ADDR, (uint8_t)6, (uint8_t)true);
  
  int16_t rawX = (Wire.read() << 8) | Wire.read();
  int16_t rawY = (Wire.read() << 8) | Wire.read();
  int16_t rawZ = (Wire.read() << 8) | Wire.read();
  
  // Same scaling factor!
  data.x = rawX / 16384.0;
  data.y = rawY / 16384.0;
  data.z = rawZ / 16384.0;
  
  return data;
}
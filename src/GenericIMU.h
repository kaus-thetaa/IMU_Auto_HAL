#ifndef GENERIC_IMU_H
#define GENERIC_IMU_H

#include <Arduino.h>

// Updated to float to hold real-world decimal values (G-forces)
struct ImuData {
  float x;
  float y;
  float z;
};

class GenericIMU {
  public:
    virtual void begin() = 0;
    virtual ImuData read() = 0; 
};

#endif
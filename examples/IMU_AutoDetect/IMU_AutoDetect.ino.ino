#include <Wire.h>

//header files, self made, took ref from the OGs
#include "MPU6050.h"
#include "ICM20948.h"

//allocae memory in ram
MPU6050 mpuSensor;
ICM20948 icmSensor;

//create a polymornphic abract class, just a pointer, a null pointer, so it doenst have garbage value
GenericIMU* activeIMU = nullptr; 

//helpper funct, used during starup, to check get the who am i id
uint8_t checkWhoAmI(uint8_t i2cAddress, uint8_t registerAddress) {
  Wire.beginTransmission(i2cAddress);
  Wire.write(registerAddress);
  Wire.endTransmission(false);
  Wire.requestFrom(i2cAddress, (uint8_t)1);
  if (Wire.available()) {
    return Wire.read();
  }
  return 0; // 0, if no chip, or ded chip
}

void setup() {
  Serial.begin(9600);
  Wire.begin(); //boots up, arduino's pins

  Serial.println("Scanning I2C Bus for Avionics...");
  delay(1000);


  uint8_t mpuID = checkWhoAmI(0x68, 0x75);
  if (mpuID == 0x68) {
    Serial.println("SUCCESS: MPU6050 Detected!");
    activeIMU = &mpuSensor; // Point the boss to the MPU translator
  } 
  else {
    //If no MPU, ping the ICM-20948 (I2C Address: 0x69, WHO_AM_I Register: 0x00)
    uint8_t icmID = checkWhoAmI(0x69, 0x00);
    if (icmID == 0xEA) {
      Serial.println("SUCCESS: ICM-20948 Detected!");
      activeIMU = &icmSensor; //point tot he OG class, to the ICM specific
    }
  }

  if (activeIMU != nullptr) {
    // Whichever sensor was detected, boot it up using the Generic interface, made form the inheriteded class
    activeIMU->begin();
    Serial.println("IMU Initialized and Ready for Flight.");
  } else {
    Serial.println("ERROR: No valid IMU found. Check your wiring!");
    while (1); // Freeze the program here forever
  }
}

void loop() {
//will re4ad only if found
  if (activeIMU != nullptr) {
    
    
    ImuData currentData = activeIMU->read();

   
    Serial.print("Accel X: "); Serial.print(currentData.x); Serial.print(" G | ");
    Serial.print("Y: "); Serial.print(currentData.y); Serial.print(" G | ");
    Serial.print("Z: "); Serial.print(currentData.z); Serial.println(" G");
  }

  delay(100); 
}
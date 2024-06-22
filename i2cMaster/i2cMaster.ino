//ESP32WROOM

#include "Wire.h"
#define I2C_DEV_ADDR 0x55

uint8_t tInToSend = 46;
uint8_t tOutToSend = -12;
uint8_t setTempReceived = 0;

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Wire.begin();
}

void loop() {
  delay(1000);

  //Write message to the slave  
  Wire.beginTransmission(I2C_DEV_ADDR);
  Wire.write(tInToSend);
  Wire.write(tOutToSend);
  uint8_t error = Wire.endTransmission(true);

  //Read 8 bytes from the slave
  setTempReceived = 0;
  uint8_t bytesReceived = Wire.requestFrom(I2C_DEV_ADDR, 8);

  if ((bool)bytesReceived) {  
    setTempReceived = Wire.read(); 
    Serial.println(setTempReceived);
  }
} 

//ESP32S3
//This is not designed for end use. It's for people new to I2C to get an idea of what is going.

#include "Wire.h"

#define THIS_I2C_ADDRESS 0x55   // Address
#define SDA_PIN 21              // SDA Pin, if the defult is not used
#define SCL_PIN 33              // SCL Pin, if the defult is not used

uint8_t uint8_to_send = 45;     // Send a number - 0 to 255

/////////// WRITE TO MASTER ////////////////
void onRequest() 
{
   Wire.write(uint8_to_send);
}
////////// END WRITE TO THE MASTER ////////////

///////////// RECEIVE FROM MASTER /////////////
void onReceive(int len)
{ 
  uint8_t uint8_t_from_master = Wire.read();

  Serial.println(len);                  // Number of bytes received from Master
  Serial.println(uint8_t_from_master);  // uint8_t received from Master
}
///////////// END RECEIVE FROM MASTER /////////////

void setup()
 {
  Serial.begin(115200);                   // Start serial comunication at 115200 baud. Match the Serial Monitor to this.
  Wire.onReceive(onReceive);              // Initiate onReceive
  Wire.onRequest(onRequest);              // Initiate onReceive
  Wire.setPins(SDA_PIN,SCL_PIN);          // Set non defult pins
  Wire.begin((uint8_t)THIS_I2C_ADDRESS);  // Initiate I2C as slave.
}

void loop() {} //Nothing needed in loop

//ESP32S3

#include "Wire.h"

#define I2C_DEV_ADDR 0x55
#define SDA_PIN 21
#define SCL_PIN 33
#define uint8_High_Byte 7

uint8_t setTempToSendOut = 28;
int tIn = 0;
int tOut = 0;

//Write to the Master
void onRequest() 
{
   Wire1.write(setTempToSendOut);
}

//Read from the Master
void onReceive(int len)
{
  tOut = 0;
  tIn = Wire1.read();
  tOut = Wire1.read();

  tIn = FixSign(tIn);
  tOut = FixSign(tOut);

  Serial.println(tIn);
  Serial.println(tOut);
}

int FixSign (int x)
{
  int result;
   if ((bool)bitRead(x,uint8_High_Byte))  {result = x -256;}
  else  {result = x;}
  return result;
}

void setup()
 {
  Serial.begin(115200);
  Wire1.onReceive(onReceive);
  Wire1.onRequest(onRequest);
  Wire1.setPins(SDA_PIN,SCL_PIN);
  Wire1.begin((uint8_t)I2C_DEV_ADDR);
}

void loop() {}

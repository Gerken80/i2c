//GERKEN80
//ESP32WROOM
//This is not designed for end use. It's for people new to I2C to get an idea of what is going.

#include "Wire.h"                       // Use the Wire library. As this is for ESP32 it not identical to other Wire libraries
#define I2C_SLAVE_ADDRESS 0x55          // Address of Slave devive - Get this from the Slave
#define QUANTITY_BYTES_TO_RECEIVE 2     // 1 to 16
#define STOP true                       // true - Release the bus / false - keep the connection alive

uint8_t uint8_to_send = 46;             // Send a number - 0 and 255
uint8_t uint8_from_slave = 0;           // Receive a number - 0 to 255

void setup() {
  Serial.begin(115200);                 //Start serial comunication at 115200 baud. Match the Serial Monitor to this.
  Wire.begin();                         //Join the I2C bus as the Master
}

void loop() {
  delay(2000);                          //Pause for some time

  /*
  Write message to the slave;
  1. Set up communication between Master and Slave at 'I2C_SLAVE_ADDRESS'
  2. Write uint8_t to buffer for sending
  3. Data is sent when endTransmission is called.
  */

  /////////////////// WRITE TO SLAVE /////////////////////////////////////
  Wire.beginTransmission(I2C_SLAVE_ADDRESS);
  Wire.write(uint8_to_send);
  uint8_t error = Wire.endTransmission(true);
  //////////////////// END WRITE TO SLAVE ////////////////////////////////

  /*
  Read Bytes from the slave
  1. Reset 
  2. Request from Slave at defined address the following;
    a. Number of Bytes to receive
    b. Keep connection alive
  3. Read Bytes from the bus
  4. Print to Serial Monitor
  */
  //uint8_from_slave = 0;

  //////////////////////////////////// WRITE TO SLAVE //////////////////////////////////////////
  uint8_t bytesReceived = Wire.requestFrom(I2C_SLAVE_ADDRESS, QUANTITY_BYTES_TO_RECEIVE, STOP);
  uint8_t uint8_from_slave = Wire.read(); // Note below..

  Serial.println(bytesReceived);
  Serial.println(uint8_from_slave);
  ////////////////////////////////// END WRITE TO SLAVE /////////////////////////////////////////

  /*
  Note. 
  This line needs to be inside an if statement so junk data is not read when no Bytes were received.
  
  if ((bool) bytesReceived) {
    uint8_t uint8_from_slave = Wire.read();
    Do more stuff
  }
  */
} 

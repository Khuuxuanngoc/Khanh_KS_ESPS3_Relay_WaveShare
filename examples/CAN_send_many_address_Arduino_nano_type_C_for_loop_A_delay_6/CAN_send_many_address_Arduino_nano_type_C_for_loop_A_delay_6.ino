/* ESP32S3 RECEIVE
Message is in Standard Format

ID: 1
Byte: Data: 01 

Send back the received data!

Message queued for transmission
Alert: The Transmission was successful.

TX buffered: 0	 

Message is in Standard Format

ID: 0
Byte: Data: 00 

Send back the received data!

Message queued for transmission
Message is in Standard Format

ID: 3
Byte: Data: 03 

Send back the received data!

Message queued for transmission
Message is in Standard Format

ID: 2
Byte: Data: 02 

Send back the received data!

Message queued for transmission
Message is in Standard Format

ID: 5
Byte: Data: 05 

Send back the received data!

Message queued for transmission
Message is in Standard Format

ID: 4
Byte: Data: 04 

Send back the received data!

Message queued for transmission
Message is in Standard Format

ID: 7
Byte: Data: 07 

Send back the received data!

Message queued for transmission
Message is in Standard Format

ID: 6
Byte: Data: 06 

Send back the received data!

Message queued for transmission
Message is in Standard Format

ID: 9
Byte: Data: 09 

Send back the received data!

Message queued for transmission
Message is in Standard Format

ID: 8
Byte: Data: 08 

Send back the received data!

Message queued for transmission
Message is in Standard Format

ID: 11
Byte: Data: 11 

Send back the received data!

Message queued for transmission
Message is in Standard Format

ID: 10
Byte: Data: 10 

Send back the received data!

Message queued for transmission
Message is in Standard Format

ID: 13
Byte: Data: 13 

Send back the received data!

Message queued for transmission
Message is in Standard Format

ID: 12
Byte: Data: 12 

Send back the received data!

Message queued for transmission
Message is in Standard Format

ID: 15
Byte: Data: 15 

Send back the received data!

Message queued for transmission
Message is in Standard Format

ID: 14
Byte: Data: 14 

Send back the received data!

Message queued for transmission
Message is in Standard Format

ID: 17
Byte: Data: 17 

Send back the received data!

Message queued for transmission
Message is in Standard Format

ID: 16
Byte: Data: 16 

Send back the received data!

Message queued for transmission
Message is in Standard Format

ID: 19
Byte: Data: 19 

Send back the received data!

Message queued for transmission
Message is in Standard Format

ID: 18
Byte: Data: 18 

Send back the received data!

Message queued for transmission
Message is in Standard Format

ID: 21
Byte: Data: 21 

Send back the received data!

Message queued for transmission
Message is in Standard Format

ID: 20
Byte: Data: 20 

Send back the received data!

Message queued for transmission
Message is in Standard Format

ID: 23
Byte: Data: 23 

Send back the received data!

Message queued for transmission
Message is in Standard Format

ID: 22
Byte: Data: 22 

Send back the received data!

Message queued for transmission
Message is in Standard Format

ID: 25
Byte: Data: 25 

Send back the received data!

Message queued for transmission
Message is in Standard Format

ID: 24
Byte: Data: 24 

Send back the received data!

Message queued for transmission
Message is in Standard Format

ID: 27
Byte: Data: 27 

Send back the received data!

Message queued for transmission
Message is in Standard Format

ID: 26
Byte: Data: 26 

Send back the received data!

Message queued for transmission
Message is in Standard Format

ID: 29
Byte: Data: 29 

Send back the received data!

Message queued for transmission
Message is in Standard Format

ID: 28
Byte: Data: 28 

Send back the received data!

Message queued for transmission
Message is in Standard Format

ID: 30
Byte: Data: 30 

Send back the received data!

Message queued for transmission
Alert: The Transmission was successful.

TX buffered: 0	 

*/


#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMessage;
MCP2515 mcp2515(10);

uint8_t num = 0;
int testData = num; // Generate random numbers (from 1 to 99) to simulate sensor data

void setup() {
  while (!Serial);
  Serial.begin(115200);
  mcp2515.reset();
  mcp2515.setBitrate(CAN_250KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();

  delay(200);
  for (uint8_t i = 0; i<=30; i+=2) {
  
  // num++;
  testData = i; // Generate random numbers (from 1 to 99) to simulate sensor data

  canMessage.can_id  = i; // ID must be unique in a single CAN Bus network.
  canMessage.can_dlc = 1; // Data Length Code
  canMessage.data[0] = testData;
  mcp2515.sendMessage(&canMessage); // Send CAN messaage
  delay(6);
  }
  

}
void loop() {


}
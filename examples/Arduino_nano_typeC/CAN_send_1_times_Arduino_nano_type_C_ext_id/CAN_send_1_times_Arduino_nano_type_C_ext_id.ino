/* ESP32S3 RECEIVE

Message is in Standard Format

ID: 0 // send 2048 but not or with SRR bit
Byte: Data: 01 

Send back the received data!

Message queued for transmission
Alert: The Transmission was successful.

TX buffered: 0	 

Message is in Standard Format

ID: 2047 // send 2047. it is in range 0 ~ 2047 of standard format
Byte: Data: 01 

Send back the received data!

Message queued for transmission
Alert: The Transmission was successful.

TX buffered: 0	 

Message is in Extended Format

ID: 2048 // send canMessage.can_id  = 2048 | CAN_EFF_FLAG;
Byte: Data: 01 

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
void setup() {
  while (!Serial);
  Serial.begin(115200);
  mcp2515.reset();
  mcp2515.setBitrate(CAN_250KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();

  delay(200);
    num++;
  int testData = num; // Generate random numbers (from 1 to 99) to simulate sensor data

  //canMessage.can_id  = 2048; this id is extended id and must or with SRR bit to be understood by other devices. standard id is (0~2047)
  canMessage.can_id  = 2048 | CAN_EFF_FLAG; // ID must be unique in a single CAN Bus network.
  canMessage.can_dlc = 1; // Data Length Code
  canMessage.data[0] = testData;
  mcp2515.sendMessage(&canMessage); // Send CAN messaage


}
void loop() {


}
/* Reply form esp32s3
Message is in Standard Format

ID: 1
Byte: Data: 01 

Send back the received data!

Message queued for transmission
Message is in Standard Format

ID: 3
Byte: Data: 02 

Send back the received data!

Message queued for transmission
Message is in Standard Format

ID: 5
Byte: Data: 03 

Send back the received data!

Message queued for transmission
Message is in Standard Format

ID: 2
Byte: Data: 01 

Send back the received data!

Message queued for transmission
Message is in Standard Format

ID: 4
Byte: Data: 02 

Send back the received data!

Message queued for transmission
Message is in Standard Format

ID: 6
Byte: Data: 03 

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
    num++;
   testData = num; // Generate random numbers (from 1 to 99) to simulate sensor data

  canMessage.can_id  = 0x002; // ID must be unique in a single CAN Bus network.
  canMessage.can_dlc = 1; // Data Length Code
  canMessage.data[0] = testData;
  mcp2515.sendMessage(&canMessage); // Send CAN messaage
    num++;
   testData = num; // Generate random numbers (from 1 to 99) to simulate sensor data

  canMessage.can_id  = 0x004; // ID must be unique in a single CAN Bus network.
  canMessage.can_dlc = 1; // Data Length Code
  canMessage.data[0] = testData;
  mcp2515.sendMessage(&canMessage); // Send CAN messaage
      num++;
   testData = num; // Generate random numbers (from 1 to 99) to simulate sensor data

  canMessage.can_id  = 0x006; // ID must be unique in a single CAN Bus network.
  canMessage.can_dlc = 1; // Data Length Code
  canMessage.data[0] = testData;
  mcp2515.sendMessage(&canMessage); // Send CAN messaage

}
void loop() {


}
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
  for (uint8_t i = 1; i<=30; i+=2) {
  
  // num++;
  testData = i; // Generate random numbers (from 1 to 99) to simulate sensor data

  canMessage.can_id  = i; // ID must be unique in a single CAN Bus network.
  canMessage.can_dlc = 1; // Data Length Code
  canMessage.data[0] = testData;
  mcp2515.sendMessage(&canMessage); // Send CAN messaage
  }
  

}
void loop() {


}
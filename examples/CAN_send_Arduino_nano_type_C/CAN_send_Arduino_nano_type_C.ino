#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMessage;
MCP2515 mcp2515(10);

void setup() {
  while (!Serial);
  Serial.begin(115200);
  mcp2515.reset();
  mcp2515.setBitrate(CAN_250KBPS);
  mcp2515.setNormalMode();
}
uint8_t num = 0;
void loop() {
  num++;
  int testData = num; // Generate random numbers (from 1 to 99) to simulate sensor data

  canMessage.can_id  = 0x001; // ID must be unique in a single CAN Bus network.
  canMessage.can_dlc = 1; // Data Length Code
  canMessage.data[0] = testData;
  mcp2515.sendMessage(&canMessage); // Send CAN messaage

  delay(200);
}
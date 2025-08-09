#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMessage;
struct can_frame canMessage2;

MCP2515 mcp2515(10);

void setup() {
  Serial.begin(115200);
  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS);
  mcp2515.setNormalMode();
}

void loop() {
  if (mcp2515.readMessage(&canMessage) == MCP2515::ERROR_OK) {
    Serial.println("CAN_ID" + String(canMessage.can_id) + ":" + String(canMessage.data[0]) + String(canMessage.data[1]) + String(canMessage.data[2]) + String(canMessage.data[3]) + String(canMessage.data[4]) + String(canMessage.data[5]) + String(canMessage.data[6]) + String(canMessage.data[7])); // Print CAN ID and CAN data
  }
  //   if (mcp2515.readMessage(&canMessage2) == MCP2515::ERROR_OK) {
  //   Serial.println("CAN_ID" + String(canMessage2.can_id) + ":" + String(canMessage2.data[0]) + String(canMessage2.data[1]) + String(canMessage2.data[2]) + String(canMessage2.data[3]) + String(canMessage2.data[4]) + String(canMessage2.data[5]) + String(canMessage2.data[6]) + String(canMessage2.data[7])); // Print CAN ID and CAN data
  // }
}

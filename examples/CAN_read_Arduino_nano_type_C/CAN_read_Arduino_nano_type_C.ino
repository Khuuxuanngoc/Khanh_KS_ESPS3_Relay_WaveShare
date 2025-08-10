#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMessage;
struct can_frame canMessage2;

MCP2515 mcp2515(10);

void setup() {
  Serial.begin(115200);
  mcp2515.reset();
  mcp2515.setBitrate(CAN_250KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();
  // mcp2515.setListenOnlyMode();
}

void loop() {
  // if (mcp2515.readMessage(&canMessage) == MCP2515::ERROR_OK) {
  //   Serial.println("CAN_ID" + String(canMessage.can_id) + ":" + String(canMessage.data[0]) + String(canMessage.data[1]) + String(canMessage.data[2]) + String(canMessage.data[3]) + String(canMessage.data[4]) + String(canMessage.data[5]) + String(canMessage.data[6]) + String(canMessage.data[7])); // Print CAN ID and CAN data
  // }
    if (mcp2515.readMessage(&canMessage) == MCP2515::ERROR_OK) {
    Serial.print("\nCAN_ID: ");
    Serial.print(canMessage.can_id,HEX);
    Serial.print(": ");
    for(uint8_t i = 0; i<8; i++)
    {
      Serial.print(String(canMessage.data[i]));
      Serial.print(' ');// Print CAN ID and CAN data
  }
    }
  //   if (mcp2515.readMessage(&canMessage2) == MCP2515::ERROR_OK) {
  //   Serial.println("CAN_ID" + String(canMessage2.can_id) + ":" + String(canMessage2.data[0]) + String(canMessage2.data[1]) + String(canMessage2.data[2]) + String(canMessage2.data[3]) + String(canMessage2.data[4]) + String(canMessage2.data[5]) + String(canMessage2.data[6]) + String(canMessage2.data[7])); // Print CAN ID and CAN data
  // }
//   auto err = mcp2515.readMessage(&canMessage);
// if (err == MCP2515::ERROR_OK) {
//   // nhận thành công
//   Serial.println("CAN_ID" + String(canMessage.can_id) + ":" + String(canMessage.data[0]) + String(canMessage.data[1]) + String(canMessage.data[2]) + String(canMessage.data[3]) + String(canMessage.data[4]) + String(canMessage.data[5]) + String(canMessage.data[6]) + String(canMessage.data[7])); // Print CAN ID and CAN data
// } else {
//   Serial.println("CAN read error: " + String(err));
// }

// uint8_t status = mcp2515.getStatus();
// Serial.print("MCP2515 Status: ");
// Serial.println(status, HEX);
// if (canMessage.can_dlc == 8) {
//   if (canMessage.data[0] == 0xAA && canMessage.data[7] == 0x55) {
    // Serial.println(mcp2515.checkReceive());
//   }
// }


delay(200);
}

/* ESP32S3 RECEIVE 
Message is in Extended Format

ID: 448998645
Byte: Data: 03 65 17 33 00 56 00 255 

Send back the received data!

Message queued for transmission
Message is in Extended Format

ID: 2659
Byte: Data: 99 73 17 34 00 00 56 00 

Send back the received data!

Message queued for transmission
Message is in Standard Format

ID: 35
Byte: Data: 03 65 17 51 00 00 00 56 

Send back the received data!

Message queued for transmission
Message is in Standard Format

ID: 85
Byte: Data: 03 68 49 83 00 56 00 00 

Send back the received data!

Message queued for transmission
Message is in Standard Format

ID: 421
Byte: Data: 03 65 17 57 00 00 00 00 

Send back the received data!

Message queued for transmission
*/

/*
This is simple example to send random data to CAN bus in 20Hz rate, using delay (not recommended in real implementations).
*/

// Lưu ý không được kết nối cổng usb, nếu không CAN bus 2 chân 11 12 sẽ bị lỗi

#include "STM32_CAN.h"
STM32_CAN Can( CAN1, DEF );  //Use PA11/12 pins for CAN1.
// STM32_CAN Can( CAN1, ALT );  //Use PB8/9 pins for CAN1.
//STM32_CAN Can( CAN1, ALT_2 );  //Use PD0/1 pins for CAN1.
//STM32_CAN Can( CAN2, DEF );  //Use PB12/13 pins for CAN2.
//STM32_CAN Can( CAN2, ALT );  //Use PB5/6 pins for CAN2
//STM32_CAN Can( CAN3, DEF );  //Use PA8/15 pins for CAN3.
//STM32_CAN Can( CAN3, ALT );  //Use PB3/4 pins for CAN3

static CAN_message_t CAN_TX_msg;

void setup() {
  Serial.begin(115200);
  Can.begin();
  Can.setBaudRate(250000);  //250KBPS
  Can.setMode(STM32_CAN::NORMAL);
  // Can.setBaudRate(500000);  //500KBPS
  //Can.setBaudRate(1000000);  //1000KBPS
}

void loop() {
  uint8_t Counter = 0;
  while(1){
    if (Counter > 255){ Counter = 0;}
    delay(50);
    CAN_TX_msg.id = (0x1A5);
    CAN_TX_msg.len = 8;
    CAN_TX_msg.buf[0] =  0x03;
    CAN_TX_msg.buf[1] =  0x41;
    CAN_TX_msg.buf[2] =  0x11;
    CAN_TX_msg.buf[3] =  Counter;
    CAN_TX_msg.buf[4] =  0x00;
    CAN_TX_msg.buf[5] =  0x00;
    CAN_TX_msg.buf[6] =  0x00;
    CAN_TX_msg.buf[7] =  0x00;
  
    Can.write(CAN_TX_msg);

    CAN_TX_msg.id = (0x1AC32CF5);
    CAN_TX_msg.flags.extended = 1;  // To enable extended ID.
    CAN_TX_msg.len = 8;
    CAN_TX_msg.buf[0] =  0x03;
    CAN_TX_msg.buf[1] =  0x41;
    CAN_TX_msg.buf[3] =  0x21;
    CAN_TX_msg.buf[4] =  0x00;
    CAN_TX_msg.buf[5] =  Counter;
    CAN_TX_msg.buf[6] =  0x00;
    CAN_TX_msg.buf[7] =  0xFF;

    Can.write(CAN_TX_msg);

    CAN_TX_msg.id = (0xA63);
    CAN_TX_msg.len = 8;
    CAN_TX_msg.buf[0] =  0x63;
    CAN_TX_msg.buf[1] =  0x49;
    CAN_TX_msg.buf[2] =  0x11;
    CAN_TX_msg.buf[3] =  0x22;
    CAN_TX_msg.buf[4] =  0x00;
    CAN_TX_msg.buf[5] =  0x00;
    CAN_TX_msg.buf[6] =  Counter;
    CAN_TX_msg.buf[7] =  0x00;

    Can.write(CAN_TX_msg);

    CAN_TX_msg.id = (0x23);
    CAN_TX_msg.flags.extended = 0;  // Back to standard ID.
    CAN_TX_msg.len = 8;
    CAN_TX_msg.buf[0] =  0x03;
    CAN_TX_msg.buf[1] =  0x41;
    CAN_TX_msg.buf[2] =  0x11;
    CAN_TX_msg.buf[3] =  0x33;
    CAN_TX_msg.buf[4] =  0x00;
    CAN_TX_msg.buf[5] =  0x00;
    CAN_TX_msg.buf[6] =  0x00;
    CAN_TX_msg.buf[7] =  Counter;

    Can.write(CAN_TX_msg);

    CAN_TX_msg.id = (0x55);
    CAN_TX_msg.len = 8;
    CAN_TX_msg.buf[0] =  0x03;
    CAN_TX_msg.buf[1] =  0x44;
    CAN_TX_msg.buf[2] =  0x31;
    CAN_TX_msg.buf[3] =  0x53;
    CAN_TX_msg.buf[4] =  0x00;
    CAN_TX_msg.buf[5] =  Counter;
    CAN_TX_msg.buf[6] =  0x00;
    CAN_TX_msg.buf[7] =  0x00;

    Can.write(CAN_TX_msg);
    Serial.print("Sent: ");
    Serial.println(Counter, HEX);
    Counter++;
  }
}

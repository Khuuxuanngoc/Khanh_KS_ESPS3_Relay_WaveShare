#pragma once

#define Extension_Enable      1                   // Whether to extend the connection to external devices     1:Expansion device Modbus RTU Relay     0:No extend
#define RS485_CAN_Enable      0                   // This item is configured according to product selection   1:Select RS485                          0:Select CAN
#define RTC_Event_Enable      1                   // Whether to enable RTC events  (Bluetooth)                1:Enable                                0:Disable



// Name and password of the WiFi access point
#define STASSID       "khanh"
#define STAPSK        "12345678"

// Details about devices on the Waveshare cloud
#define MQTT_Server   "mqtt.waveshare.cloud"
#define MQTT_Port     1883
#define MQTT_ID       "5fb00833"
#define MQTT_Pub      "Pub/1123/54/5fb00833"
#define MQTT_Sub      "Sub/1123/54/5fb00833"

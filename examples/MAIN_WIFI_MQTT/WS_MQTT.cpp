#include "WS_MQTT.h"

// The name and password of the WiFi access point
const char* ssid = STASSID;
const char* password = STAPSK;
// Details about devices on the Waveshare cloud
const char* mqtt_server = MQTT_Server;
int PORT = MQTT_Port;
const char* ID = MQTT_ID;   // Defining device ID
char pub[] = MQTT_Pub;      // MQTT release topic
char sub[] = MQTT_Sub;      // MQTT subscribe to topics


WiFiClient espClient;       //MQTT initializes the contents
PubSubClient client(espClient);

StaticJsonDocument<400> sendJson;
StaticJsonDocument<400> readJson;
unsigned long lastUpdateTime = 0;
char msg[MSG_BUFFER_SIZE];
bool WIFI_Connection = 0;
bool WIFI_Connection_Old = 0;
char ipStr[16];

const unsigned long updateInterval = 5000;

void WIFI_Init(void)
{
  xTaskCreatePinnedToCore(
    WifiStaTask,    
    "WifiStaTask",   
    4096,                
    NULL,                 
    3,                   
    NULL,                 
    0                   
  );
}


void WifiStaTask(void *parameter) {
  uint8_t Count = 0;
  WiFi.mode(WIFI_STA);                                   
  WiFi.setSleep(true);      
  WiFi.begin(ssid, password);                         // Connect to the specified Wi-Fi network
  while(1){
    if(WiFi.status() != WL_CONNECTED)
    {
      WIFI_Connection = 0;
      printf(".\n");  
      RGB_Open_Time(50, 0, 0, 500, 0); 
      Count++;
      if(Count >= 10){
        Count = 0;
        printf("\r\n"); 
        WiFi.disconnect();
        vTaskDelay(pdMS_TO_TICKS(100));
        WiFi.mode(WIFI_OFF);
        vTaskDelay(pdMS_TO_TICKS(100));
        WiFi.mode(WIFI_STA);
        vTaskDelay(pdMS_TO_TICKS(100));
        WiFi.begin(ssid, password);
      }
    }
    else{
      WIFI_Connection = 1;
      IPAddress myIP = WiFi.localIP();
      printf("IP Address: ");
      sprintf(ipStr, "%d.%d.%d.%d", myIP[0], myIP[1], myIP[2], myIP[3]);
      printf("%s\r\n", ipStr);
      RGB_Open_Time(0, 50, 0, 1000, 0); 
    
      printf("WIFI connection is successful, relay control can be performed via Waveshare cloud.\r\n");

      while (WiFi.status() == WL_CONNECTED){
        vTaskDelay(pdMS_TO_TICKS(100));
      }
    }
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
  vTaskDelete(NULL);
}

// MQTT subscribes to callback functions for processing received messages
void callback(char* topic, byte* payload, unsigned int length) {  
  uint8_t CH_Flag = 0;
  String inputString;
  for (int i = 0; i < length; i++) {
    inputString += (char)payload[i];
  }
  printf("%s\r\n",inputString.c_str());                                     // Format of data sent back by the server {"data":{"CH1":1}}
  int dataBegin = inputString.indexOf("\"data\"");                          // Finds if "data" is present in the string (quotes also)
  if (dataBegin == -1) {
    printf("Missing 'data' field in JSON. - MQTT\r\n");                     
    return;
  }
  int CH_Begin = -1;      
  if (inputString.indexOf("\"CH1\"", dataBegin) != -1){                     
    CH_Flag = 1;
    CH_Begin = inputString.indexOf("\"CH1\"", dataBegin);
  }
  else if (inputString.indexOf("\"CH2\"", dataBegin) != -1){             
    CH_Flag = 2;
    CH_Begin = inputString.indexOf("\"CH2\"", dataBegin);
  }  
  else if (inputString.indexOf("\"CH3\"", dataBegin) != -1){             
    CH_Flag = 3;
    CH_Begin = inputString.indexOf("\"CH3\"", dataBegin);
  }  
  else if (inputString.indexOf("\"CH4\"", dataBegin) != -1){             
    CH_Flag = 4;
    CH_Begin = inputString.indexOf("\"CH4\"", dataBegin);
  }  
  else if (inputString.indexOf("\"CH5\"", dataBegin) != -1){             
    CH_Flag = 5;
    CH_Begin = inputString.indexOf("\"CH5\"", dataBegin);
  }   
  else if (inputString.indexOf("\"CH6\"", dataBegin) != -1){             
    CH_Flag = 6;
    CH_Begin = inputString.indexOf("\"CH6\"", dataBegin);
  }   
  else if (inputString.indexOf("\"CH7\"", dataBegin) != -1){             
    CH_Flag = 7;
    CH_Begin = inputString.indexOf("\"CH7\"", dataBegin);
  }   
  else if (inputString.indexOf("\"CH8\"", dataBegin) != -1){             
    CH_Flag = 8;
    CH_Begin = inputString.indexOf("\"CH8\"", dataBegin);
  }   
  else if (inputString.indexOf("\"ALL\"", dataBegin) != -1){             
    CH_Flag = 9;
    CH_Begin = inputString.indexOf("\"ALL\"", dataBegin);
  }   
  else{
    printf("Note : Non-instruction data was received - MQTT!\r\n");
    CH_Flag = 0;
    return;
  }
  int valueBegin = inputString.indexOf(':', CH_Begin);
  int valueEnd = inputString.indexOf('}', valueBegin);
  if (valueBegin != -1 && valueEnd != -1) {
    if(CH_Flag != 0)
    {
      String ValueStr = inputString.substring(valueBegin + 1, valueEnd);
      int Value = ValueStr.toInt();
      if(CH_Flag < 9){
        if(Value == 1 && Relay_Flag[CH_Flag - 1] == 0){
          uint8_t Data[1]={CH_Flag+48};
          Relay_Analysis(Data,MQTT_Mode);
        }
        else if(Value == 0 && Relay_Flag[CH_Flag - 1] == 1){
          uint8_t Data[1]={CH_Flag+48};
          Relay_Analysis(Data,MQTT_Mode);
        }
      }
      else if(CH_Flag == 9){
        if(Value == 1 && ((Relay_Flag[0] & Relay_Flag[1] & Relay_Flag[2] & Relay_Flag[3] & Relay_Flag[4] & Relay_Flag[5] & Relay_Flag[6] & Relay_Flag[7]) == 0)){
          uint8_t Data[1]={9+48};
          Relay_Analysis(Data,MQTT_Mode);
        }
        else if(Value == 0 && ((Relay_Flag[0] | Relay_Flag[1] | Relay_Flag[2] | Relay_Flag[3] | Relay_Flag[4] | Relay_Flag[5] | Relay_Flag[6] | Relay_Flag[7] )== 1)){
          uint8_t Data[1]={0+48};
          Relay_Analysis(Data,MQTT_Mode);
        }
      }
    }
  }
}


// Reconnect to the MQTT server
void reconnect(void) {
  uint8_t Count = 0;
  while (!client.connected()) {
    Count++;    
    if (client.connect(ID)) {
      client.subscribe(sub);
      printf("Waveshare Cloud connection is successful and now you can use all features.\r\n"); 
    } 
    else{
      delay(500);
      if(Count % 2 == 0 && Count != 0){ 
        printf("%d\r\n", client.state());      
        RGB_Open_Time(50, 0, 50, 1000, 0); 
      } 
      if(Count % 10 == 0){                               // 10 attempts failed to connect, cancel the connection, try again
        client.disconnect();
        delay(100);
        client.setServer(mqtt_server, PORT);
        delay(100);
        client.setCallback(callback);
        delay(100);
      }
      if(Count > 32){                                   // connection fail
        Count = 0;
        printf("warning: Waveshare cloud connection fails. Currently, only Bluetooth control is available !!!\r\n"); 
      } 

    }
  }
}
// Send data in JSON format to MQTT server
void sendJsonData(void) {
  sendJson["ID"] = ID;
  String pubres;
  serializeJson(sendJson, pubres);
  int str_len = pubres.length() + 1;
  char char_array[str_len];
  pubres.toCharArray(char_array, str_len);
  client.publish(pub, char_array);
}

void MQTTTask(void *parameter) {
  bool WIFI_Connection_Old;
  while(1){
    if(WIFI_Connection == 1)
    { 
      if(!WIFI_Connection_Old){
        WIFI_Connection_Old = 1;
        client.setServer(mqtt_server, PORT);
        client.setCallback(callback);
      }
      if (!client.connected()) {
        reconnect();
      }
      client.loop();
    }
    else{
      WIFI_Connection_Old = 0;
    }
    vTaskDelay(pdMS_TO_TICKS(10));
  }
  vTaskDelete(NULL);
}
void MQTT_Init(void)
{
  WIFI_Init();
  xTaskCreatePinnedToCore(
    MQTTTask,    
    "MQTTTask",   
    4096,                
    NULL,                 
    3,                   
    NULL,                 
    0                   
  );
}


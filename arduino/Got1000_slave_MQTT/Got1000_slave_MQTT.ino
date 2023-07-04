#include <WiFi.h>
#include "PubSubClient.h"
#include <ArduinoOTA.h>
#include <FS.h>
#include <EEPROM.h>
#include <ArduinoJson.h>
#include "ModbusRtu.h"
#include <esp_task_wdt.h>
#include <iostream>
#include <string>
#define WDT_TIMEOUT 300

#ifdef ESP32
#include <SPIFFS.h>
#endif

#define led_connection 42
#define led_published 41

const char* ssid = "MIC_2.4GHz";
const char* password = "999999999";
const char* mqtt_server = "192.168.100.164";

//////////////////////SETUP/////////////////////////
IPAddress local_IP(192, 168, 100, 150); // Static IP address192.168.100.164
IPAddress gateway(192, 168, 100, 1);    // Gateway IP address
IPAddress subnet(255, 255, 255, 0);     // subnet

char Machine_no[] = "TB01";
//////////////////////SETUP/////////////////////////

WiFiClient espClient;
PubSubClient client(espClient);

Modbus slave(1, Serial1, 0);

int8_t state = 0;

int count_connection;

void setup_wifi() 
{
  esp_task_wdt_reset();
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.config(local_IP, gateway, subnet);
  //WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) 
  {
    esp_task_wdt_reset();
    count_connection++;
    digitalWrite(led_connection, HIGH);delay(100);digitalWrite(led_connection, LOW);delay(100);  
    Serial.print(".");
    if(count_connection>20)
    {
      ESP.restart();
    }
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) 
{
  esp_task_wdt_reset();
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    //digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  } else {
    //digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}

int timeout ;

void reconnect() 
{
  esp_task_wdt_reset();
  // Loop until we're reconnected
  while(!client.connected()) 
  {
    digitalWrite(led_connection, HIGH);  
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      //client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      //delay(5000);
      digitalWrite(led_connection, HIGH);delay(300);digitalWrite(led_connection, LOW);delay(300);    
      timeout++;
      if(timeout >= 10)
      {
        ESP.restart();
      }
    }
  }
}

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  esp_task_wdt_init(WDT_TIMEOUT, true); 
  esp_task_wdt_add(NULL);
  esp_task_wdt_reset();
  pinMode ( led_connection , OUTPUT);
  pinMode ( led_published, OUTPUT);
  Serial.println("Booting");
  setup_wifi();

  ArduinoOTA.setHostname(Machine_no);

  // No authentication by default
  ArduinoOTA.setPassword("1234");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("Start updating " + type);
    })
    .onEnd([]() {
      Serial.println("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });

  ArduinoOTA.begin();

  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback); 
  slave.start();
}

String rssi,d200,d201,d202,d203,d204,d205,d206,d207,d208,d209,d210,d211,d212,d213,d214,d215,d216,d217,d218,d219; // Add register ,d206,…….n;
char r[16],d0[16],d1[16],d2[16],d3[16],d4[16],d5[16],d6[16],d7[16],d8[16],d9[16],d10[16],d11[16],d12[16],d13[16],d14[16],d15[16],d16[16],d17[16],d18[16],d19[16]; // Add register ,d6[16],…….n;
int num = 20; //number of registers


void loop()
{
  ArduinoOTA.handle();
  uint16_t Data[num];
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();
  esp_task_wdt_reset();
  state = slave.poll( Data, num );
  
  if (state == 7) 
  {
    Serial.print("-----Reading ------- : ");
  }
  
  if (state == 8)
  {
    Serial.println("\n---------------starting loop----------------");
    for (int i = 0; i < (num * 2); i++)
    {
      slave.poll( Data, num );
      delay(100);
    }
    esp_task_wdt_reset();
    String rssi = String(WiFi.RSSI());
    d200 = String(Data[0]);
    d201 = String(Data[1]);
    d202 = String(Data[2]);
    d203 = String(Data[3]);
    d204 = String(Data[4]);
    d205 = String(Data[5]);
    d206 = String(Data[6]);
    d207 = String(Data[7]);
    d208 = String(Data[8]);
    d209 = String(Data[9]);
    d210 = String(Data[10]);
    d211 = String(Data[11]);
    d212 = String(Data[12]);
    d213 = String(Data[13]);
    d214 = String(Data[14]);
    d215 = String(Data[15]);
    d216 = String(Data[16]);
    d217 = String(Data[17]);
    d218 = String(Data[18]);
    d219 = String(Data[19]);

    esp_task_wdt_reset();
    digitalWrite(led_published, LOW);delay(500);digitalWrite(led_published, HIGH);delay(500);

    Serial.print("RSSI : "); Serial.println(rssi);
    Serial.print("1.D200 : "); Serial.println(d200);
    Serial.print("2.D201 : "); Serial.println(d201);
    Serial.print("3.D202 : "); Serial.println(d202);
    Serial.print("4.D203 : "); Serial.println(d203);
    Serial.print("5.D204 : "); Serial.println(d204);
    Serial.print("6.D205 : "); Serial.println(d205);
    Serial.print("7.D206 : "); Serial.println(d206);
    Serial.print("8.D207 : "); Serial.println(d207);
    Serial.print("9.D208 : "); Serial.println(d208);
    Serial.print("10.D209 : "); Serial.println(d209);
    Serial.print("11.D210 : "); Serial.println(d210);
    Serial.print("12.D211 : "); Serial.println(d211);
    Serial.print("13.D212 : "); Serial.println(d212);
    Serial.print("14.D213 : "); Serial.println(d213);
    Serial.print("15.D214 : "); Serial.println(d214);
    Serial.print("16.D215 : "); Serial.println(d215);
    Serial.print("17.D216 : "); Serial.println(d216);
    Serial.print("18.D217 : "); Serial.println(d217);
    Serial.print("19.D218 : "); Serial.println(d218);
    Serial.print("20.D219 : "); Serial.println(d219);

  esp_task_wdt_reset();
    // สร้าง JSON object
  StaticJsonDocument<5000> doc;
  doc["TB01/D200"] = d200;
  doc["TB01/D201"] = d201;
  doc["TB01/D202"] = d202;
  doc["TB01/D203"] = d203;
  doc["TB01/D204"] = d204;
  doc["TB01/D205"] = d205;
  doc["TB01/D206"] = d206;
  doc["TB01/D207"] = d207;
  doc["TB01/D208"] = d208;
  doc["TB01/D209"] = d209;
  doc["TB01/D210"] = d210;
  doc["TB01/D211"] = d211;
  doc["TB01/D212"] = d212;
  doc["TB01/D213"] = d213;
  doc["TB01/D214"] = d214;
  doc["TB01/D215"] = d215;
  doc["TB01/D216"] = d216;
  doc["TB01/D217"] = d217;
  doc["TB01/D218"] = d218;
  doc["TB01/D219"] = d219;
  
  // แปลง JSON object เป็น string
  String jsonStr;
  serializeJson(doc, jsonStr);

  // ส่งข้อมูลผ่าน MQTT
  client.publish("MBRC01/json1", jsonStr.c_str());
  Serial.println(jsonStr);

    
    Serial.println("\n---------------finish loop------------------\n\n");
    delay(5000);
  }

}

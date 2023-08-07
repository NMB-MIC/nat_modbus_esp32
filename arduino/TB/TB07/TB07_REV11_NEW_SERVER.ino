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

  const char* ssid = "MIC-IIoT-1";
  const char* password = "natmms22";
  //const char* ssid = "TP-Link_2B32";
  //const char* password = "58252017";
  const char* mqtt_server = "10.128.16.10"; //IP Server

//////////////////////SETUP/////////////////////////
IPAddress local_IP(10, 128, 48, 17); // Static IP address192.168.100.164
IPAddress gateway(10, 128, 48, 1);    // Gateway IP address
IPAddress subnet(255, 255, 254, 0);     // subnet
char Machine_no[] = "TB07"; //Machine name
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
    digitalWrite(led_connection, HIGH); delay(100); digitalWrite(led_connection, LOW); delay(100);
    Serial.print(".");
    if (count_connection > 20)
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
  while (!client.connected())
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
      digitalWrite(led_connection, HIGH); delay(300); digitalWrite(led_connection, LOW); delay(300);
      timeout++;
      if (timeout >= 10)
      {
        ESP.restart();
      }
    }
  }
}

void setup()
{
  Serial.begin(500000);
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

String rssi, M34, M36, D330, D332, D334, D336, D338, D340, D342, D344, D346, D348, D350, D226, D100, D102, D104, D106, D108, D110, D112, D114, D362, D364, D368, D370, D356, D372, D354, D366, D116, D122, D126, D128, D118, D120, D124, D286, D32;

//char d_rssi[16], d1[16], d2[16], d3[16], d4[16], d5[16], d6[16], d7[16], d8[16], d9[16], d10[16], d11[16], d12[16], d13[16], d14[16], d15[16], d16[16], d17[16], d18[16], d19[16], d20[16], d21[16], d22[16], d23[16], d24[16], d25[16], d26[16], d27[16], d28[16], d29[16], d30[16], d31[16];

//////////////เพิ่มเติม////////////////////////////
const int num = 47;   //จำนวน Register
uint16_t Data[num];
unsigned long previousMillis = 0;
unsigned long tempus = 0;
const unsigned long interval = 10000; //เวลาในการส่ง Data
//////////////เพิ่มเติม////////////////////////////

void loop()
{
  ArduinoOTA.handle();
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();
  esp_task_wdt_reset();
  state = slave.poll( Data, num );
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval && state == 8)
  {
    Serial.println("\n---------------starting loop----------------");
    previousMillis = currentMillis;
    esp_task_wdt_reset();
    String rssi = String(WiFi.RSSI());

    ///////////////////////////////////////////////////
    M34 = String(Data[0]);   Serial.print("MODEL_1R : ");                   Serial.println(M34);
    M36 = String(Data[1]);   Serial.print("MODEL_2R : ");                   Serial.println(M36);
    D330 = String(Data[2]);  Serial.print("FORMING_1R : ");                 Serial.println(D330);
    D332 = String(Data[3]);  Serial.print("FACING_BIT_1R : ");              Serial.println(D332);
    D334 = String(Data[4]);  Serial.print("RECESS1_1R : ");                 Serial.println(D334);
    D336 = String(Data[5]);  Serial.print("CUTOUT1_1R : ");                 Serial.println(D336);
    D338 = String(Data[6]);  Serial.print("RECESS2_1R : ");                 Serial.println(D338);
    D340 = String(Data[7]);  Serial.print("CUTOUT2_1R : ");                 Serial.println(D340);
    D342 = String(Data[8]);  Serial.print("DRILL_1R : ");                   Serial.println(D342);
    D344 = String(Data[9]);  Serial.print("PARTCHECK_1R : ");               Serial.println(D344);
    D346 = String(Data[10]); Serial.print("PRODUCITON_BAR : ");             Serial.println(D346);
    D348 = String(Data[11]); Serial.print("OD_BIT_1R : ");                  Serial.println(D348);
    D350 = String(Data[12]); Serial.print("PRODUCTION_2R : ");              Serial.println(D350);
    D226 = String(Data[13]); Serial.print("CT : ");                         Serial.println(D226);
    D100 = String(Data[14]); Serial.print("USAGE_FORMING_1R : ");           Serial.println(D100);
    D102 = String(Data[15]); Serial.print("USAGE_FACING_BIT_1R : ");        Serial.println(D102);
    D104 = String(Data[16]); Serial.print("USAGE_RECESS1_1R : ");           Serial.println(D104);
    D106 = String(Data[17]); Serial.print("USAGE_CUTOFF1_1R : ");           Serial.println(D106);
    D108 = String(Data[18]); Serial.print("USAGE_RECESS2_1R : ");           Serial.println(D108);
    D110 = String(Data[19]); Serial.print("USAGE_CUTOUT2_1R : ");           Serial.println(D110);
    D112 = String(Data[20]); Serial.print("USAGE_DRILL_1R : ");             Serial.println(D112);
    D114 = String(Data[21]); Serial.print("USAGE_OD_BIT_1R : ");            Serial.println(D114);
    D362 = String(Data[22]); Serial.print("FORMING_2R : ");                 Serial.println(D362);
    D364 = String(Data[23]); Serial.print("FACING_BIT_2R : ");              Serial.println(D364);
    D368 = String(Data[24]); Serial.print("RECESS1_2R : ");                 Serial.println(D368);
    D370 = String(Data[25]); Serial.print("CUTOFF1_2R : ");                 Serial.println(D370);
    D356 = String(Data[26]); Serial.print("DRILL_2R : ");                   Serial.println(D356);
    D372 = String(Data[27]); Serial.print("PARTCHECK_2R : ");               Serial.println(D372);
    D354 = String(Data[28]); Serial.print("CENTERDRILL_2R : ");             Serial.println(D354);
    D366 = String(Data[29]); Serial.print("REAMER_2R : ");                  Serial.println(D366);
    D116 = String(Data[30]); Serial.print("USAGE_FORMING_2R : ");           Serial.println(D116);
    D122 = String(Data[31]); Serial.print("USAGE_FACING_BIT_2R : ");        Serial.println(D122);
    D126 = String(Data[32]); Serial.print("USAGE_RECESS1_2R : ");           Serial.println(D126);
    D128 = String(Data[33]); Serial.print("USAGE_CUTOFF1_1R : ");           Serial.println(D128);
    D118 = String(Data[34]); Serial.print("USAGE_DRILL_2R : ");             Serial.println(D118);
    D120 = String(Data[35]); Serial.print("USAGE_CENTERDRILL_2R : ");       Serial.println(D120);
    D124 = String(Data[36]); Serial.print("USAGE_REAMER_2R : ");            Serial.println(D124);
    D286 = String(Data[37]); Serial.print("UTL : ");                        Serial.println(D286);
    D32 = String(Data[38]);  Serial.print("PRODUCTION_1R : ");              Serial.println(D32);
    ///////////////////////////////////////////////////////////////////

    esp_task_wdt_reset();
    digitalWrite(led_published, LOW); delay(100);digitalWrite(led_published, HIGH); 

    rssi = WiFi.RSSI(); // WiFi strength
    Serial.print("rssi : "); Serial.println(WiFi.RSSI());
    // สร้าง JSON object
    StaticJsonDocument<5000> doc;
    doc["mc_no"]                      = Machine_no;
    doc["rssi"]                       = rssi;
    doc["MODEL_1R"]                   = M34;
    doc["MODEL_2R"]                   = M36;
    doc["FORMING_1R"]                 = D330;
    doc["FACING_BIT_1R"]              = D332;
    doc["RECESS1_1R"]                 = D334;
    doc["CUTOUT1_1R"]                 = D336;
    doc["RECESS2_1R"]                 = D338;
    doc["CUTOUT2_1R"]                 = D340;
    doc["DRILL_1R"]                   = D342;
    doc["PARTCHECK_1R"]               = D344;
    doc["PRODUCITON_BAR"]             = D346;
    doc["OD_BIT_1R"]                  = D348;
    doc["PRODUCTION_2R"]              = D350;
    doc["CT"]                         = D226;
    doc["USAGE_FORMING_1R"]           = D100;
    doc["USAGE_FACING_BIT_1R"]        = D102;
    doc["USAGE_RECESS1_1R"]           = D104;
    doc["USAGE_CUTOFF1_1R"]           = D106;
    doc["USAGE_RECESS2_1R"]           = D108;
    doc["USAGE_CUTOUT2_1R"]           = D110;
    doc["USAGE_DRILL_1R"]             = D112;
    doc["USAGE_OD_BIT_1R"]            = D114;
    doc["FORMING_2R"]                 = D362;
    doc["FACING_BIT_2R"]              = D364;
    doc["RECESS1_2R"]                 = D368;
    doc["CUTOFF1_2R"]                 = D370;
    doc["DRILL_2R"]                   = D356;
    doc["PARTCHECK_2R"]               = D372;
    doc["CENTERDRILL_2R"]             = D354;
    doc["REAMER_2R"]                  = D366;
    doc["USAGE_FORMING_2R"]           = D116;
    doc["USAGE_FACING_BIT_2R"]        = D122;
    doc["USAGE_RECESS1_2R"]           = D126;
    doc["USAGE_CUTOFF1_1R"]           = D128;
    doc["USAGE_DRILL_2R"]             = D118;
    doc["USAGE_CENTERDRILL_2R"]       = D120;
    doc["USAGE_REAMER_2R"]            = D124;
    doc["UTL"]                        = D286;
    doc["PRODUCTION_1R"]              = D32;


    // แปลง JSON object เป็น string
    String jsonStr;
    serializeJson(doc, jsonStr);

    // ส่งข้อมูลผ่าน MQTT
    client.publish("nat/tb/tb07", jsonStr.c_str());
    Serial.println(jsonStr);

    Serial.println("\n---------------finish loop------------------\n\n");
  }

}

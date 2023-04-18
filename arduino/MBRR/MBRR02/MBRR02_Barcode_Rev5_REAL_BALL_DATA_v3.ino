#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <PubSubClient.h>
#include <ModbusMaster.h>
#include <esp_task_wdt.h>
#define WDT_TIMEOUT 300

ModbusMaster node;

#define led_connection 41
#define led_run 42


const char* ssid = "DX_Project";
const char* password = "natmms22";
//const char* ssid = "TP-Link_EF46";
//const char* password = "98148813";
const char* mqtt_server = "192.168.1.2";

IPAddress local_IP(192, 168, 1, 13); // Static IP address192.168.100.164
IPAddress gateway(192, 168, 1, 1);    // Gateway IP address
IPAddress subnet(255, 255, 255, 0);     // subnet

char Machine_no[] = "MBRR02";

WiFiClient espClient;
PubSubClient client(espClient);

/*void led()
{
  digitalWrite(led_connection , HIGH);
  delay(100);
  digitalWrite(led_connection , LOW);
  delay(100);
}*/

int count_connection;

void setup_wifi() 
{
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.config(local_IP, gateway, subnet);
//  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) 
  {
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
  // Loop until we're reconnected
  if(!client.connected()) 
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
  node.begin(1,Serial1);
  pinMode ( led_connection , OUTPUT);
  pinMode ( led_run, OUTPUT);
  Serial.println("Booting");
  setup_wifi(); 

  // Port defaults to 3232
  // ArduinoOTA.setPort(3232);

  // Hostname defaults to esp3232-[MAC]
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
}

String D11001,
D11002,
D11003,
D11004,
D11005,
D11006,
D11007,
D11008,
D11009,
D11010,
D11011,
D11012,
D11013,
D11014,
D11015,
D11016,
D11017,
D11018,
D11019,
D11020,
D11021,
D11022,
D11023,
D11024,
D11025,
D11026,
D11027,
D11028,
D11029,
D11030,
D11031,
D11032,
D11033,
D11034,
D11035,
D11036,
D11037,
D11038,
D11039,
D11040,
D11041,
D11042,
D11043,
D11044,
D11045,
D11046,
D11047,
D11048,
D11049,
D11050,
D11051,
D11052,
D11053,
D11054,
D11055,
D11056,
D11057,
D11058,
D11059,
D11060,
D11061,
D11062,
D11063,
D11064,
D11065,
D11066,
D11067,
D11068,
D11069,
D11070,
D11071,
D11072,
D11073,
D11074,
D11075,
D11076,
D11077,
D11078,
D11079,
D11080,
D11081,
D11082,
D11083,
D11084,
D11085,
D11086,
D11087,
D11088,
D11089,
D11090,
D11091,
D11092,
D11093,
D11094,
D11095,
D11096,
D11097,
D11098,
D11099,
D11100,
D11101,
D11102,
D11103,
D11104,
D11105,
D11106,
D11107,
D11108,
D11109,
D11110,
D11111,
D11112,
D11113,
D11114,
D11115,
D11116,
D11117,
D11118,
D11119,
D11120,
D11121,
D11122,
D11123,
D11124,
D11125,
D11126,
D11127,
D11128,
D11129,
D11130,
D11131,
D11132,
D11133,
D11134,
D11135,
D11136,
D11137,
D11138,
D11139,
D11140,
D11141,
D11142,
D11143,
D11144,
D11145,
D11146,
D11147,
D11148,
D11149,
D11150,
D11151,
D11152,
D11153,
D11154,
D11155,
D11156,
D11157,
D11158,
D11159,
D11160,
D11221,
D11222,
D11223,
D11224,
D11225,
D11226,
D11227,
D11228,
D11229,
D11230,
rssi
;

char i0[16],
i1[16],
i2[16],
i3[16],
i4[16],
i5[16],
i6[16],
i7[16],
i8[16],
i9[16],
i10[16],
i11[16],
i12[16],
i13[16],
i14[16],
i15[16],
i16[16],
i17[16],
i18[16],
i19[16],
i20[16],
i21[16],
i22[16],
i23[16],
i24[16],
i25[16],
i26[16],
i27[16],
i28[16],
i29[16],
i30[16],
i31[16],
i32[16],
i33[16],
i34[16],
i35[16],
i36[16],
i37[16],
i38[16],
i39[16],
i40[16],
i41[16],
i42[16],
i43[16],
i44[16],
i45[16],
i46[16],
i47[16],
i48[16],
i49[16],
i50[16],
i51[16],
i52[16],
i53[16],
i54[16],
i55[16],
i56[16],
i57[16],
i58[16],
i59[16],
i60[16],
i61[16],
i62[16],
i63[16],
i64[16],
i65[16],
i66[16],
i67[16],
i68[16],
i69[16],
i70[16],
i71[16],
i72[16],
i73[16],
i74[16],
i75[16],
i76[16],
i77[16],
i78[16],
i79[16],
i80[16],
i81[16],
i82[16],
i83[16],
i84[16],
i85[16],
i86[16],
i87[16],
i88[16],
i89[16],
i90[16],
i91[16],
i92[16],
i93[16],
i94[16],
i95[16],
i96[16],
i97[16],
i98[16],
i99[16],
i100[16],
i101[16],
i102[16],
i103[16],
i104[16],
i105[16],
i106[16],
i107[16],
i108[16],
i109[16],
i110[16],
i111[16],
i112[16],
i113[16],
i114[16],
i115[16],
i116[16],
i117[16],
i118[16],
i119[16],
i120[16],
i121[16],
i122[16],
i123[16],
i124[16],
i125[16],
i126[16],
i127[16],
i128[16],
i129[16],
i130[16],
i131[16],
i132[16],
i133[16],
i134[16],
i135[16],
i136[16],
i137[16],
i138[16],
i139[16],
i140[16],
i141[16],
i142[16],
i143[16],
i144[16],
i145[16],
i146[16],
i147[16],
i148[16],
i149[16],
i150[16],
i151[16],
i152[16],
i153[16],
i154[16],
i155[16],
i156[16],
i157[16],
i158[16],
i159[16],
i220[16],
i221[16],
i222[16],
i223[16],
i224[16],
i225[16],
i226[16],
i227[16],
i228[16],
i229[16],
i_rssi[16];

void loop() 
{
  rssi = WiFi.RSSI();
  ArduinoOTA.handle();
  if (!client.connected()) 
  {
    reconnect();
  }
  client.loop();
  digitalWrite(led_connection, HIGH);  
  digitalWrite(led_run, LOW);  
  //digitalWrite(led_connection, HIGH);
  Serial.println("\n---------------starting loop----------------");
  
node.readHoldingRegisters(0, 1);   Serial.print("TOTAL A RING  : ");  Serial.println(node.getResponseBuffer(0));D11001= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(1, 1);   Serial.print("COLUMN1 A RING NO.1 : ");  
  ////////////Negetive//////////////// 
  int ne;
  ne = node.getResponseBuffer(0); 
  int y1 = to_Negetive(ne); 
  Serial.println(y1); 
  D11002 = String(y1); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(2, 1);   Serial.print("COLUMN1 A RING NO.2 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int y2 = to_Negetive(ne); 
  Serial.println(y2); 
  D11003 = String(y2); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(3, 1);   Serial.print("COLUMN1 A RING NO.3 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int y3 = to_Negetive(ne); 
  Serial.println(y3); 
  D11004 = String(y3); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(4, 1);   Serial.print("COLUMN1 A RING NO.4 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int y4 = to_Negetive(ne); 
  Serial.println(y4); 
  D11005 = String(y4); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(5, 1);   Serial.print("COLUMN1 A RING NO.5 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int y5 = to_Negetive(ne); 
  Serial.println(y5); 
  D11006 = String(y5); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(6, 1);   Serial.print("COLUMN1 A RING NO.6 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int y6 = to_Negetive(ne); 
  Serial.println(y6); 
  D11007 = String(y6); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(7, 1);   Serial.print("COLUMN1 A RING NO.7 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int y7 = to_Negetive(ne); 
  Serial.println(y7); 
  D11008 = String(y7); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(8, 1);   Serial.print("COLUMN1 A RING NO.8 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int y8 = to_Negetive(ne); 
  Serial.println(y8); 
  D11009 = String(y8); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(9, 1);   Serial.print("COLUMN1 A RING NO.9 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int y9 = to_Negetive(ne); 
  Serial.println(y9); 
  D11010 = String(y9); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(10, 1);   Serial.print("COLUMN1 A RING NO.10 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int y10 = to_Negetive(ne); 
  Serial.println(y10); 
  D11011 = String(y10); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(11, 1);   Serial.print("COLUMN1 A RING NO.11 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int y11 = to_Negetive(ne); 
  Serial.println(y11); 
  D11012 = String(y11); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(12, 1);   Serial.print("COLUMN1 A RING NO.12 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int y12 = to_Negetive(ne); 
  Serial.println(y12); 
  D11013 = String(y12); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(13, 1);   Serial.print("COLUMN1 A RING NO.13 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int y13 = to_Negetive(ne); 
  Serial.println(y13); 
  D11014 = String(y13); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(14, 1);   Serial.print("COLUMN1 A RING NO.14 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int y14 = to_Negetive(ne); 
  Serial.println(y14); 
  D11015 = String(y14); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(15, 1);   Serial.print("COLUMN1 A RING NO.15 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int y15 = to_Negetive(ne); 
  Serial.println(y15); 
  D11016 = String(y15); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(16, 1);   Serial.print("COLUMN1 A RING NO.16 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int y16 = to_Negetive(ne); 
  Serial.println(y16); 
  D11017 = String(y16); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(17, 1);   Serial.print("COLUMN1 A RING NO.17 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int y17 = to_Negetive(ne); 
  Serial.println(y17); 
  D11018 = String(y17); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(18, 1);   Serial.print("COLUMN1 A RING NO.18 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int y18 = to_Negetive(ne); 
  Serial.println(y18); 
  D11019 = String(y18); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(19, 1);   Serial.print("COLUMN1 A RING NO.19 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int y19 = to_Negetive(ne); 
  Serial.println(y19); 
  D11020 = String(y19); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(20, 1);   Serial.print("COLUMN1 A RING NO.20 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int y20 = to_Negetive(ne); 
  Serial.println(y20); 
  D11021 = String(y20); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(21, 1);   Serial.print("COLUMN1 A RING NO.21 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int y21 = to_Negetive(ne); 
  Serial.println(y21); 
  D11022 = String(y21); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(22, 1);   Serial.print("COLUMN1 A RING NO.22 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int y22 = to_Negetive(ne); 
  Serial.println(y22); 
  D11023 = String(y22); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(23, 1);   Serial.print("COLUMN1 A RING NO.23 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int y23 = to_Negetive(ne); 
  Serial.println(y23); 
  D11024 = String(y23); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(24, 1);   Serial.print("COLUMN1 A RING NO.24 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int y24 = to_Negetive(ne); 
  Serial.println(y24); 
  D11025 = String(y24); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(25, 1);   Serial.print("COLUMN1 A RING NO.25 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int y25 = to_Negetive(ne); 
  Serial.println(y25); 
  D11026 = String(y25); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(26, 1);   Serial.print("COLUMN1 A RING NO.26 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int y26 = to_Negetive(ne); 
  Serial.println(y26); 
  D11027 = String(y26); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(27, 1);   Serial.print("COLUMN1 A RING NO.27 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int y27 = to_Negetive(ne); 
  Serial.println(y27); 
  D11028 = String(y27); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(28, 1);   Serial.print("COLUMN1 A RING NO.28 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int y28 = to_Negetive(ne); 
  Serial.println(y28); 
  D11029 = String(y28); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(29, 1);   Serial.print("COLUMN1 A RING NO.29 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int y29 = to_Negetive(ne); 
  Serial.println(y29); 
  D11030 = String(y29); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(30, 1);   Serial.print("COLUMN1 A RING NO.30 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int y30 = to_Negetive(ne); 
  Serial.println(y30); 
  D11031 = String(y30); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(31, 1);   Serial.print("COLUMN1 A RING NO.31 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int y31 = to_Negetive(ne); 
  Serial.println(y31); 
  D11032 = String(y31); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(32, 1);   Serial.print("COLUMN1 A RING NO.32 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int y32 = to_Negetive(ne); 
  Serial.println(y32); 
  D11033 = String(y32); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(33, 1);   Serial.print("COLUMN1 A RING NO.33 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int y33 = to_Negetive(ne); 
  Serial.println(y33); 
  D11034 = String(y33); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(34, 1);   Serial.print("COLUMN1 A RING NO.34 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int y34 = to_Negetive(ne); 
  Serial.println(y34); 
  D11035 = String(y34); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(35, 1);   Serial.print("COLUMN1 A RING NO.35 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int y35 = to_Negetive(ne); 
  Serial.println(y35); 
  D11036 = String(y35); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(36, 1);   Serial.print("COLUMN1 A RING NO.36 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int y36 = to_Negetive(ne); 
  Serial.println(y36); 
  D11037 = String(y36); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(37, 1);   Serial.print("COLUMN1 A RING NO.37 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int y37 = to_Negetive(ne); 
  Serial.println(y37); 
  D11038 = String(y37); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(38, 1);   Serial.print("COLUMN1 A RING NO.38 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int y38 = to_Negetive(ne); 
  Serial.println(y38); 
  D11039 = String(y38); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(39, 1);   Serial.print("COLUMN1 A RING NO.39 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int y39 = to_Negetive(ne); 
  Serial.println(y39); 
  D11040 = String(y39); 
  node.clearResponseBuffer(); 
  ////////////Negetive////////////////
node.readHoldingRegisters(40, 1);   Serial.print("COLUMN2 A RING NO.1 : ");  Serial.println(node.getResponseBuffer(0));D11041= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(41, 1);   Serial.print("COLUMN2 A RING NO.2 : ");  Serial.println(node.getResponseBuffer(0));D11042= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(42, 1);   Serial.print("COLUMN2 A RING NO.3 : ");  Serial.println(node.getResponseBuffer(0));D11043= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(43, 1);   Serial.print("COLUMN2 A RING NO.4 : ");  Serial.println(node.getResponseBuffer(0));D11044= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(44, 1);   Serial.print("COLUMN2 A RING NO.5 : ");  Serial.println(node.getResponseBuffer(0));D11045= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(45, 1);   Serial.print("COLUMN2 A RING NO.6 : ");  Serial.println(node.getResponseBuffer(0));D11046= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(46, 1);   Serial.print("COLUMN2 A RING NO.7 : ");  Serial.println(node.getResponseBuffer(0));D11047= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(47, 1);   Serial.print("COLUMN2 A RING NO.8 : ");  Serial.println(node.getResponseBuffer(0));D11048= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(48, 1);   Serial.print("COLUMN2 A RING NO.9 : ");  Serial.println(node.getResponseBuffer(0));D11049= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(49, 1);   Serial.print("COLUMN2 A RING NO.10 : ");  Serial.println(node.getResponseBuffer(0));D11050= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(50, 1);   Serial.print("COLUMN2 A RING NO.11 : ");  Serial.println(node.getResponseBuffer(0));D11051= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(51, 1);   Serial.print("COLUMN2 A RING NO.12 : ");  Serial.println(node.getResponseBuffer(0));D11052= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(52, 1);   Serial.print("COLUMN2 A RING NO.13 : ");  Serial.println(node.getResponseBuffer(0));D11053= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(53, 1);   Serial.print("COLUMN2 A RING NO.14 : ");  Serial.println(node.getResponseBuffer(0));D11054= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(54, 1);   Serial.print("COLUMN2 A RING NO.15 : ");  Serial.println(node.getResponseBuffer(0));D11055= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(55, 1);   Serial.print("COLUMN2 A RING NO.16 : ");  Serial.println(node.getResponseBuffer(0));D11056= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(56, 1);   Serial.print("COLUMN2 A RING NO.17 : ");  Serial.println(node.getResponseBuffer(0));D11057= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(57, 1);   Serial.print("COLUMN2 A RING NO.18 : ");  Serial.println(node.getResponseBuffer(0));D11058= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(58, 1);   Serial.print("COLUMN2 A RING NO.19 : ");  Serial.println(node.getResponseBuffer(0));D11059= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(59, 1);   Serial.print("COLUMN2 A RING NO.20 : ");  Serial.println(node.getResponseBuffer(0));D11060= node.getResponseBuffer(0);  node.clearResponseBuffer();

node.readHoldingRegisters(60, 1);   Serial.print("COLUMN2 A RING NO.21 : ");  Serial.println(node.getResponseBuffer(0));D11061= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(61, 1);   Serial.print("COLUMN2 A RING NO.22 : ");  Serial.println(node.getResponseBuffer(0));D11062= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(62, 1);   Serial.print("COLUMN2 A RING NO.23 : ");  Serial.println(node.getResponseBuffer(0));D11063= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(63, 1);   Serial.print("COLUMN2 A RING NO.24 : ");  Serial.println(node.getResponseBuffer(0));D11064= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(64, 1);   Serial.print("COLUMN2 A RING NO.25 : ");  Serial.println(node.getResponseBuffer(0));D11065= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(65, 1);   Serial.print("COLUMN2 A RING NO.26 : ");  Serial.println(node.getResponseBuffer(0));D11066= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(66, 1);   Serial.print("COLUMN2 A RING NO.27 : ");  Serial.println(node.getResponseBuffer(0));D11067= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(67, 1);   Serial.print("COLUMN2 A RING NO.28 : ");  Serial.println(node.getResponseBuffer(0));D11068= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(68, 1);   Serial.print("COLUMN2 A RING NO.29 : ");  Serial.println(node.getResponseBuffer(0));D11069= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(69, 1);   Serial.print("COLUMN2 A RING NO.30 : ");  Serial.println(node.getResponseBuffer(0));D11070= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(70, 1);   Serial.print("COLUMN2 A RING NO.31 : ");  Serial.println(node.getResponseBuffer(0));D11071= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(71, 1);   Serial.print("COLUMN2 A RING NO.32 : ");  Serial.println(node.getResponseBuffer(0));D11072= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(72, 1);   Serial.print("COLUMN2 A RING NO.33 : ");  Serial.println(node.getResponseBuffer(0));D11073= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(73, 1);   Serial.print("COLUMN2 A RING NO.34 : ");  Serial.println(node.getResponseBuffer(0));D11074= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(74, 1);   Serial.print("COLUMN2 A RING NO.35 : ");  Serial.println(node.getResponseBuffer(0));D11075= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(75, 1);   Serial.print("COLUMN2 A RING NO.36 : ");  Serial.println(node.getResponseBuffer(0));D11076= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(76, 1);   Serial.print("COLUMN2 A RING NO.37 : ");  Serial.println(node.getResponseBuffer(0));D11077= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(77, 1);   Serial.print("COLUMN2 A RING NO.38 : ");  Serial.println(node.getResponseBuffer(0));D11078= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(78, 1);   Serial.print("COLUMN2 A RING NO.39 : ");  Serial.println(node.getResponseBuffer(0));D11079= node.getResponseBuffer(0);  node.clearResponseBuffer();

node.readHoldingRegisters(79, 1);   Serial.print("TOTAL B RING  : ");  Serial.println(node.getResponseBuffer(0));D11080= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(80, 1);   Serial.print("COLUMN1 B RING NO.1 : ");   
  ////////////Negetive////////////////
  ne = node.getResponseBuffer(0);
  int z = to_Negetive(ne);
  Serial.println(z);
  D11081 = String(z);
  node.clearResponseBuffer();
  ////////////Negetive////////////////
  
node.readHoldingRegisters(81, 1);   Serial.print("COLUMN1 B RING NO.2 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z2 = to_Negetive(ne); 
  Serial.println(z2); 
  D11082 = String(z2); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(82, 1);   Serial.print("COLUMN1 B RING NO.3 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z3 = to_Negetive(ne); 
  Serial.println(z3); 
  D11083 = String(z3); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(83, 1);   Serial.print("COLUMN1 B RING NO.4 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z4 = to_Negetive(ne); 
  Serial.println(z4); 
  D11084 = String(z4); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(84, 1);   Serial.print("COLUMN1 B RING NO.5 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z5 = to_Negetive(ne); 
  Serial.println(z5); 
  D11085 = String(z5); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(85, 1);   Serial.print("COLUMN1 B RING NO.6 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z6 = to_Negetive(ne); 
  Serial.println(z6); 
  D11086 = String(z6); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(86, 1);   Serial.print("COLUMN1 B RING NO.7 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z7 = to_Negetive(ne); 
  Serial.println(z7); 
  D11087 = String(z7); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(87, 1);   Serial.print("COLUMN1 B RING NO.8 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z8 = to_Negetive(ne); 
  Serial.println(z8); 
  D11088 = String(z8); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(88, 1);   Serial.print("COLUMN1 B RING NO.9 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z9 = to_Negetive(ne); 
  Serial.println(z9); 
  D11089 = String(z9); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(89, 1);   Serial.print("COLUMN1 B RING NO.10 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z10 = to_Negetive(ne); 
  Serial.println(z10); 
  D11090 = String(z10); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(90, 1);   Serial.print("COLUMN1 B RING NO.11 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z11 = to_Negetive(ne); 
  Serial.println(z11); 
  D11091 = String(z11); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(91, 1);   Serial.print("COLUMN1 B RING NO.12 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z12 = to_Negetive(ne); 
  Serial.println(z12); 
  D11092 = String(z12); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(92, 1);   Serial.print("COLUMN1 B RING NO.13 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z13 = to_Negetive(ne); 
  Serial.println(z13); 
  D11093 = String(z13); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(93, 1);   Serial.print("COLUMN1 B RING NO.14 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z14 = to_Negetive(ne); 
  Serial.println(z14); 
  D11094 = String(z14); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(94, 1);   Serial.print("COLUMN1 B RING NO.15 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z15 = to_Negetive(ne); 
  Serial.println(z15); 
  D11095 = String(z15); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(95, 1);   Serial.print("COLUMN1 B RING NO.16 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z16 = to_Negetive(ne); 
  Serial.println(z16); 
  D11096 = String(z16); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(96, 1);   Serial.print("COLUMN1 B RING NO.17 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z17 = to_Negetive(ne); 
  Serial.println(z17); 
  D11097 = String(z17); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(97, 1);   Serial.print("COLUMN1 B RING NO.18 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z18 = to_Negetive(ne); 
  Serial.println(z18); 
  D11098 = String(z18); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(98, 1);   Serial.print("COLUMN1 B RING NO.19 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z19 = to_Negetive(ne); 
  Serial.println(z19); 
  D11099 = String(z19); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(99, 1);   Serial.print("COLUMN1 B RING NO.20 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z20 = to_Negetive(ne); 
  Serial.println(z20); 
  D11100 = String(z20); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(100, 1);   Serial.print("COLUMN1 B RING NO.21 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z21 = to_Negetive(ne); 
  Serial.println(z21); 
  D11101 = String(z21); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(101, 1);   Serial.print("COLUMN1 B RING NO.22 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z22 = to_Negetive(ne); 
  Serial.println(z22); 
  D11102 = String(z22); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(102, 1);   Serial.print("COLUMN1 B RING NO.23 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z23 = to_Negetive(ne); 
  Serial.println(z23); 
  D11103 = String(z23); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(103, 1);   Serial.print("COLUMN1 B RING NO.24 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z24 = to_Negetive(ne); 
  Serial.println(z24); 
  D11104 = String(z24); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(104, 1);   Serial.print("COLUMN1 B RING NO.25 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z25 = to_Negetive(ne); 
  Serial.println(z25); 
  D11105 = String(z25); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(105, 1);   Serial.print("COLUMN1 B RING NO.26 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z26 = to_Negetive(ne); 
  Serial.println(z26); 
  D11106 = String(z26); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(106, 1);   Serial.print("COLUMN1 B RING NO.27 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z27 = to_Negetive(ne); 
  Serial.println(z27); 
  D11107 = String(z27); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(107, 1);   Serial.print("COLUMN1 B RING NO.28 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z28 = to_Negetive(ne); 
  Serial.println(z28); 
  D11108 = String(z28); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(108, 1);   Serial.print("COLUMN1 B RING NO.29 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z29 = to_Negetive(ne); 
  Serial.println(z29); 
  D11109 = String(z29); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(109, 1);   Serial.print("COLUMN1 B RING NO.30 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z30 = to_Negetive(ne); 
  Serial.println(z30); 
  D11110 = String(z30); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(110, 1);   Serial.print("COLUMN1 B RING NO.31 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z31 = to_Negetive(ne); 
  Serial.println(z31); 
  D11111 = String(z31); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(111, 1);   Serial.print("COLUMN1 B RING NO.32 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z32 = to_Negetive(ne); 
  Serial.println(z32); 
  D11112 = String(z32); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(112, 1);   Serial.print("COLUMN1 B RING NO.33 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z33 = to_Negetive(ne); 
  Serial.println(z33); 
  D11113 = String(z33); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(113, 1);   Serial.print("COLUMN1 B RING NO.34 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z34 = to_Negetive(ne); 
  Serial.println(z34); 
  D11114 = String(z34); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(114, 1);   Serial.print("COLUMN1 B RING NO.35 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z35 = to_Negetive(ne); 
  Serial.println(z35); 
  D11115 = String(z35); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(115, 1);   Serial.print("COLUMN1 B RING NO.36 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z36 = to_Negetive(ne); 
  Serial.println(z36); 
  D11116 = String(z36); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(116, 1);   Serial.print("COLUMN1 B RING NO.37 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z37 = to_Negetive(ne); 
  Serial.println(z37); 
  D11117 = String(z37); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(117, 1);   Serial.print("COLUMN1 B RING NO.38 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z38 = to_Negetive(ne); 
  Serial.println(z38); 
  D11118 = String(z38); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(118, 1);   Serial.print("COLUMN1 B RING NO.39 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z39 = to_Negetive(ne); 
  Serial.println(z39); 
  D11119 = String(z39); 
  node.clearResponseBuffer(); 
  ////////////Negetive////////////////


node.readHoldingRegisters(119, 1);   Serial.print("COLUMN2 B RING NO.1 : ");  Serial.println(node.getResponseBuffer(0));D11120= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(120, 1);   Serial.print("COLUMN2 B RING NO.2 : ");  Serial.println(node.getResponseBuffer(0));D11121= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(121, 1);   Serial.print("COLUMN2 B RING NO.3 : ");  Serial.println(node.getResponseBuffer(0));D11122= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(122, 1);   Serial.print("COLUMN2 B RING NO.4 : ");  Serial.println(node.getResponseBuffer(0));D11123= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(123, 1);   Serial.print("COLUMN2 B RING NO.5 : ");  Serial.println(node.getResponseBuffer(0));D11124= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(124, 1);   Serial.print("COLUMN2 B RING NO.6 : ");  Serial.println(node.getResponseBuffer(0));D11125= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(125, 1);   Serial.print("COLUMN2 B RING NO.7 : ");  Serial.println(node.getResponseBuffer(0));D11126= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(126, 1);   Serial.print("COLUMN2 B RING NO.8 : ");  Serial.println(node.getResponseBuffer(0));D11127= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(127, 1);   Serial.print("COLUMN2 B RING NO.9 : ");  Serial.println(node.getResponseBuffer(0));D11128= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(128, 1);   Serial.print("COLUMN2 B RING NO.10 : ");  Serial.println(node.getResponseBuffer(0));D11129= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(129, 1);   Serial.print("COLUMN2 B RING NO.11 : ");  Serial.println(node.getResponseBuffer(0));D11130= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(130, 1);   Serial.print("COLUMN2 B RING NO.12 : ");  Serial.println(node.getResponseBuffer(0));D11131= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(131, 1);   Serial.print("COLUMN2 B RING NO.13 : ");  Serial.println(node.getResponseBuffer(0));D11132= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(132, 1);   Serial.print("COLUMN2 B RING NO.14 : ");  Serial.println(node.getResponseBuffer(0));D11133= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(133, 1);   Serial.print("COLUMN2 B RING NO.15 : ");  Serial.println(node.getResponseBuffer(0));D11134= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(134, 1);   Serial.print("COLUMN2 B RING NO.16 : ");  Serial.println(node.getResponseBuffer(0));D11135= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(135, 1);   Serial.print("COLUMN2 B RING NO.17 : ");  Serial.println(node.getResponseBuffer(0));D11136= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(136, 1);   Serial.print("COLUMN2 B RING NO.18 : ");  Serial.println(node.getResponseBuffer(0));D11137= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(137, 1);   Serial.print("COLUMN2 B RING NO.19 : ");  Serial.println(node.getResponseBuffer(0));D11138= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(138, 1);   Serial.print("COLUMN2 B RING NO.20 : ");  Serial.println(node.getResponseBuffer(0));D11139= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(139, 1);   Serial.print("COLUMN2 B RING NO.21 : ");  Serial.println(node.getResponseBuffer(0));D11140= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(140, 1);   Serial.print("COLUMN2 B RING NO.22 : ");  Serial.println(node.getResponseBuffer(0));D11141= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(141, 1);   Serial.print("COLUMN2 B RING NO.23 : ");  Serial.println(node.getResponseBuffer(0));D11142= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(142, 1);   Serial.print("COLUMN2 B RING NO.24 : ");  Serial.println(node.getResponseBuffer(0));D11143= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(143, 1);   Serial.print("COLUMN2 B RING NO.25 : ");  Serial.println(node.getResponseBuffer(0));D11144= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(144, 1);   Serial.print("COLUMN2 B RING NO.26 : ");  Serial.println(node.getResponseBuffer(0));D11145= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(145, 1);   Serial.print("COLUMN2 B RING NO.27 : ");  Serial.println(node.getResponseBuffer(0));D11146= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(146, 1);   Serial.print("COLUMN2 B RING NO.28 : ");  Serial.println(node.getResponseBuffer(0));D11147= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(147, 1);   Serial.print("COLUMN2 B RING NO.29 : ");  Serial.println(node.getResponseBuffer(0));D11148= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(148, 1);   Serial.print("COLUMN2 B RING NO.30 : ");  Serial.println(node.getResponseBuffer(0));D11149= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(149, 1);   Serial.print("COLUMN2 B RING NO.31 : ");  Serial.println(node.getResponseBuffer(0));D11150= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(150, 1);   Serial.print("COLUMN2 B RING NO.32 : ");  Serial.println(node.getResponseBuffer(0));D11151= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(151, 1);   Serial.print("COLUMN2 B RING NO.33 : ");  Serial.println(node.getResponseBuffer(0));D11152= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(152, 1);   Serial.print("COLUMN2 B RING NO.34 : ");  Serial.println(node.getResponseBuffer(0));D11153= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(153, 1);   Serial.print("COLUMN2 B RING NO.35 : ");  Serial.println(node.getResponseBuffer(0));D11154= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(154, 1);   Serial.print("COLUMN2 B RING NO.36 : ");  Serial.println(node.getResponseBuffer(0));D11155= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(155, 1);   Serial.print("COLUMN2 B RING NO.37 : ");  Serial.println(node.getResponseBuffer(0));D11156= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(156, 1);   Serial.print("COLUMN2 B RING NO.38 : ");  Serial.println(node.getResponseBuffer(0));D11157= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(157, 1);   Serial.print("COLUMN2 B RING NO.39 : ");  Serial.println(node.getResponseBuffer(0));D11158= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(158, 1);   Serial.print("UTL : ");  Serial.println(node.getResponseBuffer(0));D11159= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(159, 1);   Serial.print("ROBOT : ");  Serial.println(node.getResponseBuffer(0));D11160= node.getResponseBuffer(0);  node.clearResponseBuffer();

//////////////////////////////Barcode Scanner/////////////////////////////////////


  int num = 60;
  String m[num];
  String hexNum[num];
  String hexNumber;
  int x[num];
  for(int i=0;i<num;i++)
  {
    node.readHoldingRegisters(160+i, 1); 
    Serial.print(i);Serial.print(" : ");
    Serial.println(node.getResponseBuffer(0));
    m[i] = node.getResponseBuffer(0);
    node.clearResponseBuffer();
    x[i] = m[i].toInt();hexNum[i] = convertDecimalToHex(x[i]);
    hexNumber = hexNumber+hexNum[i];
    //Serial.println(hexNumber);
    esp_task_wdt_reset();
  }
  //Serial.println(hexNumber);
  char bar[230];
  hexNumber.toCharArray(bar, 230);client.publish("MBRR02/barcode", bar);
  Serial.println(bar);
//////////////////////////////Barcode Scanner/////////////////////////////////////  

node.readHoldingRegisters(220, 1);   Serial.print("REAL BALL C1 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z40 = to_Negetive(ne); 
  Serial.println(z40); 
  D11221 = String(z40); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(221, 1);   Serial.print("REAL BALL C2 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z41 = to_Negetive(ne); 
  Serial.println(z41); 
  D11222 = String(z41); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(222, 1);   Serial.print("REAL BALL C3 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z42 = to_Negetive(ne); 
  Serial.println(z42); 
  D11223 = String(z42); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 
  
node.readHoldingRegisters(223, 1);   Serial.print("REAL BALL C4 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z43 = to_Negetive(ne); 
  Serial.println(z43); 
  D11224 = String(z43); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(224, 1);   Serial.print("REAL BALL C5 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z44 = to_Negetive(ne); 
  Serial.println(z44); 
  D11225 = String(z44); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(225, 1);   Serial.print("BALL C1 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z45 = to_Negetive(ne); 
  Serial.println(z45); 
  D11226 = String(z45); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(226, 1);   Serial.print("BALL C2 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z46 = to_Negetive(ne); 
  Serial.println(z46); 
  D11227 = String(z46); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(227, 1);   Serial.print("BALL C3 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z47 = to_Negetive(ne); 
  Serial.println(z47); 
  D11228 = String(z47); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 
  
node.readHoldingRegisters(228, 1);   Serial.print("BALL C4 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z48 = to_Negetive(ne); 
  Serial.println(z48); 
  D11229 = String(z48); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 

node.readHoldingRegisters(229, 1);   Serial.print("BALL C5 : ");  
  ////////////Negetive//////////////// 
  ne = node.getResponseBuffer(0); 
  int z49 = to_Negetive(ne); 
  Serial.println(z49); 
  D11230 = String(z49); 
  node.clearResponseBuffer(); 
  ////////////Negetive//////////////// 
  
  digitalWrite(led_run, HIGH);  
  
D11001.toCharArray(i0,16);client.publish("MBRR02/D11001",i0);
D11002.toCharArray(i1,16);client.publish("MBRR02/D11002",i1);
D11003.toCharArray(i2,16);client.publish("MBRR02/D11003",i2);
D11004.toCharArray(i3,16);client.publish("MBRR02/D11004",i3);
D11005.toCharArray(i4,16);client.publish("MBRR02/D11005",i4);
D11006.toCharArray(i5,16);client.publish("MBRR02/D11006",i5);
D11007.toCharArray(i6,16);client.publish("MBRR02/D11007",i6);
D11008.toCharArray(i7,16);client.publish("MBRR02/D11008",i7);
D11009.toCharArray(i8,16);client.publish("MBRR02/D11009",i8);
D11010.toCharArray(i9,16);client.publish("MBRR02/D11010",i9);
D11011.toCharArray(i10,16);client.publish("MBRR02/D11011",i10);
D11012.toCharArray(i11,16);client.publish("MBRR02/D11012",i11);
D11013.toCharArray(i12,16);client.publish("MBRR02/D11013",i12);
D11014.toCharArray(i13,16);client.publish("MBRR02/D11014",i13);
D11015.toCharArray(i14,16);client.publish("MBRR02/D11015",i14);
D11016.toCharArray(i15,16);client.publish("MBRR02/D11016",i15);
D11017.toCharArray(i16,16);client.publish("MBRR02/D11017",i16);
D11018.toCharArray(i17,16);client.publish("MBRR02/D11018",i17);
D11019.toCharArray(i18,16);client.publish("MBRR02/D11019",i18);
D11020.toCharArray(i19,16);client.publish("MBRR02/D11020",i19);
D11021.toCharArray(i20,16);client.publish("MBRR02/D11021",i20);
D11022.toCharArray(i21,16);client.publish("MBRR02/D11022",i21);
D11023.toCharArray(i22,16);client.publish("MBRR02/D11023",i22);
D11024.toCharArray(i23,16);client.publish("MBRR02/D11024",i23);
D11025.toCharArray(i24,16);client.publish("MBRR02/D11025",i24);
D11026.toCharArray(i25,16);client.publish("MBRR02/D11026",i25);
D11027.toCharArray(i26,16);client.publish("MBRR02/D11027",i26);
D11028.toCharArray(i27,16);client.publish("MBRR02/D11028",i27);
D11029.toCharArray(i28,16);client.publish("MBRR02/D11029",i28);
D11030.toCharArray(i29,16);client.publish("MBRR02/D11030",i29);
D11031.toCharArray(i30,16);client.publish("MBRR02/D11031",i30);
D11032.toCharArray(i31,16);client.publish("MBRR02/D11032",i31);
D11033.toCharArray(i32,16);client.publish("MBRR02/D11033",i32);
D11034.toCharArray(i33,16);client.publish("MBRR02/D11034",i33);
D11035.toCharArray(i34,16);client.publish("MBRR02/D11035",i34);
D11036.toCharArray(i35,16);client.publish("MBRR02/D11036",i35);
D11037.toCharArray(i36,16);client.publish("MBRR02/D11037",i36);
D11038.toCharArray(i37,16);client.publish("MBRR02/D11038",i37);
D11039.toCharArray(i38,16);client.publish("MBRR02/D11039",i38);
D11040.toCharArray(i39,16);client.publish("MBRR02/D11040",i39);
D11041.toCharArray(i40,16);client.publish("MBRR02/D11041",i40);
D11042.toCharArray(i41,16);client.publish("MBRR02/D11042",i41);
D11043.toCharArray(i42,16);client.publish("MBRR02/D11043",i42);
D11044.toCharArray(i43,16);client.publish("MBRR02/D11044",i43);
D11045.toCharArray(i44,16);client.publish("MBRR02/D11045",i44);
D11046.toCharArray(i45,16);client.publish("MBRR02/D11046",i45);
D11047.toCharArray(i46,16);client.publish("MBRR02/D11047",i46);
D11048.toCharArray(i47,16);client.publish("MBRR02/D11048",i47);
D11049.toCharArray(i48,16);client.publish("MBRR02/D11049",i48);
D11050.toCharArray(i49,16);client.publish("MBRR02/D11050",i49);
D11051.toCharArray(i50,16);client.publish("MBRR02/D11051",i50);
D11052.toCharArray(i51,16);client.publish("MBRR02/D11052",i51);
D11053.toCharArray(i52,16);client.publish("MBRR02/D11053",i52);
D11054.toCharArray(i53,16);client.publish("MBRR02/D11054",i53);
D11055.toCharArray(i54,16);client.publish("MBRR02/D11055",i54);
D11056.toCharArray(i55,16);client.publish("MBRR02/D11056",i55);
D11057.toCharArray(i56,16);client.publish("MBRR02/D11057",i56);
D11058.toCharArray(i57,16);client.publish("MBRR02/D11058",i57);
D11059.toCharArray(i58,16);client.publish("MBRR02/D11059",i58);
D11060.toCharArray(i59,16);client.publish("MBRR02/D11060",i59);
D11061.toCharArray(i60,16);client.publish("MBRR02/D11061",i60);
D11062.toCharArray(i61,16);client.publish("MBRR02/D11062",i61);
D11063.toCharArray(i62,16);client.publish("MBRR02/D11063",i62);
D11064.toCharArray(i63,16);client.publish("MBRR02/D11064",i63);
D11065.toCharArray(i64,16);client.publish("MBRR02/D11065",i64);
D11066.toCharArray(i65,16);client.publish("MBRR02/D11066",i65);
D11067.toCharArray(i66,16);client.publish("MBRR02/D11067",i66);
D11068.toCharArray(i67,16);client.publish("MBRR02/D11068",i67);
D11069.toCharArray(i68,16);client.publish("MBRR02/D11069",i68);
D11070.toCharArray(i69,16);client.publish("MBRR02/D11070",i69);
D11071.toCharArray(i70,16);client.publish("MBRR02/D11071",i70);
D11072.toCharArray(i71,16);client.publish("MBRR02/D11072",i71);
D11073.toCharArray(i72,16);client.publish("MBRR02/D11073",i72);
D11074.toCharArray(i73,16);client.publish("MBRR02/D11074",i73);
D11075.toCharArray(i74,16);client.publish("MBRR02/D11075",i74);
D11076.toCharArray(i75,16);client.publish("MBRR02/D11076",i75);
D11077.toCharArray(i76,16);client.publish("MBRR02/D11077",i76);
D11078.toCharArray(i77,16);client.publish("MBRR02/D11078",i77);
D11079.toCharArray(i78,16);client.publish("MBRR02/D11079",i78);
D11080.toCharArray(i79,16);client.publish("MBRR02/D11080",i79);
D11081.toCharArray(i80,16);client.publish("MBRR02/D11081",i80);
D11082.toCharArray(i81,16);client.publish("MBRR02/D11082",i81);
D11083.toCharArray(i82,16);client.publish("MBRR02/D11083",i82);
D11084.toCharArray(i83,16);client.publish("MBRR02/D11084",i83);
D11085.toCharArray(i84,16);client.publish("MBRR02/D11085",i84);
D11086.toCharArray(i85,16);client.publish("MBRR02/D11086",i85);
D11087.toCharArray(i86,16);client.publish("MBRR02/D11087",i86);
D11088.toCharArray(i87,16);client.publish("MBRR02/D11088",i87);
D11089.toCharArray(i88,16);client.publish("MBRR02/D11089",i88);
D11090.toCharArray(i89,16);client.publish("MBRR02/D11090",i89);
D11091.toCharArray(i90,16);client.publish("MBRR02/D11091",i90);
D11092.toCharArray(i91,16);client.publish("MBRR02/D11092",i91);
D11093.toCharArray(i92,16);client.publish("MBRR02/D11093",i92);
D11094.toCharArray(i93,16);client.publish("MBRR02/D11094",i93);
D11095.toCharArray(i94,16);client.publish("MBRR02/D11095",i94);
D11096.toCharArray(i95,16);client.publish("MBRR02/D11096",i95);
D11097.toCharArray(i96,16);client.publish("MBRR02/D11097",i96);
D11098.toCharArray(i97,16);client.publish("MBRR02/D11098",i97);
D11099.toCharArray(i98,16);client.publish("MBRR02/D11099",i98);
D11100.toCharArray(i99,16);client.publish("MBRR02/D11100",i99);
D11101.toCharArray(i100,16);client.publish("MBRR02/D11101",i100);
D11102.toCharArray(i101,16);client.publish("MBRR02/D11102",i101);
D11103.toCharArray(i102,16);client.publish("MBRR02/D11103",i102);
D11104.toCharArray(i103,16);client.publish("MBRR02/D11104",i103);
D11105.toCharArray(i104,16);client.publish("MBRR02/D11105",i104);
D11106.toCharArray(i105,16);client.publish("MBRR02/D11106",i105);
D11107.toCharArray(i106,16);client.publish("MBRR02/D11107",i106);
D11108.toCharArray(i107,16);client.publish("MBRR02/D11108",i107);
D11109.toCharArray(i108,16);client.publish("MBRR02/D11109",i108);
D11110.toCharArray(i109,16);client.publish("MBRR02/D11110",i109);
D11111.toCharArray(i110,16);client.publish("MBRR02/D11111",i110);
D11112.toCharArray(i111,16);client.publish("MBRR02/D11112",i111);
D11113.toCharArray(i112,16);client.publish("MBRR02/D11113",i112);
D11114.toCharArray(i113,16);client.publish("MBRR02/D11114",i113);
D11115.toCharArray(i114,16);client.publish("MBRR02/D11115",i114);
D11116.toCharArray(i115,16);client.publish("MBRR02/D11116",i115);
D11117.toCharArray(i116,16);client.publish("MBRR02/D11117",i116);
D11118.toCharArray(i117,16);client.publish("MBRR02/D11118",i117);
D11119.toCharArray(i118,16);client.publish("MBRR02/D11119",i118);
D11120.toCharArray(i119,16);client.publish("MBRR02/D11120",i119);
D11121.toCharArray(i120,16);client.publish("MBRR02/D11121",i120);
D11122.toCharArray(i121,16);client.publish("MBRR02/D11122",i121);
D11123.toCharArray(i122,16);client.publish("MBRR02/D11123",i122);
D11124.toCharArray(i123,16);client.publish("MBRR02/D11124",i123);
D11125.toCharArray(i124,16);client.publish("MBRR02/D11125",i124);
D11126.toCharArray(i125,16);client.publish("MBRR02/D11126",i125);
D11127.toCharArray(i126,16);client.publish("MBRR02/D11127",i126);
D11128.toCharArray(i127,16);client.publish("MBRR02/D11128",i127);
D11129.toCharArray(i128,16);client.publish("MBRR02/D11129",i128);
D11130.toCharArray(i129,16);client.publish("MBRR02/D11130",i129);
D11131.toCharArray(i130,16);client.publish("MBRR02/D11131",i130);
D11132.toCharArray(i131,16);client.publish("MBRR02/D11132",i131);
D11133.toCharArray(i132,16);client.publish("MBRR02/D11133",i132);
D11134.toCharArray(i133,16);client.publish("MBRR02/D11134",i133);
D11135.toCharArray(i134,16);client.publish("MBRR02/D11135",i134);
D11136.toCharArray(i135,16);client.publish("MBRR02/D11136",i135);
D11137.toCharArray(i136,16);client.publish("MBRR02/D11137",i136);
D11138.toCharArray(i137,16);client.publish("MBRR02/D11138",i137);
D11139.toCharArray(i138,16);client.publish("MBRR02/D11139",i138);
D11140.toCharArray(i139,16);client.publish("MBRR02/D11140",i139);
D11141.toCharArray(i140,16);client.publish("MBRR02/D11141",i140);
D11142.toCharArray(i141,16);client.publish("MBRR02/D11142",i141);
D11143.toCharArray(i142,16);client.publish("MBRR02/D11143",i142);
D11144.toCharArray(i143,16);client.publish("MBRR02/D11144",i143);
D11145.toCharArray(i144,16);client.publish("MBRR02/D11145",i144);
D11146.toCharArray(i145,16);client.publish("MBRR02/D11146",i145);
D11147.toCharArray(i146,16);client.publish("MBRR02/D11147",i146);
D11148.toCharArray(i147,16);client.publish("MBRR02/D11148",i147);
D11149.toCharArray(i148,16);client.publish("MBRR02/D11149",i148);
D11150.toCharArray(i149,16);client.publish("MBRR02/D11150",i149);
D11151.toCharArray(i150,16);client.publish("MBRR02/D11151",i150);
D11152.toCharArray(i151,16);client.publish("MBRR02/D11152",i151);
D11153.toCharArray(i152,16);client.publish("MBRR02/D11153",i152);
D11154.toCharArray(i153,16);client.publish("MBRR02/D11154",i153);
D11155.toCharArray(i154,16);client.publish("MBRR02/D11155",i154);
D11156.toCharArray(i155,16);client.publish("MBRR02/D11156",i155);
D11157.toCharArray(i156,16);client.publish("MBRR02/D11157",i156);
D11158.toCharArray(i157,16);client.publish("MBRR02/D11158",i157);
D11159.toCharArray(i158,16);client.publish("MBRR02/D11159",i158);
D11160.toCharArray(i159,16);client.publish("MBRR02/D11160",i159);
D11221.toCharArray(i220,16);client.publish("MBRR02/D11221",i220);
D11222.toCharArray(i221,16);client.publish("MBRR02/D11222",i221);
D11223.toCharArray(i222,16);client.publish("MBRR02/D11223",i222);
D11224.toCharArray(i223,16);client.publish("MBRR02/D11224",i223);
D11225.toCharArray(i224,16);client.publish("MBRR02/D11225",i224);
D11226.toCharArray(i225,16);client.publish("MBRR02/D11226",i225);
D11227.toCharArray(i226,16);client.publish("MBRR02/D11227",i226);
D11228.toCharArray(i227,16);client.publish("MBRR02/D11228",i227);
D11229.toCharArray(i228,16);client.publish("MBRR02/D11229",i228);
D11230.toCharArray(i229,16);client.publish("MBRR02/D11230",i229);
rssi.toCharArray(i_rssi,16);client.publish("MBRR02/rssi",i_rssi);

  
  Serial.println("\n---------------finish loop------------------\n\n");
  delay(5000);
}

int to_Negetive(int ne)
{ 
  if(ne>35000)
  {
    ne = ne-65536;
  }
  return ne;
}

String convertDecimalToHex(long n) {
 
  String hexNum;
  long remainder;
 
  while (n > 0) {
 
    remainder = n % 16;
    n = n / 16;
 
    if (remainder < 10) {
      hexNum = String(remainder) + hexNum;
    }
 
    else {
     
      switch (remainder) {
     
        case 10:
          hexNum = "A" + hexNum;
          break;
 
        case 11:
          hexNum = "B" + hexNum;
          break;
 
        case 12:
          hexNum = "C" + hexNum;
          break;
 
        case 13:
          hexNum = "D" + hexNum;
          break;
 
        case 14:
          hexNum = "E" + hexNum;
          break;
 
        case 15:
          hexNum = "F" + hexNum;
          break;
 
      }
 
    }
 
  }
  String hexf = hexNum.substring(0,1);
  String hex1 = hexNum.substring(2,4);
  String hex2 = hexNum.substring(0,2);
  String hex;
  if( hexf != "D")
  {
     hex = hex1+hex2;
  }
  if(hexf == "D")
  {
    hex = hexNum.substring(1,3);
    //hex = " ";
  }
 /* Serial.print("hexNum : ");Serial.println(hexNum);
  Serial.print("hexf : ");Serial.println(hexf);
  Serial.print("hex1 : ");Serial.println(hex1);
  Serial.print("hex2 : ");Serial.println(hex2);
  Serial.print("hex  : ");Serial.println(hex); */
  return hex;
 
}

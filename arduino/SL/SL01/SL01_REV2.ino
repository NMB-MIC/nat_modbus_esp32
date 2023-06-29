#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <PubSubClient.h>
#include <ModbusMaster.h>

ModbusMaster node;

//#define led_connection 42
//#define led_run 41

#define rgb_red 41
#define rgb_green 42
#define rgb_blue 45

const char* ssid = "GD_OP";
const char* password = "natmms22";
//const char* ssid = "TP-Link_EF46";
//const char* password = "98148813";
const char* mqtt_server = "192.168.4.2";

IPAddress local_IP(192, 168, 4, 161); // Static IP address192.168.100.164
IPAddress gateway(192, 168, 4, 1);    // Gateway IP address
IPAddress subnet(255, 255, 255, 0);     // subnet

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
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) 
  {
    count_connection++;
    delay(500);
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
  while (!client.connected()) 
  {
    led_red();
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
  pinMode(rgb_red, OUTPUT);
  pinMode(rgb_green, OUTPUT);
  pinMode(rgb_blue, OUTPUT);
  //pinMode ( led_connection , OUTPUT);
  //pinMode ( led_run, OUTPUT);
  Serial.println("Booting");
  setup_wifi(); 

  // Port defaults to 3232
  // ArduinoOTA.setPort(3232);

  // Hostname defaults to esp3232-[MAC]
  ArduinoOTA.setHostname("SL01");

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

String rssi,d1200,d1202,d1204,d1206,d1208,d1210,d1212,d1214,d1216,d1218,d1220,d1222,d1224,d1226,d1228,d1230,d1232,d1234,d1236,d1238,d_sum;
char i_rssi[16],i0[16],i1[16],i2[16],i3[16],i4[16],i5[16],i6[16],i7[16],i8[16],i9[16],i10[16],i11[16],i12[16],i13[16],i14[16],i15[16],i16[16],i17[16],i18[16],i19[16],i20[32];
int total_sum;

void loop() 
{
  rssi = WiFi.RSSI();
  //Serial.print(WiFi.RSSI()); 
  ArduinoOTA.handle();
  if (!client.connected()) 
  {
    reconnect();
  }
  client.loop();
  led_green();
  //digitalWrite(led_connection, HIGH);
  Serial.println("\n---------------starting loop----------------");

  node.readHoldingRegisters(0, 1); 
  Serial.print("d1200 : ");
  Serial.println(node.getResponseBuffer(0));
  d1200 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(1, 1); 
  Serial.print("d1202 : ");
  Serial.println(node.getResponseBuffer(0));
  d1202 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(2, 1); 
  Serial.print("d1204 : ");
  Serial.println(node.getResponseBuffer(0));
  d1204 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(3, 1); 
  Serial.print("d1206 : ");
  Serial.println(node.getResponseBuffer(0));
  d1206 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(4, 1); 
  Serial.print("d1208 : ");
  Serial.println(node.getResponseBuffer(0));
  d1208 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(5, 1); 
  Serial.print("d1210 : ");
  Serial.println(node.getResponseBuffer(0));
  d1210 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(6, 1); 
  Serial.print("d1212 : ");
  Serial.println(node.getResponseBuffer(0));
  d1212 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(7, 1); 
  Serial.print("d1214 : ");
  Serial.println(node.getResponseBuffer(0));
  d1214 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(8, 1); 
  Serial.print("d1216 : ");
  Serial.println(node.getResponseBuffer(0));
  d1216 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(9, 1); 
  Serial.print("d1218 : ");
  Serial.println(node.getResponseBuffer(0));
  d1218 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(10, 1); 
  Serial.print("d1220 : ");
  Serial.println(node.getResponseBuffer(0));
  d1220 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(11, 1); 
  Serial.print("d1222 : ");
  Serial.println(node.getResponseBuffer(0));
  d1222 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(12, 1); 
  Serial.print("d1224 : ");
  Serial.println(node.getResponseBuffer(0));
  d1224 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(13, 1); 
  Serial.print("d1226 : ");
  Serial.println(node.getResponseBuffer(0));
  d1226 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(14, 1); 
  Serial.print("d1228 : ");
  Serial.println(node.getResponseBuffer(0));
  d1228 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(15, 1); 
  Serial.print("d1230 : ");
  Serial.println(node.getResponseBuffer(0));
  d1230 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(16, 1); 
  Serial.print("d1232 : ");
  Serial.println(node.getResponseBuffer(0));
  d1232 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(17, 1); 
  Serial.print("d1234 : ");
  Serial.println(node.getResponseBuffer(0));
  d1234 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(18, 1); 
  Serial.print("d1236 : ");
  Serial.println(node.getResponseBuffer(0));
  d1236 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(19, 1); 
  Serial.print("d1238 : ");
  Serial.println(node.getResponseBuffer(0));
  d1238 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  delay(500);
  led_blue();
  
  rssi.toCharArray(i_rssi, 16);client.publish("SL01/rssi", i_rssi);
  d1200.toCharArray(i0, 16);client.publish("SL01/D1200", i0);
  d1202.toCharArray(i1, 16);client.publish("SL01/D1202", i1);
  d1204.toCharArray(i2, 16);client.publish("SL01/D1204", i2);
  d1206.toCharArray(i3, 16);client.publish("SL01/D1206", i3);
  d1208.toCharArray(i4, 16);client.publish("SL01/D1208", i4);
  d1210.toCharArray(i5, 16);client.publish("SL01/D1210", i5);
  d1212.toCharArray(i6, 16);client.publish("SL01/D1212", i6);
  d1214.toCharArray(i7, 16);client.publish("SL01/D1214", i7);
  d1216.toCharArray(i8, 16);client.publish("SL01/D1216", i8);
  d1218.toCharArray(i9, 16);client.publish("SL01/D1218", i9);
  d1220.toCharArray(i10, 16);client.publish("SL01/D1220", i10);
  d1222.toCharArray(i11, 16);client.publish("SL01/D1222", i11);
  d1224.toCharArray(i12, 16);client.publish("SL01/D1224", i12);
  d1226.toCharArray(i13, 16);client.publish("SL01/D1226", i13);
  d1228.toCharArray(i14, 16);client.publish("SL01/D1228", i14);
  d1230.toCharArray(i15, 16);client.publish("SL01/D1230", i15);
  d1232.toCharArray(i16, 16);client.publish("SL01/D1232", i16);
  d1234.toCharArray(i17, 16);client.publish("SL01/D1234", i17);
  d1236.toCharArray(i18, 16);client.publish("SL01/D1236", i18);
  d1238.toCharArray(i19, 16);client.publish("SL01/D1238", i19);
/*
///////////////////////////// TOTAL /////////////////////////////////////
  total_sum = int(i0); //+ int(i1) + int(i2) + int(i3) + int(i4) + int(i5) + int(i6) + int(i7) + int(i8) + int(i9) + int(i10) + int(i11) + int(i12) + int(i13) + int(i14) + int(i15) + int(i16) + int(i17) + int(i18) + int(i19);
  d_sum = String(total_sum);
  Serial.print("d_sum : ");
  Serial.println(d_sum);
  Serial.print("total : ");
  Serial.println(total_sum);
  d_sum.toCharArray(i20, 32);client.publish("SL01/D_SUM", i20);
///////////////////////////// TOTAL /////////////////////////////////////
   */ 
  Serial.println("\n---------------finish loop------------------\n\n");
  delay(5000);
}

void led_red()
{
  digitalWrite(rgb_red, LOW); digitalWrite(rgb_green, HIGH); digitalWrite(rgb_blue, HIGH);  
}

void led_green()
{
  digitalWrite(rgb_red, HIGH); digitalWrite(rgb_green, LOW); digitalWrite(rgb_blue, HIGH);  
}

void led_blue()
{
  digitalWrite(rgb_red, HIGH); digitalWrite(rgb_green, HIGH); digitalWrite(rgb_blue, LOW);  
}

void rgb_off()
{
  digitalWrite(rgb_red, HIGH); digitalWrite(rgb_green, HIGH); digitalWrite(rgb_blue, HIGH);
}

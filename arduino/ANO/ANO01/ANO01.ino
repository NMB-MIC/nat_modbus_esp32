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

const char* ssid = "DX_Project";
const char* password = "natmms22";
//const char* ssid = "TP-Link_EF46";
//const char* password = "98148813";
const char* mqtt_server = "192.168.1.2";

IPAddress local_IP(192, 168, 1, 41); // Static IP address192.168.100.164
IPAddress gateway(192, 168, 1, 1);    // Gateway IP address
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
  if (!client.connected()) 
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
  ArduinoOTA.setHostname("AN01");

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

String rssi,d3162,d3102,d3166,d3106,d3168,d3108,d3170,d3110,d51,gd10,d3262,d3202,d3266,d3206,d3268,d3208,d3270,d3210,d52,gd12,d416,d436;
char d_rssi[16],d0[16],d1[16],d2[16],d3[16],d4[16],d5[16],d6[16],d7[16],d8[16],d9[16],d10[16],d11[16],d12[16],d13[16],d14[16],d15[16],d16[16],d17[16],d18[16],d19[16],d20[16],d21[16];


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
  Serial.print("d3162 : ");
  Serial.println(node.getResponseBuffer(0));
  d3162 = node.getResponseBuffer(0);
  node.clearResponseBuffer();
  
  node.readHoldingRegisters(1, 1); 
  Serial.print("d3102 : ");
  Serial.println(node.getResponseBuffer(0));
  d3102 = node.getResponseBuffer(0);
  node.clearResponseBuffer();
  
  node.readHoldingRegisters(2, 1); 
  Serial.print("d3166 : ");
  Serial.println(node.getResponseBuffer(0));
  d3166 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(3, 1); 
  Serial.print("d3106 : ");
  Serial.println(node.getResponseBuffer(0));
  d3106 = node.getResponseBuffer(0);
  node.clearResponseBuffer();
  
  node.readHoldingRegisters(4, 1); 
  Serial.print("d3168 : ");
  Serial.println(node.getResponseBuffer(0));
  d3168 = node.getResponseBuffer(0);
  node.clearResponseBuffer();
  
  node.readHoldingRegisters(5, 1); 
  Serial.print("d3108 : ");
  Serial.println(node.getResponseBuffer(0));
  d3108 = node.getResponseBuffer(0);
  node.clearResponseBuffer();
  
  node.readHoldingRegisters(6, 1); 
  Serial.print("d3170 : ");
  Serial.println(node.getResponseBuffer(0));
  d3170 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(7, 1); 
  Serial.print("d3110 : ");
  Serial.println(node.getResponseBuffer(0));
  d3110 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(8, 1); 
  Serial.print("d51 : ");
  Serial.println(node.getResponseBuffer(0));
  d51 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(9, 1); 
  Serial.print("gd10 : ");
  Serial.println(node.getResponseBuffer(0));
  gd10 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(10, 1); 
  Serial.print("d3262 : ");
  Serial.println(node.getResponseBuffer(0));
  d3262 = node.getResponseBuffer(0);
  node.clearResponseBuffer();
  
  node.readHoldingRegisters(11, 1); 
  Serial.print("d3202 : ");
  Serial.println(node.getResponseBuffer(0));
  d3202 = node.getResponseBuffer(0);
  node.clearResponseBuffer();
  
  node.readHoldingRegisters(12, 1); 
  Serial.print("d3266 : ");
  Serial.println(node.getResponseBuffer(0));
  d3266 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(13, 1); 
  Serial.print("d3206 : ");
  Serial.println(node.getResponseBuffer(0));
  d3206 = node.getResponseBuffer(0);
  node.clearResponseBuffer();
  
  node.readHoldingRegisters(14, 1); 
  Serial.print("d3268 : ");
  Serial.println(node.getResponseBuffer(0));
  d3268 = node.getResponseBuffer(0);
  node.clearResponseBuffer();
  
  node.readHoldingRegisters(15, 1); 
  Serial.print("d3208 : ");
  Serial.println(node.getResponseBuffer(0));
  d3208 = node.getResponseBuffer(0);
  node.clearResponseBuffer();
  
  node.readHoldingRegisters(16, 1); 
  Serial.print("d3270 : ");
  Serial.println(node.getResponseBuffer(0));
  d3270 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(17, 1); 
  Serial.print("d3210 : ");
  Serial.println(node.getResponseBuffer(0));
  d3210 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(18, 1); 
  Serial.print("d52 : ");
  Serial.println(node.getResponseBuffer(0));
  d52 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(19, 1); 
  Serial.print("gd12 : ");
  Serial.println(node.getResponseBuffer(0));
  gd12 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(20, 1); 
  Serial.print("d416 : ");
  Serial.println(node.getResponseBuffer(0));
  d416 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(21, 1); 
  Serial.print("d436 : ");
  Serial.println(node.getResponseBuffer(0));
  d436 = node.getResponseBuffer(0);
  node.clearResponseBuffer();
  
  delay(500);
  led_blue();
  rssi.toCharArray(d_rssi, 16);client.publish("AN01/rssi", d_rssi);
  d3162.toCharArray(d0, 16);client.publish("AN01/D3162", d0);
  d3102.toCharArray(d1, 16);client.publish("AN01/D3102", d1);
  d3166.toCharArray(d2, 16);client.publish("AN01/D3166", d2);
  d3106.toCharArray(d3, 16);client.publish("AN01/D3106", d3);
  d3168.toCharArray(d4, 16);client.publish("AN01/D3168", d4);
  d3108.toCharArray(d5, 16);client.publish("AN01/D3108", d5);
  d3170.toCharArray(d6, 16);client.publish("AN01/D3170", d6);
  d3110.toCharArray(d7, 16);client.publish("AN01/D3110", d7);
  d51.toCharArray(d8, 16);client.publish("AN01/D51", d8);
  gd10.toCharArray(d9, 16);client.publish("AN01/GD10", d9);

  d3262.toCharArray(d10, 16);client.publish("AN01/D3262", d10);
  d3202.toCharArray(d11, 16);client.publish("AN01/D3202", d11);
  d3266.toCharArray(d12, 16);client.publish("AN01/D3266", d12);
  d3206.toCharArray(d13, 16);client.publish("AN01/D3206", d13);
  d3268.toCharArray(d14, 16);client.publish("AN01/D3268", d14);
  d3208.toCharArray(d15, 16);client.publish("AN01/D3208", d15);
  d3270.toCharArray(d16, 16);client.publish("AN01/D3270", d16);
  d3210.toCharArray(d17, 16);client.publish("AN01/D3210", d17);
  d52.toCharArray(d18, 16);client.publish("AN01/D52", d18);
  gd12.toCharArray(d19, 16);client.publish("AN01/GD12", d19);
  d416.toCharArray(d20, 16);client.publish("AN01/D416", d20);
  d436.toCharArray(d21, 16);client.publish("AN01/D436", d21);
    
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
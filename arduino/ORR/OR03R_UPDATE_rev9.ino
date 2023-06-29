//ORR03
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <PubSubClient.h>
#include <ModbusMaster.h>

ModbusMaster node;

#define led_connection 41
#define led_run 42


const char* ssid = "GD_OP";
const char* password = "natmms22";
//const char* ssid = "TP-Link_EF46";
//const char* password = "98148813";
const char* mqtt_server = "192.168.4.2";

IPAddress local_IP(192, 168, 4, 103); // Static IP address192.168.100.164
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
  node.begin(1,Serial1);
  pinMode ( led_connection , OUTPUT);
  pinMode ( led_run, OUTPUT);
  Serial.println("Booting");
  setup_wifi(); 

  // Port defaults to 3232
  // ArduinoOTA.setPort(3232);

  // Hostname defaults to esp3232-[MAC]
  ArduinoOTA.setHostname("ORR03");

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

String rssi,zr1200,zr1232,d4000,d4002,d4004,d4006,d4008,d4010,d4012,d4014,d4016,d4018,d4020,d4022,d4024,d4026,d4028,d4030,d4032,d4034,d2754,zr900,zr836;
char i_rssi[16],i0[16],i1[16],i2[16],i3[16],i4[16],i5[16],i6[16],i7[16],i8[16],i9[16],i10[16],i11[16],i12[16],i13[16],i14[16],i15[16],i16[16],i17[16],i18[16],i19[16],i20[16],i21[16],i22[16];


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
  
  node.readHoldingRegisters(0, 1); 
  Serial.print("zr1200 : ");
  Serial.println(node.getResponseBuffer(0));
  zr1200 = node.getResponseBuffer(0);
  node.clearResponseBuffer();
  
  node.readHoldingRegisters(1, 1); 
  Serial.print("zr1232 : ");
  Serial.println(node.getResponseBuffer(0));
  zr1232 = node.getResponseBuffer(0);
  node.clearResponseBuffer();
  
  node.readHoldingRegisters(2, 1); 
  Serial.print("d4000 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4000 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(3, 1); 
  Serial.print("d4002 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4002 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(4, 1); 
  Serial.print("d4004 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4004 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(5, 1); 
  Serial.print("d4006 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4006 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(6, 1); 
  Serial.print("d4008 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4008 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(7, 1); 
  Serial.print("d4010 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4010 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(8, 1); 
  Serial.print("d4012 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4012 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(9, 1); 
  Serial.print("d4014 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4014 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(10, 1); 
  Serial.print("d4016 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4016 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(11, 1); 
  Serial.print("d4018 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4018 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(12, 1); 
  Serial.print("d4020 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4020 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(13, 1); 
  Serial.print("d4022 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4022 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(14, 1); 
  Serial.print("d4024 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4024 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(15, 1); 
  Serial.print("d4026 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4026 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(16, 1); 
  Serial.print("d4028 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4028 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(17, 1); 
  Serial.print("d4030 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4030 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(18, 1); 
  Serial.print("d4032 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4032 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(19, 1); 
  Serial.print("d4034 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4034 = node.getResponseBuffer(0); 
  node.clearResponseBuffer();

 node.readHoldingRegisters(20, 1); 
  Serial.print("d2754 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d2754 = node.getResponseBuffer(0); 
  node.clearResponseBuffer();

 node.readHoldingRegisters(21, 1); 
  Serial.print("zr900 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  zr900 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(22, 1); 
  Serial.print("zr836 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  zr836 = node.getResponseBuffer(0); 
  node.clearResponseBuffer();
  
  delay(500);
  digitalWrite(led_run, HIGH);  
  
  zr1200.toCharArray(i0, 16);client.publish("ORR03/ZR1200", i0);
  zr1232.toCharArray(i1, 16);client.publish("ORR03/ZR1232", i1);
  d4000.toCharArray(i2, 16);client.publish("ORR03/D4000", i2);
  d4002.toCharArray(i3, 16);client.publish("ORR03/D4002", i3);
  d4004.toCharArray(i4, 16);client.publish("ORR03/D4004", i4);
  d4006.toCharArray(i5, 16);client.publish("ORR03/D4006", i5);
  d4008.toCharArray(i6, 16);client.publish("ORR03/D4008", i6);
  d4010.toCharArray(i7, 16);client.publish("ORR03/D4010", i7);
  d4012.toCharArray(i8, 16);client.publish("ORR03/D4012", i8);
  d4014.toCharArray(i9, 16);client.publish("ORR03/D4014", i9);
  d4016.toCharArray(i10, 16);client.publish("ORR03/D4016", i10);
  d4018.toCharArray(i11, 16);client.publish("ORR03/D4018", i11);
  d4020.toCharArray(i12, 16);client.publish("ORR03/D4020", i12);
  d4022.toCharArray(i13, 16);client.publish("ORR03/D4022", i13);
  d4024.toCharArray(i14, 16);client.publish("ORR03/D4024", i14);
  d4026.toCharArray(i15, 16);client.publish("ORR03/D4026", i15);
  d4028.toCharArray(i16, 16);client.publish("ORR03/D4028", i16);
  d4030.toCharArray(i17, 16);client.publish("ORR03/D4030", i17);
  d4032.toCharArray(i18, 16);client.publish("ORR03/D4032", i18);
  d4034.toCharArray(i19, 16);client.publish("ORR03/D4034", i19);
  rssi.toCharArray(i_rssi, 16);client.publish("ORR03/rssi", i_rssi);
  d2754.toCharArray(i20, 16);client.publish("ORR03/D2754", i20);
  zr900.toCharArray(i21, 16);client.publish("ORR03/ZR900", i21);
  zr836.toCharArray(i22, 16);client.publish("ORR03/ZR836", i22); 
  
  Serial.println("\n---------------finish loop------------------\n\n");
  delay(5000);
}

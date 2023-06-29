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

IPAddress local_IP(192, 168, 4, 42); // Static IP address192.168.100.164
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
  ArduinoOTA.setHostname("IRB02");

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

String rssi,zr1410,zr1414,zr1416,zr524,zr544,zr564,zr624,zr644,zr664,zr724,zr744,zr764,d5200,d5220,d5240,d4000,d4002,d4004,d4006,d4008,d4010,d4012,d4014,d4016,d4018,d4020,d4022,d4024,d4026,d4028,d4030,d4032,d4034,d4036,d4038,d2754,zr900,zr836,m901,m902;
char i_rssi[16],i0[16],i1[16],i2[16],i3[16],i4[16],i5[16],i6[16],i7[16],i8[16],i9[16],i10[16],i11[16],i12[16],i13[16],i14[16],i15[16],i16[16],i17[16],i18[16],i19[16],i20[16],i21[16],i22[16],i23[16],i24[16],i25[16],i26[16],i27[16],i28[16],i29[16],i30[16],i31[16],i32[16],i33[16],i34[16],i35[16],i36[16],i37[16],i38[16],i39[16];


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
  Serial.print("zr1410 : ");
  Serial.println(node.getResponseBuffer(0));
  zr1410 = node.getResponseBuffer(0);
  node.clearResponseBuffer();
  
  node.readHoldingRegisters(1, 1); 
  Serial.print("zr1414 : ");
  Serial.println(node.getResponseBuffer(0));
  zr1414 = node.getResponseBuffer(0);
  node.clearResponseBuffer();
  
  node.readHoldingRegisters(2, 1); 
  Serial.print("zr1416 : ");
  Serial.println(node.getResponseBuffer(0));
  zr1416 = node.getResponseBuffer(0);
  node.clearResponseBuffer();
  
  
  node.readHoldingRegisters(3, 1); 
  Serial.print("zr524 : ");
  Serial.println(node.getResponseBuffer(0));
  zr524 = node.getResponseBuffer(0);
  node.clearResponseBuffer();
  
  node.readHoldingRegisters(4, 1); 
  Serial.print("zr544 : ");
  Serial.println(node.getResponseBuffer(0));
  zr544 = node.getResponseBuffer(0);
  node.clearResponseBuffer();
  
  node.readHoldingRegisters(5, 1); 
  Serial.print("zr564 : ");
  Serial.println(node.getResponseBuffer(0));
  zr564 = node.getResponseBuffer(0);
  node.clearResponseBuffer();
  
  node.readHoldingRegisters(6, 1); 
  Serial.print("zr624 : ");
  Serial.println(node.getResponseBuffer(0));
  zr624 = node.getResponseBuffer(0);
  node.clearResponseBuffer();
  
  node.readHoldingRegisters(7, 1); 
  Serial.print("zr644 : ");
  Serial.println(node.getResponseBuffer(0));
  zr644 = node.getResponseBuffer(0);
  node.clearResponseBuffer();
  
  node.readHoldingRegisters(8, 1); 
  Serial.print("zr664 : ");
  Serial.println(node.getResponseBuffer(0));
  zr664 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(9, 1); 
  Serial.print("zr724 : ");
  Serial.println(node.getResponseBuffer(0));
  zr724 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(10, 1); 
  Serial.print("zr744 : ");
  Serial.println(node.getResponseBuffer(0));
  zr744 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(11, 1); 
  Serial.print("zr764 : ");
  Serial.println(node.getResponseBuffer(0));
  zr764 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(12, 1); 
  Serial.print("d5200 : ");
  Serial.println(node.getResponseBuffer(0));
  d5200 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(13, 1); 
  Serial.print("d5220 : ");
  Serial.println(node.getResponseBuffer(0));
  d5220 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(14, 1); 
  Serial.print("d5240 : ");
  Serial.println(node.getResponseBuffer(0));
  d5240 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

 node.readHoldingRegisters(15, 1); 
  Serial.print("d4000 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4000 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(16, 1); 
  Serial.print("d4002 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4002 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(17, 1); 
  Serial.print("d4004 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4004 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(18, 1); 
  Serial.print("d4006 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4006 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(19, 1); 
  Serial.print("d4008 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4008 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(20, 1); 
  Serial.print("d4010 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4010 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(21, 1); 
  Serial.print("d4012 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4012 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(22, 1); 
  Serial.print("d4014 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4014 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(23, 1); 
  Serial.print("d4016 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4016 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(24, 1); 
  Serial.print("d4018 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4018 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(25, 1); 
  Serial.print("d4020 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4020 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(26, 1); 
  Serial.print("d4022 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4022 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(27, 1); 
  Serial.print("d4024 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4024 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(28, 1); 
  Serial.print("d4026 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4026 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(29, 1); 
  Serial.print("d4028 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4028 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(30, 1); 
  Serial.print("d4030 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4030 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(31, 1); 
  Serial.print("d4032 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4032 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(32, 1); 
  Serial.print("d4034 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4034 = node.getResponseBuffer(0); 
  node.clearResponseBuffer();

 node.readHoldingRegisters(33, 1); 
  Serial.print("d4036 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4036 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(34, 1); 
  Serial.print("d4038 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4038 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(35, 1); 
  Serial.print("d2754 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d2754 = node.getResponseBuffer(0); 
  node.clearResponseBuffer();

 node.readHoldingRegisters(36, 1); 
  Serial.print("zr900 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  zr900 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(37, 1); 
  Serial.print("zr836 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  zr836 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

  node.readCoils(38, 1); 
  Serial.print("M901 : ");
  Serial.println(node.getResponseBuffer(0));
  m901 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readCoils(39, 1); 
  Serial.print("M902 : ");
  Serial.println(node.getResponseBuffer(0));
  m902 = node.getResponseBuffer(0);
  node.clearResponseBuffer();
  
  delay(500);
  led_blue();
  
  rssi.toCharArray(i_rssi, 16);client.publish("IRB02/rssi", i_rssi);
  zr1410.toCharArray(i0, 16);client.publish("IRB02/ZR1410", i0);
  zr1414.toCharArray(i1, 16);client.publish("IRB02/ZR1414", i1);
  zr1416.toCharArray(i2, 16);client.publish("IRB02/ZR1416", i2);
  zr524.toCharArray(i3, 16);client.publish("IRB02/ZR524", i3);
  zr544.toCharArray(i4, 16);client.publish("IRB02/ZR544", i4);
  zr564.toCharArray(i5, 16);client.publish("IRB02/ZR564", i5);
  zr624.toCharArray(i6, 16);client.publish("IRB02/ZR624", i6);
  zr644.toCharArray(i7, 16);client.publish("IRB02/ZR644", i7);
  zr664.toCharArray(i8, 16);client.publish("IRB02/ZR664", i8);
  zr724.toCharArray(i9, 16);client.publish("IRB02/ZR724", i9);
  zr744.toCharArray(i10, 16);client.publish("IRB02/ZR744", i10);
  zr764.toCharArray(i11, 16);client.publish("IRB02/ZR764", i11);
  d5200.toCharArray(i12, 16);client.publish("IRB02/D5200", i12);
  d5220.toCharArray(i13, 16);client.publish("IRB02/D5220", i13);
  d5240.toCharArray(i14, 16);client.publish("IRB02/D5240", i14);
  d4000.toCharArray(i15, 16);client.publish("IRB02/D4000", i15);
  d4002.toCharArray(i16, 16);client.publish("IRB02/D4002", i16);
  d4004.toCharArray(i17, 16);client.publish("IRB02/D4004", i17);
  d4006.toCharArray(i18, 16);client.publish("IRB02/D4006", i18);
  d4008.toCharArray(i19, 16);client.publish("IRB02/D4008", i19);
  d4010.toCharArray(i20, 16);client.publish("IRB02/D4010", i20);
  d4012.toCharArray(i21, 16);client.publish("IRB02/D4012", i21);
  d4014.toCharArray(i22, 16);client.publish("IRB02/D4014", i22);
  d4016.toCharArray(i23, 16);client.publish("IRB02/D4016", i23);
  d4018.toCharArray(i24, 16);client.publish("IRB02/D4018", i24);
  d4020.toCharArray(i25, 16);client.publish("IRB02/D4020", i25);
  d4022.toCharArray(i26, 16);client.publish("IRB02/D4022", i26);
  d4024.toCharArray(i27, 16);client.publish("IRB02/D4024", i27);
  d4026.toCharArray(i28, 16);client.publish("IRB02/D4026", i28);
  d4028.toCharArray(i29, 16);client.publish("IRB02/D4028", i29);
  d4030.toCharArray(i30, 16);client.publish("IRB02/D4030", i30);
  d4032.toCharArray(i31, 16);client.publish("IRB02/D4032", i31);
  d4034.toCharArray(i32, 16);client.publish("IRB02/D4034", i32);
  d4036.toCharArray(i33, 16);client.publish("IRB02/D4036", i33);
  d4038.toCharArray(i34, 16);client.publish("IRB02/D4038", i34);
  d2754.toCharArray(i35, 16);client.publish("IRB02/D2754", i35);
  zr900.toCharArray(i36, 16);client.publish("IRB02/ZR900", i36);
  zr836.toCharArray(i37, 16);client.publish("IRB02/ZR836", i37);
  m901.toCharArray(i38, 16);client.publish("IRB02/M901", i38);
  m902.toCharArray(i39, 16);client.publish("IRB02/M902", i39);  
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

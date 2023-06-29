//TB01
//change ssid,password,mqtt_server,local_IP,setHostname,String rssi,char i_rssi,client.publish

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

const char* ssid = "DX_Project"; // ******Change ssid wifi *********
const char* password = "natmms22"; // ****** Change password *********
//const char* ssid = "TP-Link_EF46";
//const char* password = "98148813";
const char* mqtt_server = "192.168.1.2";  // ****** mqtt server *********

IPAddress local_IP(192, 168, 1, 31); // ******Change ip *********
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
  ArduinoOTA.setHostname("TB01");

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

String rssi,M34,D330,D332,D334,D336,D338,D340,D342,D344,D346,D348,D350,D226,D100,D102,D104,D106,D108,D110,D112,D114,M36,D362,D364,D368,D370,D356,D372,D354,D366,D116,D122,D126,D128,D118,D120,D124,D286,D32,D500,B9,D708,D608,D508,DB1,DB2,DB6,M205,D60,D1366,D1368,D1370,D1372,D1374,D1376,D1378,D1380,D1266,D1268;
char i_rssi[16],i0[16],i1[16],i2[16],i3[16],i4[16],i5[16],i6[16],i7[16],i8[16],i9[16],i10[16],i11[16],i12[16],i13[16],i14[16],i15[16],i16[16],i17[16],i18[16],i19[16],i20[16],i21[16],i22[16],i23[16],i24[16],i25[16],i26[16],i27[16],i28[16],i29[16],i30[16],i31[16],i32[16],i33[16],i34[16],i35[16],i36[16],i37[16],i38[16],i39[16],i40[16],i41[16],i42[16],i43[16],i44[16],i45[16],i46[16],i47[16],i48[16],i49[16],i50[16],i51[16],i52[16],i53[16],i54[16],i55[16],i56[16],i57[16],i58[16];

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

  node.readCoils(0, 1); 
  Serial.print("M34 : ");
  Serial.println(node.getResponseBuffer(0));
  M34 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readCoils(1, 1); 
  Serial.print("M36 : ");
  Serial.println(node.getResponseBuffer(0));
  M36 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readCoils(2, 1); 
  Serial.print("B9 : ");
  Serial.println(node.getResponseBuffer(0));
  B9 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readCoils(3, 1); 
  Serial.print("DB1 : ");
  Serial.println(node.getResponseBuffer(0));
  DB1 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readCoils(4, 1); 
  Serial.print("DB2 : ");
  Serial.println(node.getResponseBuffer(0));
  DB2 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readCoils(5, 1); 
  Serial.print("DB6 : ");
  Serial.println(node.getResponseBuffer(0));
  DB6 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

      node.readCoils(6, 1); 
  Serial.print("M205 : ");
  Serial.println(node.getResponseBuffer(0));
  M205 = node.getResponseBuffer(0);
  node.clearResponseBuffer();


  node.readHoldingRegisters(0, 1); 
  Serial.print("D330 : ");
  Serial.println(node.getResponseBuffer(0));
  D330 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(1, 1); 
  Serial.print("D332 : ");
  Serial.println(node.getResponseBuffer(0));
  D332 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(2, 1); 
  Serial.print("D334 : ");
  Serial.println(node.getResponseBuffer(0));
  D334 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(3, 1); 
  Serial.print("D336 : ");
  Serial.println(node.getResponseBuffer(0));
  D336 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(4, 1); 
  Serial.print("D338 : ");
  Serial.println(node.getResponseBuffer(0));
  D338 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(5, 1); 
  Serial.print("D340 : ");
  Serial.println(node.getResponseBuffer(0));
  D340 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(6, 1); 
  Serial.print("D342 : ");
  Serial.println(node.getResponseBuffer(0));
  D342 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(7, 1); 
  Serial.print("D344 : ");
  Serial.println(node.getResponseBuffer(0));
  D344 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(8, 1); 
  Serial.print("D346 : ");
  Serial.println(node.getResponseBuffer(0));
  D346 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(9, 1); 
  Serial.print("D348 : ");
  Serial.println(node.getResponseBuffer(0));
  D348 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(10, 1); 
  Serial.print("D350 : ");
  Serial.println(node.getResponseBuffer(0));
  D350 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(11, 1); 
  Serial.print("D226 : ");
  Serial.println(node.getResponseBuffer(0));
  D226 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(12, 1); 
  Serial.print("D100 : ");
  Serial.println(node.getResponseBuffer(0));
  D100 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(13, 1); 
  Serial.print("D102 : ");
  Serial.println(node.getResponseBuffer(0));
  D102 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(14, 1); 
  Serial.print("D104 : ");
  Serial.println(node.getResponseBuffer(0));
  D104 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(15, 1); 
  Serial.print("D106 : ");
  Serial.println(node.getResponseBuffer(0));
  D106 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(16, 1); 
  Serial.print("D108 : ");
  Serial.println(node.getResponseBuffer(0));
  D108 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(17, 1); 
  Serial.print("D110 : ");
  Serial.println(node.getResponseBuffer(0));
  D110 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(18, 1); 
  Serial.print("D112 : ");
  Serial.println(node.getResponseBuffer(0));
  D112 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(19, 1); 
  Serial.print("D114 : ");
  Serial.println(node.getResponseBuffer(0));
  D114 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(20, 1); 
  Serial.print("D362 : ");
  Serial.println(node.getResponseBuffer(0));
  D362 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(21, 1); 
  Serial.print("D364 : ");
  Serial.println(node.getResponseBuffer(0));
  D364 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(22, 1); 
  Serial.print("D368 : ");
  Serial.println(node.getResponseBuffer(0));
  D368 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(23, 1); 
  Serial.print("D370 : ");
  Serial.println(node.getResponseBuffer(0));
  D370 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(24, 1); 
  Serial.print("D356 : ");
  Serial.println(node.getResponseBuffer(0));
  D356 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(25, 1); 
  Serial.print("D372 : ");
  Serial.println(node.getResponseBuffer(0));
  D372 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(26, 1); 
  Serial.print("D354 : ");
  Serial.println(node.getResponseBuffer(0));
  D354 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(27, 1); 
  Serial.print("D366 : ");
  Serial.println(node.getResponseBuffer(0));
  D366 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(28, 1); 
  Serial.print("D116 : ");
  Serial.println(node.getResponseBuffer(0));
  D116 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(29, 1); 
  Serial.print("D122 : ");
  Serial.println(node.getResponseBuffer(0));
  D122 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(30, 1); 
  Serial.print("D126 : ");
  Serial.println(node.getResponseBuffer(0));
  D126 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(31, 1); 
  Serial.print("D128 : ");
  Serial.println(node.getResponseBuffer(0));
  D128 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(32, 1); 
  Serial.print("D118 : ");
  Serial.println(node.getResponseBuffer(0));
  D118 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(33, 1); 
  Serial.print("D120 : ");
  Serial.println(node.getResponseBuffer(0));
  D120 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(34, 1); 
  Serial.print("D124 : ");
  Serial.println(node.getResponseBuffer(0));
  D124 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(35, 1); 
  Serial.print("D286 : ");
  Serial.println(node.getResponseBuffer(0));
  D286 = node.getResponseBuffer(0);
  node.clearResponseBuffer();
  
  node.readHoldingRegisters(36, 1); 
  Serial.print("D32 : ");
  Serial.println(node.getResponseBuffer(0));
  D32 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(37, 1); 
  Serial.print("D500 : ");
  Serial.println(node.getResponseBuffer(0));
  D500 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(38, 1); 
  Serial.print("D708 : ");
  Serial.println(node.getResponseBuffer(0));
  D708 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(39, 1); 
  Serial.print("D608 : ");
  Serial.println(node.getResponseBuffer(0));
  D608 = node.getResponseBuffer(0);
  node.clearResponseBuffer();  

  node.readHoldingRegisters(40, 1); 
  Serial.print("D508 : ");
  Serial.println(node.getResponseBuffer(0));
  D508 = node.getResponseBuffer(0);
  node.clearResponseBuffer(); 

  node.readHoldingRegisters(41, 1); 
  Serial.print("D60 : ");
  Serial.println(node.getResponseBuffer(0));
  D60 = node.getResponseBuffer(0);
  node.clearResponseBuffer(); 

  node.readHoldingRegisters(42, 1); 
  Serial.print("D1366 : ");
  Serial.println(node.getResponseBuffer(0));
  D1366 = node.getResponseBuffer(0);
  node.clearResponseBuffer(); 

  node.readHoldingRegisters(43, 1); 
  Serial.print("D1368 : ");
  Serial.println(node.getResponseBuffer(0));
  D1368 = node.getResponseBuffer(0);
  node.clearResponseBuffer(); 

  node.readHoldingRegisters(44, 1); 
  Serial.print("D1370 : ");
  Serial.println(node.getResponseBuffer(0));
  D1370 = node.getResponseBuffer(0);
  node.clearResponseBuffer(); 

  node.readHoldingRegisters(45, 1); 
  Serial.print("D1372 : ");
  Serial.println(node.getResponseBuffer(0));
  D1372 = node.getResponseBuffer(0);
  node.clearResponseBuffer(); 

  node.readHoldingRegisters(46, 1); 
  Serial.print("D1374 : ");
  Serial.println(node.getResponseBuffer(0));
  D1374 = node.getResponseBuffer(0);
  node.clearResponseBuffer(); 

  node.readHoldingRegisters(47, 1); 
  Serial.print("D1376 : ");
  Serial.println(node.getResponseBuffer(0));
  D1376 = node.getResponseBuffer(0);
  node.clearResponseBuffer(); 

  node.readHoldingRegisters(48, 1); 
  Serial.print("D1378 : ");
  Serial.println(node.getResponseBuffer(0));
  D1378 = node.getResponseBuffer(0);
  node.clearResponseBuffer(); 

  node.readHoldingRegisters(49, 1); 
  Serial.print("D1380 : ");
  Serial.println(node.getResponseBuffer(0));
  D1380 = node.getResponseBuffer(0);
  node.clearResponseBuffer(); 

  node.readHoldingRegisters(50, 1); 
  Serial.print("D1266 : ");
  Serial.println(node.getResponseBuffer(0));
  D1266 = node.getResponseBuffer(0);
  node.clearResponseBuffer(); 

  node.readHoldingRegisters(51, 1); 
  Serial.print("D1268 : ");
  Serial.println(node.getResponseBuffer(0));
  D1268 = node.getResponseBuffer(0);
  node.clearResponseBuffer(); 
  
  delay(500);
  led_blue();
  rssi.toCharArray(i_rssi, 16);client.publish("TB01/rssi", i_rssi);
  M34.toCharArray(i0, 16);client.publish("TB01/M34", i0);
  M36.toCharArray(i1, 16);client.publish("TB01/M36", i1);
  D330.toCharArray(i2, 16);client.publish("TB01/D330", i2);
  D332.toCharArray(i3, 16);client.publish("TB01/D332", i3);
  D334.toCharArray(i4, 16);client.publish("TB01/D334", i4);
  D336.toCharArray(i5, 16);client.publish("TB01/D336", i5);
  D338.toCharArray(i6, 16);client.publish("TB01/D338", i6);
  D340.toCharArray(i7, 16);client.publish("TB01/D340", i7);
  D342.toCharArray(i8, 16);client.publish("TB01/D342", i8);     
  D344.toCharArray(i9, 16);client.publish("TB01/D344", i9);
  D346.toCharArray(i10, 16);client.publish("TB01/D346", i10);
  D348.toCharArray(i11, 16);client.publish("TB01/D348", i11);
  D350.toCharArray(i12, 16);client.publish("TB01/D350", i12);
  D226.toCharArray(i13, 16);client.publish("TB01/D226", i13);
  D100.toCharArray(i14, 16);client.publish("TB01/D100", i14);
  D102.toCharArray(i15, 16);client.publish("TB01/D102", i15);
  D104.toCharArray(i16, 16);client.publish("TB01/D104", i16);
  D106.toCharArray(i17, 16);client.publish("TB01/D106", i17);
  D108.toCharArray(i18, 16);client.publish("TB01/D108", i18);
  D110.toCharArray(i19, 16);client.publish("TB01/D110", i19);  
  D112.toCharArray(i20, 16);client.publish("TB01/D112", i20); 
  D114.toCharArray(i21, 16);client.publish("TB01/D114", i21);
  D362.toCharArray(i22, 16);client.publish("TB01/D362", i22);
  D364.toCharArray(i23, 16);client.publish("TB01/D364", i23);
  D368.toCharArray(i24, 16);client.publish("TB01/D368", i24);
  D370.toCharArray(i25, 16);client.publish("TB01/D370", i25);
  D356.toCharArray(i26, 16);client.publish("TB01/D356", i26);
  D372.toCharArray(i27, 16);client.publish("TB01/D372", i27);
  D354.toCharArray(i28, 16);client.publish("TB01/D354", i28);
  D366.toCharArray(i29, 16);client.publish("TB01/D366", i29);
  D116.toCharArray(i30, 16);client.publish("TB01/D116", i30);
  D122.toCharArray(i31, 16);client.publish("TB01/D122", i31);
  D126.toCharArray(i32, 16);client.publish("TB01/D126", i32);
  D128.toCharArray(i33, 16);client.publish("TB01/D128", i33);
  D118.toCharArray(i34, 16);client.publish("TB01/D118", i34);
  D120.toCharArray(i35, 16);client.publish("TB01/D120", i35);
  D124.toCharArray(i36, 16);client.publish("TB01/D124", i36);
  D286.toCharArray(i37, 16);client.publish("TB01/D286", i37);
  D32.toCharArray(i38, 16);client.publish("TB01/D32", i38);
  D500.toCharArray(i39, 16);client.publish("TB01/D500", i39);
  B9.toCharArray(i40, 16);client.publish("TB01/B9", i40);
  D708.toCharArray(i41, 16);client.publish("TB01/D708", i41);
  D608.toCharArray(i42, 16);client.publish("TB01/D608", i42);
  D508.toCharArray(i43, 16);client.publish("TB01/D508", i43);
  DB1.toCharArray(i44, 16);client.publish("TB01/DB1", i44);
  DB2.toCharArray(i45, 16);client.publish("TB01/DB2", i45);
  DB6.toCharArray(i46, 16);client.publish("TB01/DB6", i46);
  M205.toCharArray(i47, 16);client.publish("TB01/M205", i47);
  D60.toCharArray(i48, 16);client.publish("TB01/D60", i48);
  D1366.toCharArray(i49, 16);client.publish("TB01/D1366", i49);
  D1368.toCharArray(i50, 16);client.publish("TB01/D1368", i50);
  D1370.toCharArray(i51, 16);client.publish("TB01/D1370", i51);
  D1372.toCharArray(i52, 16);client.publish("TB01/D1372", i52);
  D1372.toCharArray(i53, 16);client.publish("TB01/D1374", i53);
  D1372.toCharArray(i54, 16);client.publish("TB01/D1376", i54);
  D1372.toCharArray(i55, 16);client.publish("TB01/D1378", i55);
  D1372.toCharArray(i56, 16);client.publish("TB01/D1380", i56);
  D1372.toCharArray(i57, 16);client.publish("TB01/D1266", i57);
  D1372.toCharArray(i58, 16);client.publish("TB01/D1268", i58);
  
  
  Serial.println("\n---------------finish loop------------------\n\n");
  delay(500);
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
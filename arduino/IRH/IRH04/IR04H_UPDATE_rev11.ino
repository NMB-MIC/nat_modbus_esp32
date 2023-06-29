//IRH04
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

IPAddress local_IP(192, 168, 4, 74); // Static IP address192.168.100.164
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
  ArduinoOTA.setHostname("IRH04");

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

//String m108,m94,m76,m62,m60,m28,m26,m19,m6,m63,d330,d332,d334,d336,d338,d340,d342,d352,d344,d346,d348,d350,d32,d226;
//char d0[16],d1[16],d2[16],d3[16],d4[16],d5[16],d6[16],d7[16],d8[16],d9[16],d10[16],d11[16],d12[16],d13[16],d14[16],d15[16],d16[16],d17[16],d18[16],d19[16],d20[16],d21[16],d22[16],d23[16];
String rssi,zr2,zr6,d5210,d5230,d5250,zr532,zr552,zr572,zr632,zr652,zr672,zr732,zr752,zr772,d4000,d4002,d4004,d4006,d4008,d4010,d4012,d4014,d4016,d4018,d4020,d4022,d4024,d4026,d4028,d4030,d4032,d4034,d4036,d4038,d4040,d4042,zr0,zr30,zr32,d3000,d3002,d3004,d3006,d3008,d3020,d3022,d3024,d3026,d3028,d3012,d3032;
char i_rssi[16],i0[16],i1[16],i2[16],i3[16],i4[16],i5[16],i6[16],i7[16],i8[16],i9[16],i10[16],i11[16],i12[16],i13[16],i14[16],i15[16],i16[16],i17[16],i18[16],i19[16],i20[16],i21[16],i22[16],i23[16],i24[16],i25[16],i26[16],i27[16],i28[16],i29[16],i30[16],i31[16],i32[16],i33[16],i34[16],i35[16],i36[16],i37[16],i38[16],i39[16],i40[16],i41[16],i42[16],i43[16],i44[16],i45[16],i46[16],i47[16],i48[16],i49[16],i50[16];


void loop() 
{
  rssi = WiFi.RSSI();
  ArduinoOTA.handle();
  while (!client.connected()) 
  {
    reconnect();
  }
  client.loop();
  digitalWrite(led_connection, HIGH);  
  digitalWrite(led_run, LOW);  
  //digitalWrite(led_connection, HIGH);
  Serial.println("\n---------------starting loop----------------");
  
  node.readHoldingRegisters(0, 1); 
  Serial.print("zr2 : ");
  Serial.println(node.getResponseBuffer(0));
  zr2 = node.getResponseBuffer(0);
  node.clearResponseBuffer();
  
  node.readHoldingRegisters(1, 1); 
  Serial.print("zr6 : ");
  Serial.println(node.getResponseBuffer(0));
  zr6 = node.getResponseBuffer(0);
  node.clearResponseBuffer();
  
  node.readHoldingRegisters(2, 1); 
  Serial.print("d5210 : ");
  Serial.println(node.getResponseBuffer(0));
  d5210 = node.getResponseBuffer(0);
  node.clearResponseBuffer();
  
  node.readHoldingRegisters(3, 1); 
  Serial.print("d5230 : ");
  Serial.println(node.getResponseBuffer(0));
  d5230 = node.getResponseBuffer(0);
  node.clearResponseBuffer();
  
  node.readHoldingRegisters(4, 1); 
  Serial.print("d5250 : ");
  Serial.println(node.getResponseBuffer(0));
  d5250 = node.getResponseBuffer(0);
  node.clearResponseBuffer();
  
  node.readHoldingRegisters(5, 1); 
  Serial.print("zr532 : ");
  Serial.println(node.getResponseBuffer(0));
  zr532 = node.getResponseBuffer(0);
  node.clearResponseBuffer();
  
  node.readHoldingRegisters(6, 1); 
  Serial.print("zr552 : ");
  Serial.println(node.getResponseBuffer(0));
  zr552 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(7, 1); 
  Serial.print("zr572 : ");
  Serial.println(node.getResponseBuffer(0));
  zr572 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(8, 1); 
  Serial.print("zr632 : ");
  Serial.println(node.getResponseBuffer(0));
  zr632 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(9, 1); 
  Serial.print("zr652 : ");
  Serial.println(node.getResponseBuffer(0));
  zr652 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(10, 1); 
  Serial.print("zr672 : ");
  Serial.println(node.getResponseBuffer(0));
  zr672 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(11, 1); 
  Serial.print("zr732 : ");
  Serial.println(node.getResponseBuffer(0));
  zr732 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(12, 1); 
  Serial.print("zr752 : ");
  Serial.println(node.getResponseBuffer(0));
  zr752 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

  node.readHoldingRegisters(13, 1); 
  Serial.print("zr772 : ");
  Serial.println(node.getResponseBuffer(0));
  zr772 = node.getResponseBuffer(0);
  node.clearResponseBuffer();

 node.readHoldingRegisters(14, 1); 
  Serial.print("d4000 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4000 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(15, 1); 
  Serial.print("d4002 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4002 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(16, 1); 
  Serial.print("d4004 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4004 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(17, 1); 
  Serial.print("d4006 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4006 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(18, 1); 
  Serial.print("d4008 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4008 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(19, 1); 
  Serial.print("d4010 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4010 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(20, 1); 
  Serial.print("d4012 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4012 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(21, 1); 
  Serial.print("d4014 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4014 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(22, 1); 
  Serial.print("d4016 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4016 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(23, 1); 
  Serial.print("d4018 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4018 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(24, 1); 
  Serial.print("d4020 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4020 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(25, 1); 
  Serial.print("d4022 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4022 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(26, 1); 
  Serial.print("d4024 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4024 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(27, 1); 
  Serial.print("d4026 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4026 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(28, 1); 
  Serial.print("d4028 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4028 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(29, 1); 
  Serial.print("d4030 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4030 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(30, 1); 
  Serial.print("d4032 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4032 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(31, 1); 
  Serial.print("d4034 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4034 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(32, 1); 
  Serial.print("d4036 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4036 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(33, 1); 
  Serial.print("d4038 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4038 = node.getResponseBuffer(0); 
  node.clearResponseBuffer();

 node.readHoldingRegisters(34, 1); 
  Serial.print("d4040 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4040 = node.getResponseBuffer(0); 
  node.clearResponseBuffer(); 

 node.readHoldingRegisters(35, 1); 
  Serial.print("d4042 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d4042 = node.getResponseBuffer(0); 
  node.clearResponseBuffer();

  node.readHoldingRegisters(36, 1); 
  Serial.print("zr0 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  zr0 = node.getResponseBuffer(0); 
  node.clearResponseBuffer();

  node.readHoldingRegisters(37, 1); 
  Serial.print("zr30 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  zr30 = node.getResponseBuffer(0); 
  node.clearResponseBuffer();

  node.readHoldingRegisters(38, 1); 
  Serial.print("zr32 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  zr32 = node.getResponseBuffer(0); 
  node.clearResponseBuffer();

  node.readHoldingRegisters(39, 1); 
  Serial.print("d3000 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d3000 = node.getResponseBuffer(0); 
  node.clearResponseBuffer();

  node.readHoldingRegisters(40, 1); 
  Serial.print("d3002 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d3002 = node.getResponseBuffer(0); 
  node.clearResponseBuffer();

  node.readHoldingRegisters(41, 1); 
  Serial.print("d3004 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d3004 = node.getResponseBuffer(0); 
  node.clearResponseBuffer();

  node.readHoldingRegisters(42, 1); 
  Serial.print("d3006 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d3006 = node.getResponseBuffer(0); 
  node.clearResponseBuffer();

  node.readHoldingRegisters(43, 1); 
  Serial.print("d3008 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d3008 = node.getResponseBuffer(0); 
  node.clearResponseBuffer();

  node.readHoldingRegisters(44, 1); 
  Serial.print("d3020 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d3020 = node.getResponseBuffer(0); 
  node.clearResponseBuffer();

  node.readHoldingRegisters(45, 1); 
  Serial.print("d3022 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d3022 = node.getResponseBuffer(0); 
  node.clearResponseBuffer();

  node.readHoldingRegisters(46, 1); 
  Serial.print("d3024 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d3024 = node.getResponseBuffer(0); 
  node.clearResponseBuffer();

  node.readHoldingRegisters(47, 1); 
  Serial.print("d3026 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d3026 = node.getResponseBuffer(0); 
  node.clearResponseBuffer();

  node.readHoldingRegisters(48, 1); 
  Serial.print("d3028 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d3028 = node.getResponseBuffer(0); 
  node.clearResponseBuffer();

  node.readHoldingRegisters(49, 1); 
  Serial.print("d3012 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d3012 = node.getResponseBuffer(0); 
  node.clearResponseBuffer();

  node.readHoldingRegisters(50, 1); 
  Serial.print("d3032 : "); 
  Serial.println(node.getResponseBuffer(0)); 
  d3032 = node.getResponseBuffer(0); 
  node.clearResponseBuffer();

  delay(500);
  digitalWrite(led_run, HIGH);  
  
  zr2.toCharArray(i0, 16);client.publish("IRH04/ZR2", i0);
  zr6.toCharArray(i1, 16);client.publish("IRH04/ZR6", i1);
  d5210.toCharArray(i2, 16);client.publish("IRH04/D5210", i2);
  d5230.toCharArray(i3, 16);client.publish("IRH04/D5230", i3);
  d5250.toCharArray(i4, 16);client.publish("IRH04/D5250", i4);
  zr532.toCharArray(i5, 16);client.publish("IRH04/ZR532", i5);
  zr552.toCharArray(i6, 16);client.publish("IRH04/ZR552", i6);
  zr572.toCharArray(i7, 16);client.publish("IRH04/ZR572", i7);
  zr632.toCharArray(i8, 16);client.publish("IRH04/ZR632", i8);
  zr652.toCharArray(i9, 16);client.publish("IRH04/ZR652", i9);
  zr672.toCharArray(i10, 16);client.publish("IRH04/ZR672", i10);
  zr732.toCharArray(i11, 16);client.publish("IRH04/ZR732", i11);
  zr752.toCharArray(i12, 16);client.publish("IRH04/ZR752", i12);
  zr772.toCharArray(i13, 16);client.publish("IRH04/ZR772", i13);
  d4000.toCharArray(i14, 16);client.publish("IRH04/D4000", i14);
  d4002.toCharArray(i15, 16);client.publish("IRH04/D4002", i15);
  d4004.toCharArray(i16, 16);client.publish("IRH04/D4004", i16);
  d4006.toCharArray(i17, 16);client.publish("IRH04/D4006", i17);
  d4008.toCharArray(i18, 16);client.publish("IRH04/D4008", i18);
  d4010.toCharArray(i19, 16);client.publish("IRH04/D4010", i19);
  d4012.toCharArray(i20, 16);client.publish("IRH04/D4012", i20);
  d4014.toCharArray(i21, 16);client.publish("IRH04/D4014", i21);
  d4016.toCharArray(i22, 16);client.publish("IRH04/D4016", i22);
  d4018.toCharArray(i23, 16);client.publish("IRH04/D4018", i23);
  d4020.toCharArray(i24, 16);client.publish("IRH04/D4020", i24);
  d4022.toCharArray(i25, 16);client.publish("IRH04/D4022", i25);
  d4024.toCharArray(i26, 16);client.publish("IRH04/D4024", i26);
  d4026.toCharArray(i27, 16);client.publish("IRH04/D4026", i27);
  d4028.toCharArray(i28, 16);client.publish("IRH04/D4028", i28);
  d4030.toCharArray(i29, 16);client.publish("IRH04/D4030", i29);
  d4032.toCharArray(i30, 16);client.publish("IRH04/D4032", i30);
  d4034.toCharArray(i31, 16);client.publish("IRH04/D4034", i31);
  d4036.toCharArray(i32, 16);client.publish("IRH04/D4036", i32);
  d4038.toCharArray(i33, 16);client.publish("IRH04/D4038", i33);
  d4040.toCharArray(i34, 16);client.publish("IRH04/D4040", i34);
  d4042.toCharArray(i35, 16);client.publish("IRH04/D4042", i35);
  zr0.toCharArray(i36, 16);client.publish("IRH04/ZR0", i36);
  zr30.toCharArray(i37, 16);client.publish("IRH04/ZR30", i37);
  zr32.toCharArray(i38, 16);client.publish("IRH04/ZR32", i38);
  d3000.toCharArray(i39, 16);client.publish("IRH04/D3000", i39);
  d3002.toCharArray(i40, 16);client.publish("IRH04/D3002", i40);
  d3004.toCharArray(i41, 16);client.publish("IRH04/D3004", i41);
  d3006.toCharArray(i42, 16);client.publish("IRH04/D3006", i42);
  d3008.toCharArray(i43, 16);client.publish("IRH04/D3008", i43);
  d3020.toCharArray(i44, 16);client.publish("IRH04/D3020", i44);
  d3022.toCharArray(i45, 16);client.publish("IRH04/D3022", i45);
  d3024.toCharArray(i46, 16);client.publish("IRH04/D3024", i46);
  d3026.toCharArray(i47, 16);client.publish("IRH04/D3026", i47);
  d3028.toCharArray(i48, 16);client.publish("IRH04/D3028", i48);
  d3012.toCharArray(i49, 16);client.publish("IRH04/D3012", i49);
  d3032.toCharArray(i50, 16);client.publish("IRH04/D3032", i50);
  rssi.toCharArray(i_rssi, 16);client.publish("IRH04/rssi", i_rssi);
  
  Serial.println("\n---------------finish loop------------------\n\n");
  delay(5000);
}

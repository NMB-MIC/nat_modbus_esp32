#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <PubSubClient.h>
#include <ModbusMaster.h>

ModbusMaster node;

#define led_connection 41
#define led_run 42


const char* ssid = "DX_Project";
const char* password = "natmms22";
//const char* ssid = "TP-Link_EF46";
//const char* password = "98148813";
const char* mqtt_server = "192.168.1.2";

IPAddress local_IP(192, 168, 1, 201); // Static IP address192.168.100.164
IPAddress gateway(192, 168, 1, 1);    // Gateway IP address
IPAddress subnet(255, 255, 255, 0);     // subnet

char Machine_no[] = "GSSM01";

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

String D14001,
D14002,
D14003,
D14004,
D14005,
D14006,
D14007,
D14008,
D14009,
D14010,
D14011,
D14012,
D14013,
D14014,
D14015,
D14016,
D14017,
D14018,
D14019,
D14020,
D14021,
D14022,
D14023,
D14024,
D14025,
D14026,
D14027,
D14028,
D14029,
D14030,
D14031,
D14032,
D14033,
D14034,
D14035,
D14036,
D14037,
D14038,
D936,
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
  
node.readHoldingRegisters(0, 1);   Serial.print("(GREASE) CYCLE TIME : ");  Serial.println(node.getResponseBuffer(0));D14001= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(1, 1);   Serial.print("(GREASE) DAILY OK : ");  Serial.println(node.getResponseBuffer(0));D14002= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(2, 1);   Serial.print("(GREASE) DAILY NG A RING : ");  Serial.println(node.getResponseBuffer(0));D14003= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(3, 1);   Serial.print("(GREASE) DAILY NG B RING : ");  Serial.println(node.getResponseBuffer(0));D14004= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(4, 1);   Serial.print("(GREASE) DAILY TOTAL : ");  Serial.println(node.getResponseBuffer(0));D14005= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(5, 1);   Serial.print("(GREASE) DAILY YIELD : ");  Serial.println(node.getResponseBuffer(0));D14006= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(6, 1);   Serial.print("(GREASE) SHIFY OK : ");  Serial.println(node.getResponseBuffer(0));D14007= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(7, 1);   Serial.print("(GREASE) SHIFT NG A RING : ");  Serial.println(node.getResponseBuffer(0));D14008= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(8, 1);   Serial.print("(GREASE) SHIFT NG B RING : ");  Serial.println(node.getResponseBuffer(0));D14009= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(9, 1);   Serial.print("(GREASE) SHIFT TOTAL : ");  Serial.println(node.getResponseBuffer(0));D14010= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(10, 1);   Serial.print("(GREASE) SHIFT YIELD : ");  Serial.println(node.getResponseBuffer(0));D14011= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(11, 1);   Serial.print("(SHIELD&SNAP) CYCLE TIME : ");  Serial.println(node.getResponseBuffer(0));D14012= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(12, 1);   Serial.print("(SHIELD&SNAP) DAILY OK : ");  Serial.println(node.getResponseBuffer(0));D14013= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(13, 1);   Serial.print("(SHIELD&SNAP) DAILY NG A RING : ");  Serial.println(node.getResponseBuffer(0));D14014= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(14, 1);   Serial.print("(SHIELD&SNAP) DAILY NG B RING : ");  Serial.println(node.getResponseBuffer(0));D14015= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(15, 1);   Serial.print("(SHIELD&SNAP) DAILY TOTAL : ");  Serial.println(node.getResponseBuffer(0));D14016= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(16, 1);   Serial.print("(SHIELD&SNAP) DAILY YIELD : ");  Serial.println(node.getResponseBuffer(0));D14017= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(17, 1);   Serial.print("(SHIELD&SNAP) SHIFT OK  : ");  Serial.println(node.getResponseBuffer(0));D14018= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(18, 1);   Serial.print("(SHIELD&SNAP) SHIFT NG A RING : ");  Serial.println(node.getResponseBuffer(0));D14019= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(19, 1);   Serial.print("(SHIELD&SNAP) SHIFT NG B RING : ");  Serial.println(node.getResponseBuffer(0));D14020= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(20, 1);   Serial.print("(SHIELD&SNAP) SHIFT TOTAL  : ");  Serial.println(node.getResponseBuffer(0));D14021= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(21, 1);   Serial.print("(SHIELD&SNAP) SHIFT YIELD : ");  Serial.println(node.getResponseBuffer(0));D14022= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(22, 1);   Serial.print("A RING SHIELD HI NG : ");  Serial.println(node.getResponseBuffer(0));D14023= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(23, 1);   Serial.print("A RING SHIELD LO NG : ");  Serial.println(node.getResponseBuffer(0));D14024= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(24, 1);   Serial.print("A RING SHIELD NG : ");  Serial.println(node.getResponseBuffer(0));D14025= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(25, 1);   Serial.print("A RING SNAP NG : ");  Serial.println(node.getResponseBuffer(0));D14026= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(26, 1);   Serial.print("B RING SHIELD HI NG : ");  Serial.println(node.getResponseBuffer(0));D14027= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(27, 1);   Serial.print("B RING SHIELD LO NG : ");  Serial.println(node.getResponseBuffer(0));D14028= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(28, 1);   Serial.print("B RING SHIELD NG : ");  Serial.println(node.getResponseBuffer(0));D14029= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(29, 1);   Serial.print("B RING SNAP NG : ");  Serial.println(node.getResponseBuffer(0));D14030= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(30, 1);   Serial.print("UTL : ");  Serial.println(node.getResponseBuffer(0));D936= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(31, 1);   Serial.print("SHIELD1 USE COUNT : ");  Serial.println(node.getResponseBuffer(0));D14031= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(32, 1);   Serial.print("SHIELD2 USE COUNT : ");  Serial.println(node.getResponseBuffer(0));D14032= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(33, 1);   Serial.print("SNAP1 USE COUNT : ");  Serial.println(node.getResponseBuffer(0));D14033= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(34, 1);   Serial.print("SNAP2 USE COUNT : ");  Serial.println(node.getResponseBuffer(0));D14034= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(35, 1);   Serial.print("SHIELD1 LOSS : ");  Serial.println(node.getResponseBuffer(0));D14035= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(36, 1);   Serial.print("SHIELD2 LOSS : ");  Serial.println(node.getResponseBuffer(0));D14036= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(37, 1);   Serial.print("SNAP1 LOSS : ");  Serial.println(node.getResponseBuffer(0));D14037= node.getResponseBuffer(0);  node.clearResponseBuffer();
node.readHoldingRegisters(38, 1);   Serial.print("SNAP2 LOSS : ");  Serial.println(node.getResponseBuffer(0));D14038= node.getResponseBuffer(0);  node.clearResponseBuffer();


  
digitalWrite(led_run, HIGH);  
  
D14001.toCharArray(i0,16);client.publish("GSSM01/D14001",i0);
D14002.toCharArray(i1,16);client.publish("GSSM01/D14002",i1);
D14003.toCharArray(i2,16);client.publish("GSSM01/D14003",i2);
D14004.toCharArray(i3,16);client.publish("GSSM01/D14004",i3);
D14005.toCharArray(i4,16);client.publish("GSSM01/D14005",i4);
D14006.toCharArray(i5,16);client.publish("GSSM01/D14006",i5);
D14007.toCharArray(i6,16);client.publish("GSSM01/D14007",i6);
D14008.toCharArray(i7,16);client.publish("GSSM01/D14008",i7);
D14009.toCharArray(i8,16);client.publish("GSSM01/D14009",i8);
D14010.toCharArray(i9,16);client.publish("GSSM01/D14010",i9);
D14011.toCharArray(i10,16);client.publish("GSSM01/D14011",i10);
D14012.toCharArray(i11,16);client.publish("GSSM01/D14012",i11);
D14013.toCharArray(i12,16);client.publish("GSSM01/D14013",i12);
D14014.toCharArray(i13,16);client.publish("GSSM01/D14014",i13);
D14015.toCharArray(i14,16);client.publish("GSSM01/D14015",i14);
D14016.toCharArray(i15,16);client.publish("GSSM01/D14016",i15);
D14017.toCharArray(i16,16);client.publish("GSSM01/D14017",i16);
D14018.toCharArray(i17,16);client.publish("GSSM01/D14018",i17);
D14019.toCharArray(i18,16);client.publish("GSSM01/D14019",i18);
D14020.toCharArray(i19,16);client.publish("GSSM01/D14020",i19);
D14021.toCharArray(i20,16);client.publish("GSSM01/D14021",i20);
D14022.toCharArray(i21,16);client.publish("GSSM01/D14022",i21);
D14023.toCharArray(i22,16);client.publish("GSSM01/D14023",i22);
D14024.toCharArray(i23,16);client.publish("GSSM01/D14024",i23);
D14025.toCharArray(i24,16);client.publish("GSSM01/D14025",i24);
D14026.toCharArray(i25,16);client.publish("GSSM01/D14026",i25);
D14027.toCharArray(i26,16);client.publish("GSSM01/D14027",i26);
D14028.toCharArray(i27,16);client.publish("GSSM01/D14028",i27);
D14029.toCharArray(i28,16);client.publish("GSSM01/D14029",i28);
D14030.toCharArray(i29,16);client.publish("GSSM01/D14030",i29);
D936.toCharArray(i30,16);client.publish("GSSM01/D936",i30);
D14031.toCharArray(i31,16);client.publish("GSSM01/D14031",i31);
D14032.toCharArray(i32,16);client.publish("GSSM01/D14032",i32);
D14033.toCharArray(i33,16);client.publish("GSSM01/D14033",i33);
D14034.toCharArray(i34,16);client.publish("GSSM01/D14034",i34);
D14035.toCharArray(i35,16);client.publish("GSSM01/D14035",i35);
D14036.toCharArray(i36,16);client.publish("GSSM01/D14036",i36);
D14037.toCharArray(i37,16);client.publish("GSSM01/D14037",i37);
D14038.toCharArray(i38,16);client.publish("GSSM01/D14038",i38);
rssi.toCharArray(i_rssi,16);client.publish("GSSM01/rssi",i_rssi);

  Serial.println("\n---------------finish loop------------------\n\n");
  delay(5000);
}

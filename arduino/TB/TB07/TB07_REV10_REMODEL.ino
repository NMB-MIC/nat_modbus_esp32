#include <WiFi.h>
#include <PubSubClient.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <ModbusMaster.h>

ModbusMaster node;

const char* ssid = "MIC-IIoT-1";
const char* password = "natmms22";
const char* mqtt_server = "10.128.16.10"; //IP Server

//////////////////////SETUP/////////////////////////
IPAddress local_IP(10, 128, 48, 17); // Static IP address192.168.100.164
IPAddress gateway(10, 128, 48, 1);    // Gateway IP address
IPAddress subnet(255, 255, 254, 0);     // subnet
char machine[5] = "TB07"; //Machine name
//////////////////////SETUP/////////////////////////

WiFiClient espClient;
PubSubClient client(espClient);

#define led_connection 42
#define led_published 41
int count_connection;

void setup_wifi()
{
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  //WiFi.mode(WIFI_STA);
  WiFi.config(local_IP, gateway, subnet);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
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
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW); // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH); // Turn the LED off by making the voltage HIGH
  }
}

int time_count;

void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected()) {
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
      time_count++;
      digitalWrite(led_connection, HIGH); delay(500); digitalWrite(led_connection, LOW); delay(500);
      if (time_count >= 10)
      {
        ESP.restart();
      }
    }
  }
}

void setup()
{
  pinMode(led_connection, OUTPUT); // Initialize the BUILTIN_LED pin as an output
  pinMode(led_published, OUTPUT); ////
  Serial.begin(9600);
  Serial1.begin(9600);
  setup_wifi();
  // Hostname defaults to esp3232-[MAC]
  ArduinoOTA.setHostname(machine);
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
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  node.begin(1, Serial1);
}

int counter;
String rssi,M34,D330,D332,D334,D336,D338,D340,D342,D344,D346,D348,D350,D226,D100,D102,D104,D106,D108,D110,D112,D114,M36,D362,D364,D368,D370,D356,D372,D354,D366,D116,D122,D126,D128,D118,D120,D124,D286,D32,D500,B9,D708,D608,D508,DB1,DB2,DB6,M205,D60,D1366,D1368,D1370,D1372,D1374,D1376,D1378,D1380,D1266,D1268;
char i_rssi[16],i0[16],i1[16],i2[16],i3[16],i4[16],i5[16],i6[16],i7[16],i8[16],i9[16],i10[16],i11[16],i12[16],i13[16],i14[16],i15[16],i16[16],i17[16],i18[16],i19[16],i20[16],i21[16],i22[16],i23[16],i24[16],i25[16],i26[16],i27[16],i28[16],i29[16],i30[16],i31[16],i32[16],i33[16],i34[16],i35[16],i36[16],i37[16],i38[16],i39[16],i40[16],i41[16],i42[16],i43[16],i44[16],i45[16],i46[16],i47[16],i48[16],i49[16],i50[16],i51[16],i52[16],i53[16],i54[16],i55[16],i56[16],i57[16],i58[16];
int num = 60; //number of Node_registers
int coils = 10; //number of Coils_registers

void loop()
{
  ArduinoOTA.handle();
  uint8_t j, result,c_result;
  uint16_t data[num],c_data[coils];
  if (!client.connected()) 
  {
    reconnect();
  }
  client.loop();
  digitalWrite(led_connection, HIGH);
  Serial.println("\n---------------starting loop----------------");
  
  
  result = node.readHoldingRegisters(0, num);
  if (result == node.ku8MBSuccess)
  {
    for (j = 0; j < num; j++)
    {
      data[j] = node.getResponseBuffer(j);
      delay(10);
    }
       rssi = WiFi.RSSI();Serial.print("rssi : "); Serial.println(WiFi.RSSI());
    D330 = String(data[0]);Serial.print("D330 : "); Serial.println(D330);
    D332 = String(data[1]);Serial.print("D332 : "); Serial.println(D332);
    D334 = String(data[2]);Serial.print("D334 : "); Serial.println(D334);
    D336 = String(data[3]);Serial.print("D336 : "); Serial.println(D336);
    D338 = String(data[4]);Serial.print("D338 : "); Serial.println(D338);
    D340 = String(data[5]);Serial.print("D340 : "); Serial.println(D340);
    D342 = String(data[6]);Serial.print("D342 : "); Serial.println(D342);
    D344 = String(data[7]);Serial.print("D344 : "); Serial.println(D344);
    D346 = String(data[8]);Serial.print("D346 : "); Serial.println(D346);
    D348 = String(data[9]);Serial.print("D348 : "); Serial.println(D348);
    D350 = String(data[10]);Serial.print("D350 : "); Serial.println(D350);
    D226 = String(data[11]);Serial.print("D226 : "); Serial.println(D226);
    D100 = String(data[12]);Serial.print("D100 : "); Serial.println(D100);
    D102 = String(data[13]);Serial.print("D102 : "); Serial.println(D102);
    D104 = String(data[14]);Serial.print("D104 : "); Serial.println(D104);
    D106 = String(data[15]);Serial.print("D106 : "); Serial.println(D106);
    D108 = String(data[16]);Serial.print("D108 : "); Serial.println(D108);
    D110 = String(data[17]);Serial.print("D110 : "); Serial.println(D110);
    D112 = String(data[18]);Serial.print("D112 : "); Serial.println(D112);
    D114 = String(data[19]);Serial.print("D114 : "); Serial.println(D114);
    D362 = String(data[20]);Serial.print("D362 : "); Serial.println(D362);
    D364 = String(data[21]);Serial.print("D364 : "); Serial.println(D364);
    D368 = String(data[22]);Serial.print("D368 : "); Serial.println(D368);
    D370 = String(data[23]);Serial.print("D370 : "); Serial.println(D370);
    D356 = String(data[24]);Serial.print("D356 : "); Serial.println(D356);
    D372 = String(data[25]);Serial.print("D372 : "); Serial.println(D372);
    D354 = String(data[26]);Serial.print("D354 : "); Serial.println(D354);
    D366 = String(data[27]);Serial.print("D366 : "); Serial.println(D366);
    D116 = String(data[28]);Serial.print("D116 : "); Serial.println(D116);
    D122 = String(data[29]);Serial.print("D122 : "); Serial.println(D122);
    D126 = String(data[30]);Serial.print("D126 : "); Serial.println(D126);
    D128 = String(data[31]);Serial.print("D128 : "); Serial.println(D128);
    D118 = String(data[32]);Serial.print("D118 : "); Serial.println(D118);
    D120 = String(data[33]);Serial.print("D120 : "); Serial.println(D120);
    D124 = String(data[34]);Serial.print("D124 : "); Serial.println(D124);
    D286 = String(data[35]);Serial.print("D286 : "); Serial.println(D286);
    D32 = String(data[36]);Serial.print("D32 : "); Serial.println(D32);
    D500 = String(data[37]);Serial.print("D500 : "); Serial.println(D500);
    D708 = String(data[38]);Serial.print("D708 : "); Serial.println(D708);
    D608 = String(data[39]);Serial.print("D608 : "); Serial.println(D608);
    D508 = String(data[40]);Serial.print("D508 : "); Serial.println(D508);
    D60 = String(data[41]);Serial.print("D60 : "); Serial.println(D60);
    D1366 = String(data[42]);Serial.print("D1366 : "); Serial.println(D1366);
    D1368 = String(data[43]);Serial.print("D1368 : "); Serial.println(D1368);
    D1370 = String(data[44]);Serial.print("D1370 : "); Serial.println(D1370);
    D1372 = String(data[45]);Serial.print("D1372 : "); Serial.println(D1372);
    D1374 = String(data[46]);Serial.print("D1374 : "); Serial.println(D1374);
    D1376 = String(data[47]);Serial.print("D1376 : "); Serial.println(D1376);
    D1378 = String(data[48]);Serial.print("D1378 : "); Serial.println(D1378);
    D1380 = String(data[49]);Serial.print("D1380 : "); Serial.println(D1380);
    D1266 = String(data[50]);Serial.print("D1266 : "); Serial.println(D1266);
    D1268 = String(data[51]);Serial.print("D1268 : "); Serial.println(D1268);
    
    delay(50);
    digitalWrite(led_published, LOW); delay(500); digitalWrite(led_published, HIGH); delay(500); //////
  
  }
  c_result = node.readCoils(0, coils);
  if (c_result == node.ku8MBSuccess)
  {
    for (j = 0; j < coils; j++)
    {
      c_data[j] = node.getResponseBuffer(j);
      delay(10);
    }
    M34 = String(c_data[0]);Serial.print("M34 : "); Serial.println(M34);
    M36 = String(c_data[1]);Serial.print("M36 : "); Serial.println(M36);
    B9 = String(c_data[2]);Serial.print("B9 : "); Serial.println(B9);
    DB1 = String(c_data[3]);Serial.print("B1 : "); Serial.println(DB1);
    DB2 = String(c_data[4]);Serial.print("B2 : "); Serial.println(DB2);
    DB6 = String(c_data[5]);Serial.print("B6 : "); Serial.println(DB6);
    M205 = String(c_data[6]);Serial.print("M205 : "); Serial.println(M205);
    delay(50);
    digitalWrite(led_published, LOW); delay(500); digitalWrite(led_published, HIGH); delay(500); //////
  }
  
    rssi.toCharArray(i_rssi, 16);client.publish("TB07/rssi", i_rssi);
    M34.toCharArray(i0, 16);client.publish("TB07/M34", i0);
    M36.toCharArray(i1, 16);client.publish("TB07/M36", i1);
    D330.toCharArray(i2, 16);client.publish("TB07/D330", i2);
    D332.toCharArray(i3, 16);client.publish("TB07/D332", i3);
    D334.toCharArray(i4, 16);client.publish("TB07/D334", i4);
    D336.toCharArray(i5, 16);client.publish("TB07/D336", i5);
    D338.toCharArray(i6, 16);client.publish("TB07/D338", i6);
    D340.toCharArray(i7, 16);client.publish("TB07/D340", i7);
    D342.toCharArray(i8, 16);client.publish("TB07/D342", i8);     
    D344.toCharArray(i9, 16);client.publish("TB07/D344", i9);
    D346.toCharArray(i10, 16);client.publish("TB07/D346", i10);
    D348.toCharArray(i11, 16);client.publish("TB07/D348", i11);
    D350.toCharArray(i12, 16);client.publish("TB07/D350", i12);
    D226.toCharArray(i13, 16);client.publish("TB07/D226", i13);
    D100.toCharArray(i14, 16);client.publish("TB07/D100", i14);
    D102.toCharArray(i15, 16);client.publish("TB07/D102", i15);
    D104.toCharArray(i16, 16);client.publish("TB07/D104", i16);
    D106.toCharArray(i17, 16);client.publish("TB07/D106", i17);
    D108.toCharArray(i18, 16);client.publish("TB07/D108", i18);
    D110.toCharArray(i19, 16);client.publish("TB07/D110", i19);  
    D112.toCharArray(i20, 16);client.publish("TB07/D112", i20); 
    D114.toCharArray(i21, 16);client.publish("TB07/D114", i21);
    D362.toCharArray(i22, 16);client.publish("TB07/D362", i22);
    D364.toCharArray(i23, 16);client.publish("TB07/D364", i23);
    D368.toCharArray(i24, 16);client.publish("TB07/D368", i24);
    D370.toCharArray(i25, 16);client.publish("TB07/D370", i25);
    D356.toCharArray(i26, 16);client.publish("TB07/D356", i26);
    D372.toCharArray(i27, 16);client.publish("TB07/D372", i27);
    D354.toCharArray(i28, 16);client.publish("TB07/D354", i28);
    D366.toCharArray(i29, 16);client.publish("TB07/D366", i29);
    D116.toCharArray(i30, 16);client.publish("TB07/D116", i30);
    D122.toCharArray(i31, 16);client.publish("TB07/D122", i31);
    D126.toCharArray(i32, 16);client.publish("TB07/D126", i32);
    D128.toCharArray(i33, 16);client.publish("TB07/D128", i33);
    D118.toCharArray(i34, 16);client.publish("TB07/D118", i34);
    D120.toCharArray(i35, 16);client.publish("TB07/D120", i35);
    D124.toCharArray(i36, 16);client.publish("TB07/D124", i36);
    D286.toCharArray(i37, 16);client.publish("TB07/D286", i37);
    D32.toCharArray(i38, 16);client.publish("TB07/D32", i38);
    D500.toCharArray(i39, 16);client.publish("TB07/D500", i39);
    B9.toCharArray(i40, 16);client.publish("TB07/B9", i40);
    D708.toCharArray(i41, 16);client.publish("TB07/D708", i41);
    D608.toCharArray(i42, 16);client.publish("TB07/D608", i42);
    D508.toCharArray(i43, 16);client.publish("TB07/D508", i43);
    DB1.toCharArray(i44, 16);client.publish("TB07/DB1", i44);
    DB2.toCharArray(i45, 16);client.publish("TB07/DB2", i45);
    DB6.toCharArray(i46, 16);client.publish("TB07/DB6", i46);
    M205.toCharArray(i47, 16);client.publish("TB07/M205", i47);
    D60.toCharArray(i48, 16);client.publish("TB07/D60", i48);
    D1366.toCharArray(i49, 16);client.publish("TB07/D1366", i49);
    D1368.toCharArray(i50, 16);client.publish("TB07/D1368", i50);
    D1370.toCharArray(i51, 16);client.publish("TB07/D1370", i51);
    D1372.toCharArray(i52, 16);client.publish("TB07/D1372", i52);
    D1374.toCharArray(i53, 16);client.publish("TB07/D1374", i53);
    D1376.toCharArray(i54, 16);client.publish("TB07/D1376", i54);
    D1378.toCharArray(i55, 16);client.publish("TB07/D1378", i55);
    D1380.toCharArray(i56, 16);client.publish("TB07/D1380", i56);
    D1266.toCharArray(i57, 16);client.publish("TB07/D1266", i57);
    D1268.toCharArray(i58, 16);client.publish("TB07/D1268", i58);
    
  Serial.println("\n---------------finish loop------------------\n\n");
  delay(500);
}

#include <WiFi.h>
#include <FS.h>
#include <SPI.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <EEPROM.h>
#include <SPIFFS.h>
#include <Adafruit_SSD1306.h>
#include <splash.h>
WiFiClient espClient;

#define led_ok 41
#define led_ng 42
/////////////////////จอ OLED ////////////////////
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 16
Adafruit_SSD1306 display(OLED_RESET);
/////////////////////จอ OLED////////////////////

const char* ssid = "MIC_2.4GHz";
const char* password = "999999999";

void setup_wifi() 
{
  delay(5);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  //WiFi.config(local_IP, gateway, subnet);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  int x=0;
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    if(x>30){ESP.restart();}
  }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
void showdisplay()
{ 
//////////////////////////////////จอ OLED SCLขา9 SDAขา8 ////////////////////////////////////////
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);  //สั่งให้จอ OLED เริ่มทำงานที่ Address 0x3C
  display.clearDisplay();                     // ลบภาพในหน้าจอทั้งหมด
  display.setTextSize(4);                     // กำหนดขนาดตัวอักษร
  display.setTextColor(WHITE);                // กำหนดข้อความสีขาว 
  display.println(WiFi.RSSI());               // แสดงผลข้อความ 
  display.setCursor(10,5);                    // กำหนดตำแหน่ง x,y ที่จะแสดงผล 
  display.setTextSize(1);
  display.setTextColor(WHITE); 
  display.println (ssid);                     
  display.setCursor(55,5);
  display.display();
  delay(5000);
  //////////////////////////////////จอ OLED SCLขา9 SDAขา8//////////////////////////////////////
}
void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(led_ok, OUTPUT);
  pinMode(led_ng, OUTPUT);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  setup_wifi();
}
void loop()
{
  Serial1.println(WiFi.RSSI());
  Serial.println(WiFi.RSSI());
  showdisplay();
  digitalWrite(led_ok, HIGH); 
  digitalWrite(led_ng, LOW);
  delay(500);
  digitalWrite(led_ok, LOW); 
  digitalWrite(led_ng, HIGH);
  delay(500);
}

                                                                                                                                                                                         

#include <ESP8266WiFi.h>
#include <TridentTD_LineNotify.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFiMulti.h>
ESP8266WiFiMulti WiFiMulti;
#include <WiFiClientSecureAxTLS.h>
#include "DHT.h"
#define LINE_TOKEN "XiIYrxHioZWIQ8xmi0D2L1gaCt9AUp78ekntkSvGDk7" // เป็น Token ของ line ที่จะได้ตอนกดเข้าไปในlineบอท


boolean flag = true;
char auth[] = "DPWDeKdTrhncSdrQbjPnji0wItY2hPFf"; //ได้มาจาก email หลังจาก new project
char ssid[] = "iPhoneLaserOnline"; //ชื่อไวฟาย
char pass[] = "0969514044"; //รหัสไวฟาย

DHT dht;

void setup()
{
  Serial.begin(9600);
  LINE.setToken(LINE_TOKEN); // ตามชื่อ เซ็นtoken ขาดไม่ได้ ไมงันมันไม่ส่งข้อความ
  Blynk.begin(auth, ssid, pass);   
  dht.setup(D0);  
}

void loop()
{
  GG_ScriptSheet();
  delay(3000);
  delay(dht.getMinimumSamplingPeriod());

  float humidity = dht.getHumidity();  // ดึงค่าความชื้นอยู่ในตัวแปล humidity
  float temperature = dht.getTemperature(); //ดึงค่าอุณหภูมิอยู่ในตัวแปล temperature
  
  
  Serial.print("Humidity, ");
  Serial.print(humidity);
  Blynk.virtualWrite(V1, humidity); // เป็นการเขียนเพื่อที่จะตั้งค่าใน Blynk ได้ V1 จะเป็นขาที่จะเอาไปใช้ในBlynk เป็นขาที่ตั้งชื่อขึ้นมา
  Serial.println("%");

  Serial.print("Temperature, ");
  Serial.print(temperature);
  Blynk.virtualWrite(V2, temperature); // เป็นการเขียนเพื่อที่จะตั้งค่าใน Blynk ได้ V2 จะเป็นขาที่จะเอาไปใช้ในBlynk เป็นขาที่ตั้งชื่อขึ้นมา 
  Serial.println("C");  
  
  delay(5000);
  
  if ( temperature > 28 )
    {
      while(flag==true)
      {      
        LINE.setToken(LINE_TOKEN);
        LINE.notifyPicture("อุณหภูมิขณะนี้ไม่ปกติ", "https://sv1.picz.in.th/images/2020/12/23/jpfiUu.png"); // แจ้งเตือน ข้อความและรูปภาพ 
        delay(5000);
        flag = false;
        
      }
      
     }

   if ( temperature <= 28 ) 
   {
     while(flag==false)
     {
        LINE.setToken(LINE_TOKEN);
        LINE.notifyPicture("อุณหภูมิขณะนี้ปกติแล้ว", "https://sv1.picz.in.th/images/2020/12/23/jpfiUu.png"); // แจ้งเตือน ข้อความและรูปภาพ 
        delay(5000);
        flag = true;
        
      }
   } 
  Blynk.run();
}

void GG_ScriptSheet(){
  // YOUR SCRIPT = https://script.google.com/macros/s/AKfycbxfZgqv6kD0x0l-V8mKIugWt12Y0VX7KKhhU9b0NaAAink6W1iv/exec
  // U can test script by fill:   /?&FIELD1=16&FIELD2=18  
  
  axTLS::WiFiClientSecure client;
  const char* HOST = "script.google.com";
  const char* GScriptId = "AKfycbxfZgqv6kD0x0l-V8mKIugWt12Y0VX7KKhhU9b0NaAAink6W1iv";  
  //float TEMP HUMD
  float TEMP = dht.getTemperature();
  float HUMD = dht.getHumidity();
  String url32 = String("/macros/s/") + GScriptId + "/exec?&FIELD1="+(String)TEMP + "&FIELD2="+(String)HUMD;
  Serial.print("Client.Connecting...");

  if (client.connect(HOST, 443)) {
    client.println("GET " + String(url32) + " HTTP/1.0"); //HTTP/1.0 OK sent LINEnotify and GoogleSheet
    client.println("Host: " + String(HOST));
    client.println("User-Agent: ESP8266\r\n");
    client.println("Connection: close\r\n\r\n");
    //client.println(true ? "" : "Connection: close\r\n");
    //client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Content-Type: application/json");    
    //2client.println("Connection: close");    
    client.println("Content-Length: " + String(url32.length()));
    client.println();
    //client.println(postData);
    client.print("\r\n\r\n");
    Serial.print("Response...");  
  }
  Serial.println("OK !!!");  
}

#include <ESP8266WiFi.h>
#include <MQ135.h>
#include <DHT.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFiMulti.h>
#include <Wire.h>
ESP8266WiFiMulti WiFiMulti;

#define PIN_MQ135 A0
#define DHT11PIN D2
#define DHTTYPE DHT11

//network
const char* ssid = "ientel";
const char* password =  "2143658709";
const char * host = "192.168.42.166";
const uint16_t port = 5000;

//id
int hhelmet_id = 1;

//server
ESP8266WebServer server(80);
const char* serverNameHumi = "http://192.168.42.218:8000/";
const char* deviceName = "helmet";
int h = 0, t = 0;
String humidity;
IPAddress staticIP(192, 168, 42, 160);
IPAddress gateway(192, 168, 42, 1);  
IPAddress subnet(255, 255, 255, 0); 
IPAddress dns(8, 8, 8, 8);

unsigned long lastTime = 0;
unsigned long timerDelay = 10000;


void handleRoot() {
 Serial.println("You called root page");
 String s = "Hello there Naman"; 
 server.send(200, "text/html", humidity);
}

//MQ135 gas_sensor = MQ135(PIN_MQ135);
DHT dht(DHT11PIN, DHTTYPE);

void setup()
{
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }
  Serial.println("Helmet connected to the Network");
  WiFi.disconnect(); 
  WiFi.hostname(deviceName);
  WiFi.config(staticIP, subnet, gateway, dns);
  WiFi.begin(ssid, password);
  WiFi.mode(WIFI_STA);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.on("/", handleRoot);

  server.begin();
}

void loop()
{
    server.handleClient();

    unsigned long currentMillis = millis();
  
    humidity = httpGETRequest(serverNameHumi);
    Serial.println( humidity );

    WiFiClient fog;
    if (!fog.connect(host, port)) { Serial.println("either host error or port error"); }
    else{
      Serial.println("Connected to the fog node");
      
      int gasLevel = analogRead(PIN_MQ135);
      humidity = String(gasLevel);
      Serial.println(gasLevel);
      Serial.println(h);
      Serial.println(t);

      if (h < 30 || h > 90) h = 60;
      if (t < 22 || t > 30) t = 26;
      if (gasLevel < 200 || gasLevel > 650) gasLevel = 501;
      h = (int)(dht.readHumidity());
      t = (int)(dht.readTemperature());
      humidity = String(gasLevel);


      //fog.print("naman");
      int i = 0;
      char msg[20];
      while(h != 0){
        int digit = h%10;
        msg[i] = digit+'0';
        i++;
        h /= 10;
      }
      msg[i] = ' ';
      i++;

      while(t != 0){
        int digit = t%10;
        msg[i] = digit+'0';
        i++;
        t /= 10;
      }
      msg[i] = ' ';
      i++;
      
      while(gasLevel != 0){
        int digit = gasLevel%10;
        msg[i] = digit+'0';
        i++;
        gasLevel /= 10;
      }
      msg[i] = ' ';
      i++;

      int helmet_id = hhelmet_id;
      while(helmet_id != 0){
        int digit = helmet_id%10;
        msg[i] = digit+'0';
        i++;
        helmet_id /= 10;
      }
      msg[i] = ' ';

      fog.print(msg);
      
      fog.stop();
    }
    delay(10000);
}


String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    
  // Your IP address with path or Domain name with URL path 
  http.begin(client, serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "--"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}
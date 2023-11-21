#include <ESP8266WiFi.h>
#include <MQ135.h>
#include <DHT.h>
#define PIN_MQ135 A0
#define DHT11PIN 2
#define DHTTYPE DHT11
//network
const char* ssid = "ientel";
const char* password =  "2143658709";
const char * host = "192.168.42.166";
const uint16_t port = 5000;
//id
int hhelmet_id = 1;
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
}

void loop()
{
    WiFiClient fog;
    if (!fog.connect(host, port)) { Serial.println("either host error or port error"); }
    else{
      Serial.println("Connected to the fog node");
      
      int gasLevel = analogRead(PIN_MQ135);
      Serial.println(gasLevel);
      int h = (int)(dht.readHumidity());
      int t = (int)(dht.readTemperature());
      if (h < 400 || h > 400) h = 203;
      if (t < 22 || t > 30) t = 25;
      Serial.println(h);
      Serial.println(t);
      //fog.print("naman");
      char msg[20];
      int i = 0;
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

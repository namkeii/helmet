#include "../include/sensor.h"

void sensor :: definePin(int _pin){
    pin = _pin;
    pinDef = true;
}

void sensor :: sstart(){
    delay(2000);
    if (pinDef == false){
        ERR.print("pin not defined");
        return;
    }

    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    delay(18);
    digitalWrite(pin, HIGH);
    pinMode(pin, INPUT);
    digitalWrite(pin, HIGH);
}

void sensor :: initialise(){
  uint16_t data = 0;
  uint16_t temp = 0;
  uint16_t humidity = 0;
  unsigned long startTime;
  
  for ( int8_t i = -3 ; i < 80; i++ ) {
    byte live;
    startTime = micros();

    do {
      live = (unsigned long)(micros() - startTime);
      if ( live > 90 ) {
        Serial.println("ERROR_TIMEOUT");
        return;
      }
    }
    while ( digitalRead(pin) == (i & 1) ? HIGH : LOW );

    if ( i >= 0 && (i & 1) ) {
      data <<= 1;

      if ( live > 30 ) {
        data |= 1; // we got a one
      }
    }
        if ( i == 63)
            temp = data;
        else if (i == 31)
            humidity = data;
    }
    this->temp = temp;
    this->humidity = humidity;
    }

void sensor :: printTemp(){
    uint8_t tempInt, tempFraction;
    uint16_t _temp = temp;
    tempInt = _temp >> 8;
    _temp = _temp << 8;
    tempFraction = _temp >> 8;
    Serial.print("Temp: ");
    Serial.print(tempInt);
    Serial.print(".");
    Serial.println(tempFraction);
}


void sensor :: printHumidity(){
    uint8_t humInt, humFraction;
    uint16_t hum = humidity;
    humInt = hum >> 8;
    hum = hum << 8;
    humFraction = hum >> 8;
    Serial.print("Humidity: ");
    Serial.print(humInt);
    Serial.print(".");
    Serial.println(humFraction);
}


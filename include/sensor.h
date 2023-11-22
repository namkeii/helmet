#include "Arduino.h"
#include <iostream>
#define ERR Serial
#include <stdint.h>
class sensor
{
    private:
        uint16_t temp;
        uint16_t humidity;
        uint8_t pin;
        bool pinDef = false;
    public:
        void definePin(int);
        void sstart();
        void initialise();
        void printTemp();
        void printHumidity();
};

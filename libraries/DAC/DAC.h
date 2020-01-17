#ifndef DAC_DAC_H
#define DAC_DAC_H

#include <Arduino.h>
#include <SPI.h>

#define DAC_RESOLUTION 4096

typedef struct MCP4922 DAC;

struct MCP4922 {
    int _SDI, _SCK, _CS, _LDAC;
};

DAC* generateDAC(int _SDI, int _SCK, int _CS, int _LDAC);

void Set(DAC* dac, unsigned int A, unsigned int B);

#endif //DAC_DAC_H
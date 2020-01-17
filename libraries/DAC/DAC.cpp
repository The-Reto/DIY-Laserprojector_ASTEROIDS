#include "DAC.h"

void sendIntValueSPI(DAC* dac, unsigned int A, unsigned int B);

void sendIntValueSPI(DAC* dac, unsigned int A , unsigned int B) {
    unsigned int channelA = A | 0b0111000000000000u;
    unsigned int channelB = B | 0b1111000000000000u;

    digitalWrite(dac->_CS, LOW);
    SPI.transfer(highByte(channelA));
    SPI.transfer(lowByte(channelA));
    digitalWrite(dac->_CS, HIGH);

    digitalWrite(dac->_CS, LOW);
    SPI.transfer(highByte(channelB));
    SPI.transfer(lowByte(channelB));
    digitalWrite(dac->_CS, HIGH);
    digitalWrite(dac->_LDAC,LOW);

    digitalWrite(dac->_LDAC,HIGH);
}

DAC *generateDAC(int _SDI, int _SCK, int _CS, int _LDAC) {
    DAC* ret = (DAC*) malloc(sizeof(DAC));
    ret->_CS = _CS;
    ret->_SDI = _SDI;
    ret->_LDAC = _LDAC;
    ret->_SCK = _SCK;

    pinMode(_SDI,OUTPUT);
    pinMode(_SCK,OUTPUT);
    pinMode(_CS,OUTPUT);
    pinMode(_LDAC,OUTPUT);

    SPI.begin();
    return ret;
}

void Set(DAC *dac, unsigned int A, unsigned int B) {
    sendIntValueSPI(dac,A,B);
}
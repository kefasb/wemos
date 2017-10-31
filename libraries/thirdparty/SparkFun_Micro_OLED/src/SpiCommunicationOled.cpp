/*
 * SpiCommunicationOled.cpp
 *
 * Author: Piotr Borkowski
 */

#include <SPI.h>
#include "SparkFun_Micro_OLED/src/SpiCommunicationOled.h"

// Configure SPI settings - Max clk frequency for display is 10MHz
SPISettings oledSettings(10000000, MSBFIRST, SPI_MODE0);

SpiCommunicationOled::SpiCommunicationOled(uint8_t dcPin, uint8_t csPin) :
        dcPin(dcPin), csPin(csPin) {
}

SpiCommunicationOled::~SpiCommunicationOled() {
}

void SpiCommunicationOled::setup() const {
    pinMode(dcPin, OUTPUT);

    pinMode(MOSI, OUTPUT);  // MOSI is an OUTPUT
    pinMode(SCK, OUTPUT);   // SCK is an OUTPUT
    pinMode(csPin, OUTPUT); // CS is an OUTPUT
    digitalWrite(csPin, HIGH);  // Start CS High

#if defined(__AVR__)
    pinMode(10, OUTPUT); // Required for setting into Master mode
#endif
    SPI.begin();
}

void SpiCommunicationOled::writeData(uint8_t data) const {
    digitalWrite(dcPin, HIGH);

    SPI.beginTransaction(oledSettings);
    digitalWrite(csPin, LOW);
    SPI.transfer(data);
    digitalWrite(csPin, HIGH);
    SPI.endTransaction();
}

void SpiCommunicationOled::writeCommand(uint8_t data) const {
    digitalWrite(dcPin, LOW);

    SPI.beginTransaction(oledSettings);
    digitalWrite(csPin, LOW);
    SPI.transfer(data);
    digitalWrite(csPin, HIGH);
    SPI.endTransaction();
}

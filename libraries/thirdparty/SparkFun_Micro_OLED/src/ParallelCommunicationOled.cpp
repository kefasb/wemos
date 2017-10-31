/*
 * ParallelCommunicationOled.cpp
 *
 * Author: Piotr Borkowski
 */

#include "SparkFun_Micro_OLED/src/ParallelCommunicationOled.h"

ParallelCommunicationOled::ParallelCommunicationOled(uint8_t dcPin,
        uint8_t csPin, uint8_t wrPin, uint8_t rdPin, uint8_t d0Pin,
        uint8_t d1Pin, uint8_t d2Pin, uint8_t d3Pin, uint8_t d4Pin,
        uint8_t d5Pin, uint8_t d6Pin, uint8_t d7Pin) :
        dcPin(dcPin), csPin(csPin), wrPin(wrPin), rdPin(rdPin), dPins { d0Pin,
                d1Pin, d2Pin, d3Pin, d4Pin, d5Pin, d6Pin, d7Pin } {
}

ParallelCommunicationOled::~ParallelCommunicationOled() {
}

void ParallelCommunicationOled::setup() const {
    pinMode(dcPin, OUTPUT);

    pinMode(wrPin, OUTPUT);
    digitalWrite(wrPin, HIGH);
    pinMode(rdPin, OUTPUT);
    digitalWrite(rdPin, HIGH);
    pinMode(csPin, OUTPUT);
    digitalWrite(csPin, HIGH);
    for (int i = 0; i < 8; i++) {
        pinMode(dPins[i], OUTPUT);
    }
}

void ParallelCommunicationOled::writeData(uint8_t data) const {
    digitalWrite(csPin, LOW);
    digitalWrite(dcPin, HIGH);
    digitalWrite(wrPin, LOW);

    for (int i = 0; i < 8; i++) {
        if (data & (1 << i))
            digitalWrite(dPins[i], HIGH);
        else
            digitalWrite(dPins[i], LOW);
    }

    digitalWrite(wrPin, HIGH);
    digitalWrite(csPin, HIGH);
}

void ParallelCommunicationOled::writeCommand(uint8_t command) const {
    digitalWrite(csPin, LOW);
    digitalWrite(dcPin, LOW);
    digitalWrite(wrPin, LOW);

    for (int i = 0; i < 8; i++) {
        if (command & (1 << i))
            digitalWrite(dPins[i], HIGH);
        else
            digitalWrite(dPins[i], LOW);
    }

    digitalWrite(wrPin, HIGH);
    digitalWrite(csPin, HIGH);
}

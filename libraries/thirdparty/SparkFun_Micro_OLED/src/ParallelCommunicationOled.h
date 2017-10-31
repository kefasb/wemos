/*
 * ParallelCommunicationOled.h
 *
 * Author: Piotr Borkowski
 */

#ifndef PARALLELCOMMUNICATION_OLED_H_
#define PARALLELCOMMUNICATION_OLED_H_

#include <Arduino.h>
#include "SparkFun_Micro_OLED/src/ICommunicationOled.h"

class ParallelCommunicationOled: public ICommunicationOled {
public:
    ParallelCommunicationOled(uint8_t dcPin, uint8_t csPin, uint8_t wrPin,
            uint8_t rdPin, uint8_t d0Pin, uint8_t d1Pin, uint8_t d2Pin,
            uint8_t d3Pin, uint8_t d4Pin, uint8_t d5Pin, uint8_t d6Pin,
            uint8_t d7Pin);
    virtual ~ParallelCommunicationOled();

    void setup() const;
    void writeData(uint8_t data) const;
    void writeCommand(uint8_t command) const;

private:
    const uint8_t dcPin;
    const uint8_t csPin;
    const uint8_t wrPin;
    const uint8_t rdPin;
    const uint8_t dPins[8];
};

#endif /* PARALLELCOMMUNICATION_OLED_H_ */

/*
 * SpiCommunicationOled.h
 *
 * Author: Piotr Borkowski
 */

#ifndef SPICOMMUNICATION_OLED_H_
#define SPICOMMUNICATION_OLED_H_

#include <Arduino.h>
#include "SparkFun_Micro_OLED/src/ICommunicationOled.h"

class SpiCommunicationOled: public ICommunicationOled {
public:
    SpiCommunicationOled(uint8_t dcPin, uint8_t csPin);
    virtual ~SpiCommunicationOled();

    void setup() const override;
    void writeData(uint8_t data) const override;
    void writeCommand(uint8_t data) const override;

private:
    const uint8_t dcPin;
    const uint8_t csPin;

};

#endif /* SPICOMMUNICATION_OLED_H_ */

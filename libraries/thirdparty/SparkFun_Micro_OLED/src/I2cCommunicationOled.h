/*
 * I2cCommunicationOled.h
 *
 * Author: Piotr Borkowski
 */

#ifndef I2CCOMMUNICATION_OLED_H_
#define I2CCOMMUNICATION_OLED_H_

#include <Arduino.h>
#include <SparkFun_Micro_OLED/src/ICommunicationOled.h>

class I2cCommunicationOled: public ICommunicationOled {
public:
    static const uint8_t OLED_I2C_DEFAULT_ADDRESS = 0x3C;
    static const uint8_t OLED_ALTERNATIVE_ADDRESS = 0x3D;

    I2cCommunicationOled();
    I2cCommunicationOled(uint8_t i2cAddress);
    virtual ~I2cCommunicationOled();

    void setup() const override;
    void writeData(uint8_t data) const override;
    void writeCommand(uint8_t command) const override;

private:
    static const uint8_t OLED_I2C_COMMAND = 0x00;
    static const uint8_t OLED_I2C_DATA = 0x40;
    const uint8_t i2cAddress;

};

#endif /* I2CCOMMUNICATION_OLED_H_ */

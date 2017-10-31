/*
 * ICommunicationOled.h
 *
 * Author: Piotr Borkowski
 *
 */

#ifndef ICOMMUNICATION_OLED_H_
#define ICOMMUNICATION_OLED_H_

class ICommunicationOled {
public:
    virtual ~ICommunicationOled() {
    }

    virtual void setup() const = 0;
    virtual void writeData(uint8_t data) const = 0;
    virtual void writeCommand(uint8_t command) const = 0;
};

#endif /* ICOMMUNICATION_OLED_H_ */

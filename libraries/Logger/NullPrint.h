/*
 * NullPrint.h
 *
 * Author: Piotr Borkowski
 *
 * A Print variant that does not print anything.
 */

#ifndef LOGGER_NULLPRINT_H_
#define LOGGER_NULLPRINT_H_

#include "Print.h"

class NullPrint: public Print {
public:
    NullPrint();
    virtual ~NullPrint();

    virtual size_t write(uint8_t);
    virtual size_t write(const uint8_t *buffer, size_t size);
};

extern NullPrint DefaultNullPrint;

#endif /* LOGGER_NULLPRINT_H_ */

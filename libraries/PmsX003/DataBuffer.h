/*
 * DataBuffer.h
 *
 * Author: Piotr Borkowski
 */

#ifndef LIBRARIES_PMS3003_DATABUFFER_H_
#define LIBRARIES_PMS3003_DATABUFFER_H_

#include <stdint.h>
#include "PmsData.h"

class DataBuffer {
public:
    DataBuffer();
    virtual ~DataBuffer();

    bool add(PmsData data);

    PmsData getNext();

private:
    static const uint16_t BUFFER_SIZE = 300;
    PmsData buffer[BUFFER_SIZE];
    uint16_t addIndex;
    uint16_t getIndex;
};

#endif /* LIBRARIES_PMS3003_DATABUFFER_H_ */

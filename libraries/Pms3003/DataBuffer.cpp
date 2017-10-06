/*
 * DataBuffer.cpp
 *
 * Author: Piotr Borkowski
 */

#include <DataBuffer.h>

DataBuffer::DataBuffer() :
        addIndex(0), getIndex(0) {
}

DataBuffer::~DataBuffer() {
}

bool DataBuffer::add(PmsData data) {
    if (addIndex < BUFFER_SIZE) {
        buffer[addIndex++] = data;
        return true;
    } else {
        return false;
    }
}

PmsData DataBuffer::getNext() {
}

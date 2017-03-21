/*
 * NullPrint.cpp
 *
 * Author: Piotr Borkowski
 *
 */

#include "NullPrint.h"

NullPrint DefaultNullPrint;

NullPrint::NullPrint() {
}

NullPrint::~NullPrint() {
}

size_t NullPrint::write(uint8_t unsignedChar) {
    return 0;
}

size_t NullPrint::write(const uint8_t* buffer, size_t size) {
    return 0;
}

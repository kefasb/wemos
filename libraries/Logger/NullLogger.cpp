/*
 * NullLogger.cpp
 *
 * Author: Piotr Borkowski
 *
 */

#include "NullLogger.h"

NullLogger DefaultNullLogger;

NullLogger::NullLogger() :
        Logger(DefaultNullPrint) {
}

NullLogger::~NullLogger() {
}


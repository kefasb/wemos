/*
 * NullLogger.h
 *
 * Author: Piotr Borkowski
 *
 * NullLogger is to be used when logging is not needed but a Logger is expected.
 */

#ifndef LOGGER_NULLLOGGER_H_
#define LOGGER_NULLLOGGER_H_

#include "Logger.h"
#include "NullPrint.h"

class NullLogger: public Logger {
public:
    NullLogger();
    virtual ~NullLogger();
};

extern NullLogger DefaultNullLogger;

#endif /* LOGGER_NULLLOGGER_H_ */

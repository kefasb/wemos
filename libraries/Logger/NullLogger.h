/*
 * NullLogger.h
 *
 * Author: Piotr Borkowski
 *
 * NullLogger is to be used when logging is not needed but a Logger is expected.
 */

#ifndef LOGGER_NULLLOGGER_H_
#define LOGGER_NULLLOGGER_H_

#include "ILogger.h"

class NullLogger: public ILogger {
public:
    virtual ~NullLogger() {
    }

    void logDebug(const char* const , ...) const override final {
    }

    void logInfo(const char* const , ...) const override final {
    }

    void logError(const char* const , ...) const override final {
    }
};

extern NullLogger DefaultNullLogger;

#endif /* LOGGER_NULLLOGGER_H_ */

/*
 * ILogger.h
 *
 * Author: Piotr Borkowski
 *
 * Logging interface
 */

#ifndef LOGGER_ILOGGER_H_
#define LOGGER_ILOGGER_H_

class ILogger {
public:
    virtual ~ILogger() {
    }

    /**
     * Tries to log given text on DEBUG level. It checks if logging level allows it.
     * @param text Text to be logged, may be a format
     * @param args Additional arguments if text is a format
     */
    virtual void logDebug(const char* const text, ...) const=0;

    /**
     * Tries to log given text on INFO level. It checks if logging level allows it.
     * @param text Text to be logged, may be a format
     * @param args Additional arguments if text is a format
     */
    virtual void logInfo(const char* const text, ...) const=0;

    /**
     * Tries to log given text on ERROR level. It checks if logging level allows it.
     * @param text Text to be logged, may be a format
     * @param args Additional arguments if text is a format
     */
    virtual void logError(const char* const text, ...) const=0;
};

#endif /* LOGGER_ILOGGER_H_ */

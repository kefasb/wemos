/*
 * Logger.h
 *
 * Author: Piotr Borkowski
 *
 * Provides logging functionality.
 * Logs to provided Print interface. Has several logging levels that may be used
 * to better adjust printed information. LogLevel is used for that.
 * Smaller number means higher priority.
 * Logger created with a priority sends to output only logs with equal or higher priority.
 * E.g. logger created with priority INFO sends logs printed with logError and LogInfo.
 *
 */

#ifndef LOGGER_LOGGER_H_
#define LOGGER_LOGGER_H_

#include "Print.h"
#include "ILogger.h"

enum LogLevel {
    NONE = -1, ERROR = 5, INFO = 10, DEBUG = 15, ALL = 100
};

class Logger: public ILogger {
public:
    /**
     * Creates logger that will send logs to provided Print interface and will include
     * provided className in log.
     * @param out Print interface to be used to send logs to
     * @param className Class name to be used for logs
     * @param logLevel Logging level the logger will be created with
     */
    Logger(Print& out, const char* const className, LogLevel logLevel = INFO);

    /**
     * Creates logger that will send logs to provided Print interface.
     * @param out Print interface to be used to send logs to
     * @param logLevel Logging level the logger will be created with
     */
    Logger(Print& out, LogLevel logLevel = INFO);

    /**
     * destructor
     */
    virtual ~Logger();

    void logDebug(const char* const text, ...) const override;

    void logInfo(const char* const text, ...) const override;

    void logError(const char* const text, ...) const override;

private:
    static constexpr char DEBUG_TXT[] = "[DEBUG] ";
    static constexpr char INFO_TXT[] = "[INFO] ";
    static constexpr char ERROR_TXT[] = "[ERROR] ";
    static const uint8_t PREFIX_MAX_LENGTH = 22;
    static const uint8_t CLASS_NAME_MAX_LENGTH = 20;

    Print& out;
    const LogLevel logLevel;
    char prefix[PREFIX_MAX_LENGTH + 1];

    void logIt(const char* const severity, const char* const text, va_list args) const;

    bool isAllowedToLogOnLevel(LogLevel level) const;
};

#endif /* LOGGER_LOGGER_H_ */

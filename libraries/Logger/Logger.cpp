/*
 * Logger.cpp
 *
 * Author: Piotr Borkowski
 *
 */

#include "Logger.h"

constexpr char Logger::DEBUG_TXT[];
constexpr char Logger::INFO_TXT[];
constexpr char Logger::ERROR_TXT[];

Logger::Logger(Print& out, const char* const className, LogLevel logLevel) :
        out(out), logLevel(logLevel) {
    strncpy(prefix, className, CLASS_NAME_MAX_LENGTH);
    prefix[CLASS_NAME_MAX_LENGTH] = 0;
    strcat(prefix, ": ");
}

Logger::Logger(Print& out, LogLevel logLevel) :
        out(out), logLevel(logLevel) {
    strncpy(prefix, "", PREFIX_MAX_LENGTH + 1);
}

Logger::~Logger() {
}

void Logger::logIt(const char* const levelTxt, const char* const text, va_list args) const {
    out.print(levelTxt);
    out.print(prefix);
    char buf[256];
    vsnprintf(buf, 256, text, args);
    out.print(buf);
    out.println();
}

bool Logger::isAllowedToLogOnLevel(LogLevel level) const {
    return logLevel >= level;
}

void Logger::logDebug(const char* const text, ...) const {
    if (isAllowedToLogOnLevel(DEBUG)) {
        va_list args;
        va_start(args, text);
        logIt(DEBUG_TXT, text, args);
        va_end(args);
    }
}

void Logger::logInfo(const char* const text, ...) const {
    if (isAllowedToLogOnLevel(INFO)) {
        va_list args;
        va_start(args, text);
        logIt(INFO_TXT, text, args);
        va_end(args);
    }
}

void Logger::logError(const char* const text, ...) const {
    if (isAllowedToLogOnLevel(ERROR)) {
        va_list args;
        va_start(args, text);
        logIt(ERROR_TXT, text, args);
        va_end(args);
    }
}

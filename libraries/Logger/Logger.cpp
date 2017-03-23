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

    prefix = new char[strlen(className) + 3];
    strcpy(prefix, className);
    strcat(prefix, ": ");
}

Logger::Logger(Print& out, LogLevel logLevel) :
        out(out), logLevel(logLevel), prefix(NULL) {
}

Logger::~Logger() {
    if (NULL != prefix) {
        delete[] prefix;
    }
}

void Logger::logIt(const char* const levelTxt, const char* const text, ...) const {
    out.print(levelTxt);
    out.print(prefix);
    va_list args;
    va_start(args, text);
    out.printf(text, args);
    va_end(args);
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
        logIt(INFO_TXT, text);
        va_end(args);
    }
}

void Logger::logError(const char* const text, ...) const {
    if (isAllowedToLogOnLevel(ERROR)) {
        va_list args;
        va_start(args, text);
        logIt(ERROR_TXT, text);
        va_end(args);
    }
}

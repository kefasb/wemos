/*
 * Pms3003.cpp
 *
 * Author: Piotr Borkowski
 *
 */

#include "Pms3003.h"

constexpr uint8_t Pms3003::HEADER[];

void Pms3003::insertHeaderToBuf(uint8_t buf[]) const {
    for (uint8_t i = 0; i < HEADER_LEN; i++) {
        buf[i] = HEADER[i];
    }
}

Pms3003::Pms3003(Stream& pmsSerial, uint8_t setPin, const ILogger& logger) :
        serial(pmsSerial), setPin(setPin), logger(logger) {
}

Pms3003::~Pms3003() {
}

void Pms3003::printBufferContents(const uint8_t buf[]) const {
    char bufferStr[BUF_LEN * 3] = { 0 };
    uint16_t length = 0;
    for (uint8_t i = 0; i < BUF_LEN; i++) {
        length += sprintf(&bufferStr[length], "%d", buf[i]);
    }
    logger.logDebug(bufferStr);
}

PmsData Pms3003::readData() {
    uint8_t pms3003Buf[BUF_LEN];
    insertHeaderToBuf(pms3003Buf);

    PmsData data = EmptyData();
    if (serial.find(HEADER, HEADER_LEN)) {
        if (DATA_LEN == serial.readBytes(pms3003Buf + HEADER_LEN, DATA_LEN)) {
            printBufferContents(pms3003Buf);
            if (validateChecksum(pms3003Buf)) {
                data = PmsData(extractPm01(pms3003Buf), extractPm25(pms3003Buf),
                        extractPm10(pms3003Buf));
            }
        }
    }
    return data;
}

void Pms3003::clearData() {
    uint16_t clearingTimeout = millis() + 3000;
    while (serial.available() > 0 && (millis() < clearingTimeout)) {
        serial.read();
        delay(10);
    }
}

void Pms3003::printChecksums(const uint16_t sum, const uint16_t receivedSum) const {
    logger.logDebug("Checksum mismatch!");
    logger.logDebug("Calculated sum: %u", sum);
    logger.logDebug("Received sum: %u", receivedSum);
}

bool Pms3003::validateChecksum(const uint8_t buf[]) const {
    uint16_t sum = calculateChecksum(buf);
    uint16_t receivedSum = extractChecksum(buf);
    bool checksumMatch = sum == receivedSum;

    if (!checksumMatch) {
        printChecksums(sum, receivedSum);
    }
    return checksumMatch;
}

uint16_t Pms3003::extractChecksum(const uint8_t buf[]) const {
    return (buf[CHECKSUM_FIRST_POS] << 8) + buf[CHECKSUM_FIRST_POS + 1];
}

uint16_t Pms3003::calculateChecksum(const uint8_t buf[]) const {
    uint16_t sum = 0;
    for (uint8_t i = 0; i < CHECKSUM_FIRST_POS; i++) {
        sum += buf[i];
    }
    return sum;
}

uint16_t Pms3003::extractPm01(const uint8_t buf[]) const {
    return (buf[PM01_FIRST_POS] << 8) + buf[PM01_FIRST_POS + 1];
}

uint16_t Pms3003::extractPm25(const uint8_t buf[]) const {
    return (buf[PM25_FIRST_POS] << 8) + buf[PM25_FIRST_POS + 1];
}

uint16_t Pms3003::extractPm10(const uint8_t buf[]) const {
    return (buf[PM10_FIRST_POS] << 8) + buf[PM10_FIRST_POS + 1];
}

bool Pms3003::wakeup() {
    digitalWrite(setPin, WAKEUP_VALUE);
    int8_t checkCount = 3;
    do {
        delay(100);
    } while ((--checkCount >= 0) && (readData() == EmptyData()));

    bool successful = checkCount >= 0;
    if (!successful) {
        logger.logError("Wakeup unsuccessful!");
    }
    return successful;
}

bool Pms3003::sleep() {
    digitalWrite(setPin, SLEEP_VALUE);
    int8_t checkCount = 3;
    do {
        delay(100);
    } while ((--checkCount >= 0) && (readData() != EmptyData()));
    bool successful = checkCount >= 0;
    if (!successful) {
        logger.logError("Sleep unsuccessful!");
    }
    if (successful) {
        clearData();
    }
    return successful;
}

/*
 * PmsX003.cpp
 *
 * Author: Piotr Borkowski
 *
 */

#include <PmsX003.h>

constexpr uint8_t PmsX003::HEADER[];

void PmsX003::insertHeaderToBuf(uint8_t buf[]) const {
    for (uint8_t i = 0; i < HEADER_LEN; i++) {
        buf[i] = HEADER[i];
    }
}

PmsX003::PmsX003(Stream& pmsSerial, uint8_t setPin, const ILogger& logger) :
        serial(pmsSerial), setPin(setPin), logger(logger) {
}

PmsX003::~PmsX003() {
}

void PmsX003::printBufferContents(const uint8_t buf[]) const {
    char bufferStr[BUF_LEN * 3] = { 0 };
    uint16_t length = 0;
    for (uint8_t i = 0; i < BUF_LEN; i++) {
        length += sprintf(&bufferStr[length], "%d", buf[i]);
    }
    logger.logDebug(bufferStr);
}

PmsData PmsX003::readData() {
    uint8_t pmsBuf[BUF_LEN];
    insertHeaderToBuf(pmsBuf);

    PmsData data = EmptyData();
    if (serial.find(HEADER, HEADER_LEN)) {
        if (DATA_LENGTH_DEFINITION_LEN
                == serial.readBytes(pmsBuf + HEADER_LEN, DATA_LENGTH_DEFINITION_LEN)) {
            uint16_t dataLen = calculateDataLen(pmsBuf);
            logger.logDebug("Data len received: %u", dataLen);
            if (MAX_DATA_LEN_SUPPORTED < dataLen) {
                logger.logError("Received data format is not supported");
            } else if (dataLen == serial.readBytes(pmsBuf + DATA_START_POS, dataLen)) {
                printBufferContents(pmsBuf);
                if (validateChecksum(pmsBuf, DATA_START_POS + dataLen - CHECKSUM_LEN)) {
                    data = PmsData(extractPm01(pmsBuf), extractPm25(pmsBuf), extractPm10(pmsBuf));
                }
            }
        }
    }
    return data;
}

uint16_t PmsX003::calculateDataLen(const uint8_t buf[]) const {
    uint16_t dataLen = (buf[HEADER_LEN] << 8) + (buf[HEADER_LEN + 1]);
    return dataLen;
}

void PmsX003::clearData() {
    uint16_t clearingTimeout = millis() + 3000;
    while (serial.available() > 0 && (millis() < clearingTimeout)) {
        serial.read();
        delay(5);
    }
    if (serial.available() == 0) {
        logger.logDebug("Buffer successfully cleared.");
    } else {
        logger.logDebug("Buffer not completely cleared.");
    }
}

void PmsX003::printChecksums(const uint16_t sum, const uint16_t receivedSum) const {
    logger.logDebug("Checksum mismatch!");
    logger.logDebug("Calculated sum: %u", sum);
    logger.logDebug("Received sum: %u", receivedSum);
}

bool PmsX003::validateChecksum(const uint8_t buf[], const uint8_t checksumStartPos) const {
    uint16_t sum = calculateChecksum(buf, checksumStartPos);
    uint16_t receivedSum = extractChecksum(buf, checksumStartPos);
    bool checksumMatch = sum == receivedSum;

    if (!checksumMatch) {
        printChecksums(sum, receivedSum);
    }
    return checksumMatch;
}

uint16_t PmsX003::extractChecksum(const uint8_t buf[], const uint8_t checksumStartPos) const {
    return (buf[checksumStartPos] << 8) + buf[checksumStartPos + 1];
}

uint16_t PmsX003::calculateChecksum(const uint8_t buf[], const uint8_t checksumStartPos) const {
    uint16_t sum = 0;
    for (uint8_t i = 0; i < checksumStartPos; i++) {
        sum += buf[i];
    }
    return sum;
}

uint16_t PmsX003::extractPm01(const uint8_t buf[]) const {
    return (buf[PM01_FIRST_POS] << 8) + buf[PM01_FIRST_POS + 1];
}

uint16_t PmsX003::extractPm25(const uint8_t buf[]) const {
    return (buf[PM25_FIRST_POS] << 8) + buf[PM25_FIRST_POS + 1];
}

uint16_t PmsX003::extractPm10(const uint8_t buf[]) const {
    return (buf[PM10_FIRST_POS] << 8) + buf[PM10_FIRST_POS + 1];
}

bool PmsX003::wakeup() {
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

bool PmsX003::sleep() {
    digitalWrite(setPin, SLEEP_VALUE);
    int8_t checkCount = 3;
    do {
        delay(100);
    } while ((--checkCount >= 0) && (readData() != EmptyData()));
    bool successful = checkCount >= 0;
    if (!successful) {
        logger.logError("Sleep unsuccessful!");
    }
    clearData();
    return successful;
}

/*
 * Pms3003.h
 *
 * Author: Piotr Borkowski
 *
 * Handles Pms3003 device.
 *
 */

#ifndef PMS3003_PMS3003_H_
#define PMS3003_PMS3003_H_

class Logger;

#include "Arduino.h"
#include "Stream.h"
#include "NullLogger.h"
#include "PmsData.h"
#include "EmptyData.h"

class Pms3003 {
public:
    /**
     * Creates a Pms3003 handler that will read the data from Pms3003 on given serial
     * and will use given pin to put the device to sleep and wake it up.
     * Uses provided logger to log information.
     * @param pmsSerial Serial to be used for communication with Pms3003
     * @param setPin Pin to be used to put Pms3003 to sleep and wake it up
     * @param logger {@link Logger} to be used for logging
     */
    Pms3003(Stream& pmsSerial, uint8_t setPin, const Logger& logger = DefaultNullLogger);

    /**
     * destructor
     */
    virtual ~Pms3003();

    /**
     * Wakes Pms3003 up.
     * @return true if successfully waken up, false otherwise
     */
    bool wakeup();

    /**
     * Puts Pms3003 to sleep.
     * @return true if successfully put to sleep, false otherwise
     */
    bool sleep();

    /**
     * Reads one measurement from the serial.
     * IT IS BLOCKING READING NOW.
     * TODO TO BE CHANGED TO NON BLOCKING
     * @return Measurement packed into {@link PmsData}.
     *          If received data is not correct will return {@link EmptyData}.
     */
    PmsData readData();

    /**
     * Clears not read data remaining in the serial.
     */
    void clearData();

private:
    static const uint8_t BUF_LEN = 24;
    static const uint8_t HEADER_LEN = 2;
    static const uint8_t DATA_LEN = BUF_LEN - HEADER_LEN;

    static const uint8_t HEADER_FIRST_BYTE = 0x42;
    static const uint8_t HEADER_SECOND_BYTE = 0x4d;
    static constexpr uint8_t HEADER[HEADER_LEN] = { HEADER_FIRST_BYTE, HEADER_SECOND_BYTE };

    static const uint8_t PM01_FIRST_POS = BUF_LEN - 14;
    static const uint8_t PM25_FIRST_POS = BUF_LEN - 12;
    static const uint8_t PM10_FIRST_POS = BUF_LEN - 10;
    static const uint8_t CHECKSUM_FIRST_POS = BUF_LEN - 2;

    static const uint8_t WAKEUP_VALUE = 1;
    static const uint8_t SLEEP_VALUE = 0;

    Stream& serial;
    const uint8_t setPin;
    const Logger* logger;

    bool validateChecksum(const uint8_t buf[]) const;
    uint16_t extractChecksum(const uint8_t buf[]) const;
    uint16_t calculateChecksum(const uint8_t buf[]) const;

    uint16_t extractPm01(const uint8_t buf[]) const;
    uint16_t extractPm25(const uint8_t buf[]) const;
    uint16_t extractPm10(const uint8_t buf[]) const;

    void insertHeaderToBuf(uint8_t buf[]) const;
    void printBufferContents(const uint8_t buf[]) const;
    void printChecksums(const uint16_t sum, const uint16_t receivedSum) const;
};

#endif /* PMS3003_PMS3003_H_ */

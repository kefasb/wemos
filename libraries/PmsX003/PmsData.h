/*
 * PmsData.h
 *
 * Author: Piotr Borkowski
 *
 * Wraps measure from Pms device into object.
 *
 */

#ifndef PMS3003_PMSDATA_H_
#define PMS3003_PMSDATA_H_

#include <stdint.h>
#include <Print.h>

typedef uint16_t PMUnit;

class PmsData {
public:
    /**
     * Creates a data with 0 values.
     */
    PmsData();

    /**
     * Creates a data with given values.
     */
    PmsData(PMUnit pm01, PMUnit pm25, PMUnit pm10);

    /**
     * destructor
     */
    virtual ~PmsData();

    PMUnit getPm01() const;
    PMUnit getPm25() const;
    PMUnit getPm10() const;

    bool operator==(const PmsData& other) const;

    bool operator!=(const PmsData& other) const;

    PmsData operator+(const PmsData& other) const;

    /**
     * Prints containing values on the given Print interface.
     */
    void print(Print& out) const;
    void printPm25AndPm10(Print& out) const;
    void printPm25AndPm10(Print& out, const char* const format) const;

private:
    PMUnit pm01;
    PMUnit pm25;
    PMUnit pm10;

};

#endif /* PMS3003_PMSDATA_H_ */

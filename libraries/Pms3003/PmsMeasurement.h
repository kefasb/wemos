/*
 * PmsMeasurement.h
 *
 * Author: Piotr Borkowski
 *
 * Handles a bunch of measurements from given Pms device. Returns an average of the measurements done.
 *
 */

#ifndef PMS3003_PMS3003MEASUREMENT_H_
#define PMS3003_PMS3003MEASUREMENT_H_

#include <stdint.h>
#include "Pms3003.h"
#include "PmsData.h"
#include "EmptyData.h"

typedef uint16_t (PmsData::*PMGetter)(void) const;
typedef uint8_t MeasureNumber;

class PmsMeasurement {
public:
    /**
     * Creates a measurements object that will use provided pms to read data from.
     * It will perform a number of warmup measurement that will not be taken to the result.
     * After warmup measurements it will perform a number of measurements that will be taken
     * for average counting.
     * @param pms Pms device to read the data from
     * @param measures Number of measurements to calculate average from
     * @param warmupmeasures Number of warmup measurements
     */
    PmsMeasurement(Pms3003& pms, MeasureNumber measures = 20, MeasureNumber warmupMeasures = 15);

    /**
     * desctructor
     */
    virtual ~PmsMeasurement();

    /**
     * Performs a number of measurements and returns an average.
     * Reads data from Pms until desired number of valid measures are collected.
     * It wakes the Pms up before measurements and put the Pms to sleep after measurements are done.
     * IT IS BLOCKING MEASUREMENT NOW
     * TODO TO BE CHANGED TO NON BLOCKING
     * @return Average of measurements performed packed into {@link PmsData}
     */
    PmsData measure() const;

private:
    static const MeasureNumber HIGH_MEASURES_DROP = 2;
    static const MeasureNumber LOW_MEASURES_DROP = 2;

    Pms3003& pms;
    const MeasureNumber warmupMeasuresNumber;
    const MeasureNumber measuresNumber;
    const MeasureNumber measuresToCount;

    bool wakupPms() const;bool sleepPms() const;
    void warmup() const;
    void doMeasurements(PMUnit pm01MeasuresData[], PMUnit pm25MeasuresData[],
            PMUnit pm10MeasuresData[]) const;
    PmsData measurementsAverage(PMUnit pm01MeasuresData[], PMUnit pm25MeasuresData[],
            PMUnit pm10MeasuresData[]) const;
    void sort(PMUnit measuresData[]) const;
    void validateMeasurements(PMUnit pm01MeasuresData[], PMUnit pm25MeasuresData[],
            PMUnit pm10MeasuresData[]) const;
};

#endif /* PMS3003_PMS3003MEASUREMENT_H_ */

/*
 * PmsMeasurement.cpp
 *
 * Author: Piotr Borkowski
 *
 */

#include "PmsMeasurement.h"

PmsMeasurement::PmsMeasurement(Pms3003& pms, MeasureNumber measures, MeasureNumber warmupMeasures) :
        pms(pms), warmupMeasuresNumber(warmupMeasures), measuresNumber(measures), measuresToCount(
                measuresNumber - HIGH_MEASURES_DROP - LOW_MEASURES_DROP) {
}

PmsMeasurement::~PmsMeasurement() {
}

void PmsMeasurement::warmup() const {
    MeasureNumber warmupCount = 0;
    while (warmupCount < warmupMeasuresNumber) {
        if (pms.readData() != EmptyData()) {
            ++warmupCount;
        }
    }
    pms.clearData();
}

bool PmsMeasurement::wakupPms() const {
    return pms.wakeup();
}

bool PmsMeasurement::sleepPms() const {
    return pms.sleep();
}

void PmsMeasurement::doMeasurements(PMUnit pm01MeasuresData[], PMUnit pm25MeasuresData[],
        PMUnit pm10MeasuresData[]) const {
    uint8_t measureCount = 0;
    while (measureCount < measuresNumber) {
        PmsData pmsData = pms.readData();
        if (pmsData != EmptyData()) {
            pm01MeasuresData[measureCount] = pmsData.getPm01();
            pm25MeasuresData[measureCount] = pmsData.getPm25();
            pm10MeasuresData[measureCount] = pmsData.getPm10();
            ++measureCount;
        }
    }
}

PmsData PmsMeasurement::measurementsAverage(PMUnit pm01MeasuresData[], PMUnit pm25MeasuresData[],
        PMUnit pm10MeasuresData[]) const {
    PMUnit pm01Sum = 0;
    PMUnit pm25Sum = 0;
    PMUnit pm10Sum = 0;
    for (MeasureNumber i = 0; i < measuresNumber; i++) {
        pm01Sum += pm01MeasuresData[i];
        pm25Sum += pm25MeasuresData[i];
        pm10Sum += pm10MeasuresData[i];
    }
    PmsData average = PmsData(pm01Sum / measuresToCount, pm25Sum / measuresToCount,
            pm10Sum / measuresToCount);
    return average;
}

void PmsMeasurement::sort(PMUnit measuresData[]) const {
    for (MeasureNumber i = 0; i < measuresNumber - 1; i++) {
        PMUnit lowest = measuresData[i];
        MeasureNumber lowestIndex = i;
        for (MeasureNumber j = i + 1; j < measuresNumber; j++) {
            PMUnit current = measuresData[i];
            if (current < lowest) {
                lowest = current;
                lowestIndex = j;
            }
        }
        if (i != lowestIndex) {
            PMUnit tmp = measuresData[lowestIndex];
            measuresData[lowestIndex] = measuresData[i];
            measuresData[i] = tmp;
        }
    }
}

void PmsMeasurement::validateMeasurements(PMUnit pm01MeasuresData[], PMUnit pm25MeasuresData[],
        PMUnit pm10MeasuresData[]) const {
    sort(pm01MeasuresData);
    sort(pm25MeasuresData);
    sort(pm10MeasuresData);
    for (MeasureNumber i = 0; i < LOW_MEASURES_DROP; i++) {
        pm01MeasuresData[i] = 0;
        pm25MeasuresData[i] = 0;
        pm10MeasuresData[i] = 0;
    }
    for (MeasureNumber i = measuresNumber - HIGH_MEASURES_DROP - 1; i < measuresNumber; i++) {
        pm01MeasuresData[i] = 0;
        pm25MeasuresData[i] = 0;
        pm10MeasuresData[i] = 0;
    }
}

PmsData PmsMeasurement::measure() const {
    PmsData result = EmptyData();
    if (!wakupPms()) {
        return result;
    }
    warmup();

    PMUnit pm01MeasuresData[measuresNumber];
    PMUnit pm25MeasuresData[measuresNumber];
    PMUnit pm10MeasuresData[measuresNumber];
    doMeasurements(pm01MeasuresData, pm25MeasuresData, pm10MeasuresData);

    sleepPms();

    validateMeasurements(pm01MeasuresData, pm25MeasuresData, pm10MeasuresData);
    result = measurementsAverage(pm01MeasuresData, pm25MeasuresData, pm10MeasuresData);

    return result;
}

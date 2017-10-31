/*
 * TempRhData.h
 *
 * Author: Piotr Borkowski
 *
 */

#ifndef TEMPRH_TEMPRHDATA_H_
#define TEMPRH_TEMPRHDATA_H_

#include <Arduino.h>
#include <Print.h>

class TempRhData {
public:
    TempRhData();
    TempRhData(const float temp, const float rh);
    virtual ~TempRhData();

    float getTemp() const;
    float getRh() const;

    bool operator==(const TempRhData& other) const;

    bool operator!=(const TempRhData& other) const;

    void print(Print& out) const;

private:
    float temperature;
    float relativeHumidity;
    static const int NO_TEMPERATURE = -256;
    static const int NO_HUMIDITY = -256;
};

#endif /* TEMPRH_TEMPRHDATA_H_ */

/*
 * TempRhData.cpp
 *
 * Author: Piotr Borkowski
 *
 */

#include "TempRhData.h"

TempRhData::TempRhData() :
        temperature(NO_TEMPERATURE), relativeHumidity(NO_HUMIDITY) {
}

TempRhData::TempRhData(const float temp, const float rh) :
        temperature(temp), relativeHumidity(rh) {
}

TempRhData::~TempRhData() {
}

float TempRhData::getTemp() const {
    return temperature;
}

float TempRhData::getRh() const {
    return relativeHumidity;
}

void TempRhData::print(Print& out) const {
    out.print("Temp: ");
    out.println(getTemp());
    out.print("RH: ");
    out.println(getRh());
}

bool TempRhData::operator ==(const TempRhData& other) const {
    return temperature == other.temperature
            && relativeHumidity == other.relativeHumidity;
}

bool TempRhData::operator !=(const TempRhData& other) const {
    return !(operator==(other));
}

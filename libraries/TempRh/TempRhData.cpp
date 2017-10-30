/*
 * TempRhData.cpp
 *
 * Author: Piotr Borkowski
 *
 */

#include <TempRhData.h>

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

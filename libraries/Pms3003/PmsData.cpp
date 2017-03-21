/*
 * PmsData.cpp
 *
 * Author: Piotr Borkowski
 *
 */

#include "PmsData.h"

PmsData::PmsData() :
        PmsData(0, 0, 0) {
}

PmsData::PmsData(PMUnit pm01, PMUnit pm25, PMUnit pm10) :
        pm01(pm01), pm25(pm25), pm10(pm10) {
}

PmsData::~PmsData() {
}

PMUnit PmsData::getPm01() const {
    return pm01;
}

PMUnit PmsData::getPm25() const {
    return pm25;
}

PMUnit PmsData::getPm10() const {
    return pm10;
}

bool PmsData::operator ==(const PmsData& other) const {
    return getPm01() == other.getPm01() && getPm25() == other.getPm25()
            && getPm10() == other.getPm10();
}

bool PmsData::operator !=(const PmsData& other) const {
    return !(operator ==(other));
}

PmsData PmsData::operator+(const PmsData& other) const {
    return PmsData(getPm01() + other.getPm01(), getPm25() + other.getPm25(),
            getPm10() + other.getPm10());
}

void PmsData::print(Print& out) const {
    out.print("PM01: ");
    out.println(getPm01());
    out.print("PM25: ");
    out.println(getPm25());
    out.print("PM10: ");
    out.println(getPm10());
}

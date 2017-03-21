/*
 * Duration.cpp
 *
 * Author: Piotr Borkowski
 *
 */

#include "Duration.h"

Duration::Duration() {
}

Duration::~Duration() {
}

DurationUnit Duration::Seconds(uint8_t seconds, TimeBase base) {
    return seconds * base;
}

DurationUnit Duration::Minutes(uint8_t minutes, TimeBase base) {
    return minutes * SECONDS_IN_MINUTE * base;
}

/*
 * TimeoutTimer.cpp
 *
 * Author: Piotr Borkowski
 *
 */

#include "TimeoutTimer.h"

TimeoutTimer::TimeoutTimer(uint32_t timeout, void (*callback)()) :
        IntervalTimer(timeout, callback, 1) {
}

TimeoutTimer::~TimeoutTimer() {
}


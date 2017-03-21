/*
 * IntervalTimer.cpp
 *
 * Author: Piotr Borkowski
 *
 */

#include "IntervalTimer.h"

IntervalTimer::IntervalTimer(uint32_t interval, void (*callback)(), uint16_t loopsLimit) :
        UnconditionalTimer(interval, callback), loopsLimit(loopsLimit), loopsCount(0) {
}

IntervalTimer::~IntervalTimer() {
}

void IntervalTimer::postAction() {
    if (INFINITE_LOOPS != loopsLimit && loopsCount < loopsLimit) {
        ++loopsCount;
    }
    loopStartTime = millis();
}

bool IntervalTimer::stopCondition() {
    if (INFINITE_LOOPS == loopsLimit) {
        return false;
    } else if (loopsCount < loopsLimit) {
        return false;
    } else {
        return true;
    }
}

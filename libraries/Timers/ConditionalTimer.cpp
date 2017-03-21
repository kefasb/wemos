/*
 * ConditionalTimer.cpp
 *
 * Author: Piotr Borkowski
 *
 */

#include "ConditionalTimer.h"

ConditionalTimer::ConditionalTimer(uint32_t interval, bool (*checkCondition)(),
        uint16_t checksLimit) :
        BaseTimer(interval), checksLimit(checksLimit), checksCount(0), conditionMet(false), checkCondition(
                checkCondition) {
}

ConditionalTimer::~ConditionalTimer() {
}

void ConditionalTimer::performAction() {
    conditionMet = checkCondition();
}

void ConditionalTimer::postAction() {
    if (checksCount < checksLimit) {
        checksCount++;
    }
    loopStartTime = millis();
}

bool ConditionalTimer::stopCondition() {
    return (checksCount >= checksLimit) || conditionMet;
}

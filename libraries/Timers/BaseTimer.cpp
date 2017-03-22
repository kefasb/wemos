/*
 * Timer.cpp
 *
 * Author: Piotr Borkowski
 *
 */

#include "BaseTimer.h"

BaseTimer::BaseTimer(uint32_t waitTime) :
        loopStartTime(0), running(false), waitTime(waitTime) {
}

BaseTimer::~BaseTimer() {
}

bool BaseTimer::isRunning() {
    return running;
}

void BaseTimer::start() {
    loopStartTime = millis();
    if (!stopCondition()) {
        running = true;
    }
}

void BaseTimer::stop() {
    running = false;
}

bool BaseTimer::isMyTime() {
    return (millis() - loopStartTime >= waitTime);
}

void BaseTimer::tick() {
    if (isRunning() && isMyTime()) {
        performAction();

        postAction();

        if (stopCondition()) {
            stop();
        }
    }
}

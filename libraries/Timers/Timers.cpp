/*
 * Timers.cpp
 *
 * Author: Piotr Borkowski
 *
 */

#include "Timers.h"

Timers::Timers() {
    for (TimerId id = 0; id < MAX_TIMERS; id++) {
        timers[id] = NULL;
    }
}

Timers::~Timers() {
    for (TimerId id = 0; id < MAX_TIMERS; id++) {
        if (NULL != timers[id]) {
            deleteTimer(id);
        }
    }
}

TimerId Timers::findFreeTimerId() {
    TimerId freeId = INVALID_TIMER_ID;
    for (TimerId id = 0; id < MAX_TIMERS; id++) {
        if (NULL == timers[id]) {
            freeId = id;
            break;
        }
    }
    return freeId;
}

bool Timers::isTimerIdValid(TimerId timerId) {
    return timerId >= 0;
}

void Timers::assignIdToTimer(TimerId timerId, ITimer* timer) {
    timers[timerId] = timer;
}

TimerId Timers::timeoutTimer(uint32_t timeout, void (*callback)()) {
    TimerId timerId = findFreeTimerId();
    if (isTimerIdValid(timerId)) {
        TimeoutTimer* timeoutTimer = new TimeoutTimer(timeout, callback);
        assignIdToTimer(timerId, timeoutTimer);
        timeoutTimer->start();
    }
    return timerId;
}

TimerId Timers::intervalTimer(uint32_t interval, void (*callback)()) {
    TimerId timerId = findFreeTimerId();
    if (isTimerIdValid(timerId)) {
        IntervalTimer* intervalTimer = new IntervalTimer(interval, callback);
        assignIdToTimer(timerId, intervalTimer);
        intervalTimer->start();
    }
    return timerId;
}

TimerId Timers::intervalTimer(uint32_t interval, void (*callback)(), uint16_t loopsLimit) {
    TimerId timerId = findFreeTimerId();
    if (isTimerIdValid(timerId)) {
        IntervalTimer* intervalTimer = new IntervalTimer(interval, callback, loopsLimit);
        assignIdToTimer(timerId, intervalTimer);
        intervalTimer->start();
    }
    return timerId;
}

bool Timers::isDeadTimer(TimerId id) {
    return (NULL != timers[id]) && (!timers[id]->isRunning());
}

void Timers::deleteTimer(TimerId id) {
    delete timers[id];
    timers[id] = NULL;
}

void Timers::deleteDeadTimers() {
    for (TimerId id = 0; id < MAX_TIMERS; id++) {
        if (isDeadTimer(id)) {
            deleteTimer(id);
        }
    }
}

void Timers::tickTimer(TimerId id) const {
    if (NULL != timers[id]) {
        timers[id]->tick();
    }
}

void Timers::performTimersActions() const {
    for (TimerId id = 0; id < MAX_TIMERS; id++) {
        tickTimer(id);
    }
}

void Timers::tick() {
    performTimersActions();

    deleteDeadTimers();
}

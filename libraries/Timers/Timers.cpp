/*
 * Timers.cpp
 *
 * Author: Piotr Borkowski
 *
 */

#include "Timers.h"

Timers::Timers() {
    for (TimerSlot id = 0; id < MAX_TIMERS; id++) {
        timers[id] = NULL;
    }
}

Timers::~Timers() {
    for (TimerSlot id = 0; id < MAX_TIMERS; id++) {
        if (NULL != timers[id]) {
            deleteTimer(id);
        }
    }
}

TimerSlot Timers::findFreeTimerId() {
    TimerSlot freeId = INVALID_TIMER_ID;
    for (TimerSlot id = 0; id < MAX_TIMERS; id++) {
        if (NULL == timers[id]) {
            freeId = id;
            break;
        }
    }
    return freeId;
}

bool Timers::isTimerIdValid(TimerSlot timerId) {
    return timerId >= 0;
}

void Timers::assignIdToTimer(TimerSlot timerId, ITimer* timer) {
    timers[timerId] = timer;
}

TimerSlot Timers::timeoutTimer(uint32_t timeout, void (*callback)()) {
    TimerSlot timerId = findFreeTimerId();
    if (isTimerIdValid(timerId)) {
        TimeoutTimer* timeoutTimer = new TimeoutTimer(timeout, callback);
        assignIdToTimer(timerId, timeoutTimer);
        timeoutTimer->start();
    }
    return timerId;
}

TimerSlot Timers::intervalTimer(uint32_t interval, void (*callback)()) {
    TimerSlot timerId = findFreeTimerId();
    if (isTimerIdValid(timerId)) {
        IntervalTimer* intervalTimer = new IntervalTimer(interval, callback);
        assignIdToTimer(timerId, intervalTimer);
        intervalTimer->start();
    }
    return timerId;
}

TimerSlot Timers::intervalTimer(uint32_t interval, void (*callback)(), uint16_t loopsLimit) {
    TimerSlot timerId = findFreeTimerId();
    if (isTimerIdValid(timerId)) {
        IntervalTimer* intervalTimer = new IntervalTimer(interval, callback, loopsLimit);
        assignIdToTimer(timerId, intervalTimer);
        intervalTimer->start();
    }
    return timerId;
}

bool Timers::isDeadTimer(TimerSlot id) {
    return (NULL != timers[id]) && (!timers[id]->isRunning());
}

void Timers::deleteTimer(TimerSlot id) {
    delete timers[id];
    timers[id] = NULL;
}

void Timers::deleteDeadTimers() {
    for (TimerSlot id = 0; id < MAX_TIMERS; id++) {
        if (isDeadTimer(id)) {
            deleteTimer(id);
        }
    }
}

void Timers::tickTimer(TimerSlot id) const {
    if (NULL != timers[id]) {
        timers[id]->tick();
    }
}

void Timers::performTimersActions() const {
    for (TimerSlot id = 0; id < MAX_TIMERS; id++) {
        tickTimer(id);
    }
}

void Timers::tick() {
    performTimersActions();

    deleteDeadTimers();
}

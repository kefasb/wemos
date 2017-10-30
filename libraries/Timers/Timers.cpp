/*
 * Timers.cpp
 *
 * Author: Piotr Borkowski
 *
 */

#include "Timers.h"

Timers::Timers(const ILogger& logger) :
		logger(logger) {
	for (TimerSlot slot = 0; slot < MAX_TIMERS; slot++) {
		timers[slot] = NULL;
	}
}

Timers::~Timers() {
	for (TimerSlot slot = 0; slot < MAX_TIMERS; slot++) {
		if (NULL != timers[slot]) {
			deleteTimer(slot);
		}
	}
}

TimerSlot Timers::findFreeTimerSlot() {
	TimerSlot freeSlot = INVALID_TIMER;
	for (TimerSlot slot = 0; slot < MAX_TIMERS; slot++) {
		if (NULL == timers[slot]) {
			freeSlot = slot;
			break;
		}
	}
	return freeSlot;
}

bool Timers::isTimerSlotValid(TimerSlot timerSlot) {
	return timerSlot >= 0;
}

void Timers::assignSlotToTimer(TimerSlot timerSlot, ITimer* timer) {
	timers[timerSlot] = timer;
}

bool Timers::canCreateTimer(TimerSlot timerSlot) {
	bool timerSlotValid = isTimerSlotValid(timerSlot);
	if (!timerSlotValid) {
		logger.logError("Free timer slot not found. Unable to create timer");
	}
	return timerSlotValid;
}

TimerSlot Timers::timeoutTimer(uint32_t timeout, void (*callback)()) {
	TimerSlot timerSlot = findFreeTimerSlot();
	if (canCreateTimer(timerSlot)) {
		TimeoutTimer* timeoutTimer = new TimeoutTimer(timeout, callback);
		assignSlotToTimer(timerSlot, timeoutTimer);

		timeoutTimer->start();
	}
	return timerSlot;
}

TimerSlot Timers::intervalTimer(uint32_t interval, void (*callback)()) {
	TimerSlot timerSlot = findFreeTimerSlot();
	if (canCreateTimer(timerSlot)) {
		IntervalTimer* intervalTimer = new IntervalTimer(interval, callback);
		assignSlotToTimer(timerSlot, intervalTimer);
		intervalTimer->start();
	}
	return timerSlot;
}

TimerSlot Timers::intervalTimer(uint32_t interval, void (*callback)(),
		uint16_t loopsLimit) {
	TimerSlot timerSlot = findFreeTimerSlot();
	if (canCreateTimer(timerSlot)) {
		IntervalTimer* intervalTimer = new IntervalTimer(interval, callback,
				loopsLimit);
		assignSlotToTimer(timerSlot, intervalTimer);
		intervalTimer->start();
	}
	return timerSlot;
}

bool Timers::isDeadTimer(TimerSlot slot) {
	return (NULL != timers[slot]) && (!timers[slot]->isRunning());
}

void Timers::deleteTimer(TimerSlot slot) {
	delete timers[slot];
	timers[slot] = NULL;
}

void Timers::deleteDeadTimers() {
	for (TimerSlot slot = 0; slot < MAX_TIMERS; slot++) {
		if (isDeadTimer(slot)) {
			deleteTimer(slot);
		}
	}
}

void Timers::tickTimer(TimerSlot slot) const {
	if (NULL != timers[slot]) {
		timers[slot]->tick();
	}
}

void Timers::performTimersActions() const {
	for (TimerSlot slot = 0; slot < MAX_TIMERS; slot++) {
		tickTimer(slot);
	}
}

void Timers::tick() {
	performTimersActions();

	deleteDeadTimers();
}

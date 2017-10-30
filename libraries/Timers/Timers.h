/*
 * Timers.h
 *
 * Author: Piotr Borkowski
 *
 * Manages timers.
 */

#ifndef TIMER_TIMERS_H_
#define TIMER_TIMERS_H_

#include <stddef.h>
#include "ITimer.h"
#include "TimeoutTimer.h"
#include "IntervalTimer.h"
#include "ILogger.h"
#include "NullLogger.h"

typedef int8_t TimerSlot;

class Timers {
public:
	static const int8_t INVALID_TIMER = -1;

	/**
	 * Creates timers managing object.
	 */
	Timers(const ILogger& logger = DefaultNullLogger);

	/**timer expires
	 * destructor
	 */
	virtual ~Timers();

	/**
	 * Tries to create {@link TimeoutTimer} object with given settings.
	 * @param timeout Timeout after which the callback will be called
	 * @param callback Callback function to be called after timer expires
	 * @return Valid {@link TimerId} when successfully created timer,
	 *          {@link INVALID_TIMER_ID} otherwise.
	 */
	TimerSlot timeoutTimer(uint32_t timeout, void (*callback)());

	/**
	 * Tries to create infinite {@link IntervalTimer} object with given settings.
	 * @param interval Interval after which the callback will be called
	 * @param callback Callback function to be called after each interval
	 * @return Valid {@link TimerId} when successfully created timer,
	 *          {@link INVALID_TIMER_ID} otherwise.
	 */
	TimerSlot intervalTimer(uint32_t interval, void (*callback)());

	/**
	 * Tries to create {@link IntervalTimer} object with given settings.
	 * @param interval Interval after which the callback will be called
	 * @param callback Callback function to be called after each interval
	 * @param loopsLimit Loops number after which the timer will expire
	 * @return Valid {@link TimerId} when successfully created timer,
	 *          {@link INVALID_TIMER_ID} otherwise.
	 */
	TimerSlot intervalTimer(uint32_t interval, void (*callback)(),
			uint16_t loopsLimit);

	/**
	 * Timers tick
	 */
	void tick();

private:
	typedef uint16_t TimerId;
	struct TimerWithId {
		ITimer* timer;
		TimerId id;
	};

	static const uint8_t MAX_TIMERS = 15;

	TimerId maxId = 0;
	ITimer* timers[MAX_TIMERS];
	TimerWithId timersWithId[MAX_TIMERS];
	const ILogger& logger;

	bool isTimerSlotValid(TimerSlot timerSlot);bool isDeadTimer(TimerSlot slot);
	TimerSlot findFreeTimerSlot();
	void assignSlotToTimer(TimerSlot timerSlot, ITimer* timer);
	void deleteDeadTimers();
	void performTimersActions() const;
	void deleteTimer(TimerSlot slot);
	void tickTimer(TimerSlot slot) const;bool canCreateTimer(
			TimerSlot timerSlot);
};

#endif /* TIMER_TIMERS_H_ */

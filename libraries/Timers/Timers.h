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

typedef int8_t TimerId;

class Timers {
public:
    static const int8_t INVALID_TIMER_ID = -1;

    /**
     * Creates timers managing object.
     */
    Timers();

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
    TimerId timeoutTimer(uint32_t timeout, void (*callback)());

    /**
     * Tries to create infinite {@link IntervalTimer} object with given settings.
     * @param interval Interval after which the callback will be called
     * @param callback Callback function to be called after each interval
     * @return Valid {@link TimerId} when successfully created timer,
     *          {@link INVALID_TIMER_ID} otherwise.
     */
    TimerId intervalTimer(uint32_t interval, void (*callback)());

    /**
     * Tries to create {@link IntervalTimer} object with given settings.
     * @param interval Interval after which the callback will be called
     * @param callback Callback function to be called after each interval
     * @param loopsLimit Loops number after which the timer will expire
     * @return Valid {@link TimerId} when successfully created timer,
     *          {@link INVALID_TIMER_ID} otherwise.
     */
    TimerId intervalTimer(uint32_t interval, void (*callback)(), uint16_t loopsLimit);

    /**
     * Timers tick
     */
    void tick();

private:
    static const uint8_t MAX_TIMERS = 15;

    ITimer* timers[MAX_TIMERS];

    bool isTimerIdValid(TimerId timerId);
    bool isDeadTimer(TimerId id);
    TimerId findFreeTimerId();
    void assignIdToTimer(TimerId timerId, ITimer* timer);
    void deleteDeadTimers();
    void performTimersActions() const;
    void deleteTimer(TimerId id);
    void tickTimer(TimerId id) const;
};

#endif /* TIMER_TIMERS_H_ */

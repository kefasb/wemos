/*
 * IntervalTimer.h
 *
 * Author: Piotr Borkowski
 *
 * Timer which will call the callback function after each interval.
 * Performs until defined number of loops or infinite when loops limit not defined.
 */

#ifndef TIMER_INTERVALTIMER_H_
#define TIMER_INTERVALTIMER_H_

#include "./base/UnconditionalTimer.h"

class IntervalTimer: public UnconditionalTimer {
public:
    /**
     * Creates interval timer object. May be infinite when loops limit not given.
     * @param interval Interval after which the callback will be called
     * @param callback Callback function to be called after each interval
     * @param loopsLimit Loops number after which the timer will expire.
     *          When not given then means that never expires.
     */
    IntervalTimer(uint32_t interval, void (*callback)(), uint16_t loopsLimit = INFINITE_LOOPS);

    /**
     * destructor
     */
    virtual ~IntervalTimer();

protected:
    void postAction();

    bool stopCondition();

    static const uint16_t INFINITE_LOOPS = UINT16_MAX;
private:

    const uint16_t loopsLimit;
    uint16_t loopsCount;
};

#endif /* TIMER_INTERVALTIMER_H_ */

/*
 * TimeoutTimer.h
 *
 * Author: Piotr Borkowski
 *
 * Timer which will call given callback function after the timeout.
 *
 */

#ifndef TIMER_TIMEOUTTIMER_H_
#define TIMER_TIMEOUTTIMER_H_

#include "IntervalTimer.h"

class TimeoutTimer: public IntervalTimer {
public:
    /**
     * Creates timeout timer object. May be created only with time without
     * callback function. In such situation no function will be called after the timeout.
     * This behaviour may be useful for the situations when only timeout checking
     * is required.
     * @param timeout Timeout after which the callback function will be called if given
     * @param callback Callback function to be called
     */
    TimeoutTimer(uint32_t timeout, void (*callback)() = NULL);

    /**
     * destructor
     */
    virtual ~TimeoutTimer();

protected:

private:
};

#endif /* TIMER_TIMEOUTTIMER_H_ */

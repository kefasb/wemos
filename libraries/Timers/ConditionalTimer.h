/*
 * ConditionalTimer.h
 *
 * Author: Piotr Borkowski
 *
 * Calls given callback function defined number of times and checks the result.
 * Performs until callback function returns false or limit of checks reached.
 *
 */

#ifndef TIMER_CONDITIONALTIMER_H_
#define TIMER_CONDITIONALTIMER_H_

#include "BaseTimer.h"
#include "IntervalTimer.h"

class ConditionalTimer: public BaseTimer {

public:
    /**
     * Creates conditional timer.
     * @param interval Interval after which the checkCondition will be called
     * @param checkCondition Callback function that returns bool to be called after each interval
     * @param checksLimit Limit of loops after which the timer will expire.
     */
    ConditionalTimer(uint32_t interval, bool (*checkCondition)(), uint16_t checksLimit);

    /**
     * destructor
     */
    virtual ~ConditionalTimer();

protected:
    void performAction();

    void postAction();

    bool stopCondition();

private:
    uint16_t checksLimit;
    uint16_t checksCount;
    bool conditionMet;

    bool (*checkCondition)(void);
};

#endif /* TIMER_CONDITIONALTIMER_H_ */

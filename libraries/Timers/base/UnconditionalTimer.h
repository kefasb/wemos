/*
 * UnconditionalTimer.h
 *
 * Author: Piotr Borkowski
 *
 * Timer using void function as callback.
 * Timer lifetime depends only on timing settings.
 */

#ifndef TIMER_UNCONDITIONALTIMER_H_
#define TIMER_UNCONDITIONALTIMER_H_

#include "BaseTimer.h"

class UnconditionalTimer: public BaseTimer {

public:
    virtual ~UnconditionalTimer();

protected:
    UnconditionalTimer(uint32_t waitTime, void (*callback)(void));

    void performAction() final;

private:
    void (*callback)(void);
};

#endif /* TIMER_UNCONDITIONALTIMER_H_ */

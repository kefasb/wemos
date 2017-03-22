/*
 * Timer.h
 *
 * Author: Piotr Borkowski
 *
 * Base class for timers.
 */

#ifndef TIMER_BASETIMER_H_
#define TIMER_BASETIMER_H_

#include <stdint.h>
#include "Arduino.h"
#include "ITimer.h"

class BaseTimer: public ITimer {
public:
    /**
     * destructor
     */
    virtual ~BaseTimer();

    /**
     * Timer tick.
     */
    void tick();

    /**
     * Checks whether the timer is still running.
     * @return true when timer is still running, false otherwise
     */
    bool isRunning();

    /**
     * Starts the timer;
     */
    void start();

    /**
     * Stops the timer.
     */
    void stop();

protected:
    BaseTimer(uint32_t waitTime);

    /**
     * Action to be performed when it is time to.
     */
    virtual void performAction()=0;

    /**
     * Any actions that the timer shall do after performing an action.
     */
    virtual void postAction()=0;

    /**
     * Makes checking whether the timer shall still run.
     */
    virtual bool stopCondition()=0;

    uint32_t loopStartTime;
    bool running;

private:
    bool isMyTime();

    const uint32_t waitTime;
};

#endif /* TIMER_BASETIMER_H_ */

/*
 * Timer.h
 *
 * Author: Piotr Borkowski
 *
 * Timer interface.
 */

#ifndef TIMER_TIMER_H_
#define TIMER_TIMER_H_

#include <stdint.h>
#include "Arduino.h"
#include "ITimer.h"

template<typename T>
class Timer: public virtual ITimer {

public:
    /**
     * destructor
     */
    virtual ~Timer();

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
    /**
     * Creates timer object with given parameters.
     * @param someTime Time after which the timer will do actions
     * @param callback Callback function to call after given time
     */
    Timer(uint32_t someTime, T (*callback)());

    /**
     * Any actions that the timer shall do after calling callback function.
     */
    virtual void postCallback() = 0;

    uint32_t loopStartTime;
    bool running;

private:
    bool isMyTime();

    const uint32_t waitTime;
    T (* const callback)();
};

#endif /* TIMER_TIMER_H_ */

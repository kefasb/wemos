/*
 * ITimer.h
 *
 * Author: Piotr Borkowski
 *
 * Timer interface.
 */

#ifndef TIMER_ITIMER_H_
#define TIMER_ITIMER_H_

class ITimer {
public:
    /**
     * Timer tick.
     */
    virtual void tick()=0;

    /**
     * Checks whether the timer is still running.
     * @return true when timer is still running, false otherwise
     */
    virtual bool isRunning()=0;

    /**
     * Starts the timer;
     */
    virtual void start()=0;

    /**
     * Stops the timer.
     */
    virtual void stop()=0;

    /**
     * destructor
     */
    virtual ~ITimer() {
    }
};

#endif /* TIMER_ITIMER_H_ */

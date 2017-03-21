/*
 * Timer.cpp
 *
 * Author: Piotr Borkowski
 *
 */

#include "Timer.h"

template<typename T>
Timer<T>::Timer(uint32_t someTime, T (*callback)()) :
        loopStartTime(0), running(false), waitTime(someTime), callback(callback) {
}

template<typename T>
Timer<T>::~Timer() {
}

template<typename T>
bool Timer<T>::isRunning() {
    return running;
}

template<typename T>
void Timer<T>::start() {
    loopStartTime = millis();
    running = true;
}

template<typename T>
void Timer<T>::stop() {
    running = false;
}

template<typename T>
bool Timer<T>::isMyTime() {
    return (millis() - loopStartTime >= waitTime);
}

template<typename T>
void Timer<T>::tick() {
    if (isRunning() && isMyTime()) {
        if (NULL != callback) {
            callback();
        }
        postCallback();
    }
}

template class Timer<void> ;
template class Timer<bool> ;

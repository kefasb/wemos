/*
 * UnconditionalTimer.cpp
 *
 * Author: Piotr Borkowski
 *
 */

#include "UnconditionalTimer.h"

UnconditionalTimer::UnconditionalTimer(uint32_t waitTime, void (*callback)(void)) :
        BaseTimer(waitTime), callback(callback) {
}

UnconditionalTimer::~UnconditionalTimer() {
}

void UnconditionalTimer::performAction() {
    callback();
}

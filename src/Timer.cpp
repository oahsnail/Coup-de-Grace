#include "Timer.h"
#include <iostream>


using namespace std;

Timer::Timer() {
    paused = false;
    runTime = 0;
    c.restart();
}

void Timer::reset() {
    c.restart();
    runTime = 0;
    paused = false;
}

void Timer::start() {
    if (paused) {
        c.restart();
    }
    paused = false;
}

void Timer::pause() {
    if (!paused) {
        runTime += c.getElapsedTime().asSeconds();
    }
    paused = true;
}

float Timer::getElapsedSeconds() {
    if (!paused) {
        return runTime + c.getElapsedTime().asSeconds();
    }
    return runTime;
}

#include "Timer.h"
#include <iostream>
#include <SFML/Graphics.hpp>


using namespace std;

Timer::Timer() {
    bPaused = false;
    runTime = 0;
    mC.restart();
}

void Timer::reset() {
    mC.restart();
    runTime = 0;
    bPaused = false;
}

void Timer::start() {
    if (bPaused) {
        mC.restart();
    }
    bPaused = false;
}

void Timer::pause() {
    if (!bPaused) {
        runTime += mC.getElapsedTime().asSeconds();
    }
    bPaused = true;
}

float Timer::getElapsedSeconds() {
    if (!bPaused) {
        return runTime + mC.getElapsedTime().asSeconds();
    }
    return runTime;
}

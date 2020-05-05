#ifndef TIMER_H
#define TIMER_H
#include <SFML/Graphics.hpp>


class Timer {
public:
    sf::Clock mC;
    float runTime;
    bool bPaused;

    Timer();
    void reset();
    void start();
    void pause();
    float getElapsedSeconds();



};

#endif // TIMER_H

#ifndef TIMER_H
#define TIMER_H
#include <SFML/Graphics.hpp>


class Timer {
public:
    sf::Clock c;
    float runTime;
    bool paused;

    Timer();
    void reset();
    void start();
    void pause();
    float getElapsedSeconds();



};

#endif // TIMER_H

#ifndef PLATFORM_H
#define PLATFORM_H
#include <SFML/Graphics.hpp>

class Platform {
public:
    float xVel;
    float yVel;
    float top;
    float bottom;
    float left;
    float right;

    sf::Sprite image;
    Platform(float x, float y, sf::Sprite s);
};

#endif // PLATFORM_H

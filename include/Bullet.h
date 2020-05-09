#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>
#include "Constants.h"


class Bullet {
public:
    Direction bulletDir;
    Bullet(Direction d, sf::Color c);
    void setDirection(Direction d) {
        bulletDir = d;
    }
    Direction getDirection() {
        return bulletDir;
    }
    sf::RectangleShape image;

    int getRight() {
        return image.getPosition().x + image.getLocalBounds().width;
    }
    int getLeft() {
        return image.getPosition().x;
    }
    int getBottom() {
        return image.getPosition().y + image.getLocalBounds().height;
    }
    int getTop() {
        return image.getPosition().y;
    }


};

#endif // BULLET_H

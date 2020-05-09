#include "Bullet.h"
#include <iostream>

using namespace std;

Bullet::Bullet(Direction d, sf::Color c) {
    image.setSize(sf::Vector2f(BULLET_SIZE, BULLET_SIZE));
    image.setFillColor(c);
    setDirection(d);
}

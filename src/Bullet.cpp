#include "Bullet.h"
#include <iostream>

using namespace std;

Bullet::Bullet(Direction d, sf::Color c) {
    image.setSize(sf::Vector2f(BULLET_SIZE, BULLET_SIZE));
    image.setFillColor(c);
    setDirection(d);
}

bool Bullet::hittingPlatform(Platform p[]) {
    int bulletX = image.getPosition().x;
    int bulletY = image.getPosition().y;

    for(size_t i = 0; i < NUM_PLATFORMS; i++) {
        if((bulletX + image.getLocalBounds().width > p[i].left)&(bulletX < p[i].right)&(bulletY + image.getLocalBounds().height >  p[i].top)&(bulletY < p[i].bottom)) {
            return true;
        }
    }
        return false;
}

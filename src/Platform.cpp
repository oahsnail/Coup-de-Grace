#include "Platform.h"


Platform::Platform(float x, float y, sf::Sprite s) {
    image = s;
    image.setPosition(x,y);
    left = image.getPosition().x;
    right = image.getPosition().x + image.getLocalBounds().width;
    top = image.getPosition().y;
    bottom = image.getPosition().y + image.getLocalBounds().height;
}

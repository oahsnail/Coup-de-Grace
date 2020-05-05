#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include "Platform.h"

class Player {
public:
    float xVel;
    float yVel;
    float xPos;
    float yPos;
    float speed;
    enum Direction {UP, DOWN, LEFT, RIGHT};
    Direction dir;
    bool onGround;
    sf::Sprite sprite;

    //constructor
    Player(sf::Sprite s);
    void update(bool playerUp, bool playerDown, bool playerLeft, bool playerRight, Platform platform[]);
    void checkBoundaryCollision();
    void checkPlatformCollision(Platform p);
};

#endif // PLAYER_H

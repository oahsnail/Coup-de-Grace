#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include "Platform.h"


class Player {
public:
    float xVel;
    float yVel;
    float speed;
    enum Direction {UP, DOWN, LEFT, RIGHT};
    Direction dir;
    bool onGround;
    bool onPlatform;
    sf::Sprite sprite;
    float x;




    //constructor
    Player(sf::Sprite s);
    void update(bool playerUp, bool playerDown, bool playerLeft, bool playerRight, Platform platform[]);
    void checkBoundaryCollision(float dx, float dy);
    void checkPlatformCollision(float dx, float dy, Platform p);
    void checkFlagCollision();

};

#endif // PLAYER_H

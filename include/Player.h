#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include "Platform.h"
#include "Bullet.h"
#include <vector>


class Player {
public:
    float xVel;
    float yVel;
    float speed;
    Direction dir;
    bool onGround;
    bool onPlatform;
    sf::Sprite sprite;
    std::vector<Bullet> bullets;
    float x;
    bool isDead;




    //constructor
    Player(sf::Sprite s, Direction initDir);
    void update(bool playerUp, bool playerDown, bool playerLeft, bool playerRight, bool fireBullet, Platform platform[]);
    void checkBoundaryCollision(float dx, float dy);
    void checkPlatformCollision(float dx, float dy, Platform p);
    void checkBulletCollision(Bullet b);
    void checkFlagCollision();
    void shootBullet();

};

#endif // PLAYER_H

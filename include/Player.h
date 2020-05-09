#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include "Platform.h"
#include "Bullet.h"
#include <vector>


class Player {
public:

    Direction dir;

    sf::Sprite sprite;
    std::vector<Bullet> bullets;
    bool isDead;
    sf::Color bulletColor;



    //constructor
    Player(sf::Sprite s, Direction initDir, sf::Color c);
    void update(bool playerUp, bool playerDown, bool playerLeft, bool playerRight, bool fireBullet, Platform platform[]);
    void checkBoundaryCollision(float dx, float dy);
    void checkPlatformCollision(float dx, float dy, Platform p);
    void checkBulletCollision(Bullet b);
    void checkFlagCollision();
    void shootBullet();

    private:
    float xVel;
    float yVel;
    float speed;
    float x;
    bool onGround;
    bool onPlatform;
};

#endif // PLAYER_H

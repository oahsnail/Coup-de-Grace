#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>

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
    void update(bool playerUp, bool playerDown, bool playerLeft, bool playerRight);
    void checkCollision();
};

#endif // PLAYER_H

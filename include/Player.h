#ifndef PLAYER_H
#define PLAYER_H


class Player
{
public:
    float xvel;
    float yvel;
    float xpos;
    float ypos;
    float speed;
    enum Direction {UP, DOWN, LEFT, RIGHT};
    Direction dir;

    //constructor
    Player();
    void update(bool playerUp, bool playerDown, bool playerLeft, bool playerRight);
    void checkCollision();
};

#endif // PLAYER_H

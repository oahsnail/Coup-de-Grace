#include "Player.h"
#include "Constants.h"

using namespace std;

Player::Player() {
    xvel = 0;
    yvel = 0;
    xpos = 0;
    ypos = 0;
    speed = 10;
}
void Player::update(bool playerUp, bool playerDown, bool playerLeft, bool playerRight) {
    if(playerUp) {
        dir = UP;
        yvel = -speed;
    }
    if(playerDown) {
        dir = DOWN;
        yvel = speed;
    }
    if((playerUp & playerDown) | (!playerUp & !playerDown)) {
        yvel = 0;
    }
    if(playerLeft) {
        dir = LEFT;
        xvel = -speed;
    }
    if(playerRight) {
        dir = RIGHT;
        xvel = speed;
    }
    if((playerRight & playerLeft) | (!playerRight & !playerLeft)) {
        xvel = 0;
    }


    xpos += xvel;
    ypos += yvel;
    Player::checkCollision();

}
void Player::checkCollision() {
    if((xpos >= WINDOW_WIDTH) | (xpos <= 0)) {
        xpos -= xvel;
        xvel = 0;
    }
    if((ypos >= WINDOW_HEIGHT) | (ypos <= 0)) {
        ypos -= yvel;
        yvel = 0;
    }
}

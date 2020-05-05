#include <iostream>
#include "Player.h"
#include "Constants.h"


using namespace std;

Player::Player(sf::Sprite s) {
    xVel = 0;
    yVel = 0;
    speed = 10;
    onGround = false;
    sprite = s;

}
void Player::update(bool playerUp, bool playerDown, bool playerLeft, bool playerRight) {
    if(playerUp) {
        dir = UP;
        yVel = -speed;
    }
    if(playerDown) {
        dir = DOWN;
        yVel = speed;
    }
    if((playerUp & playerDown) | (!playerUp & !playerDown)) {
        yVel = 0;
    }
    if(playerLeft) {
        dir = LEFT;
        xVel = -speed;
    }
    if(playerRight) {
        dir = RIGHT;
        xVel = speed;
    }
    if((playerRight & playerLeft) | (!playerRight & !playerLeft)) {
        xVel = 0;
    }
    if(onGround) {
        yVel = 0;
        if(playerUp) {
            yVel = -speed;
        }
    }

    xPos += xVel;
    yPos += yVel;
    Player::checkCollision();



}
void Player::checkCollision() {
    if((xPos >= WINDOW_WIDTH-PLAYER_WIDTH) | (xPos <= 0)) {
        xPos -= xVel;
        xVel = 0;
    }
    if((yPos <= 0)) {
        yPos -= yVel;
        yVel = 0;
    }
    if(yPos >= GROUND_HEIGHT-PLAYER_HEIGHT) {
        onGround = true;
    } else if(yPos < GROUND_HEIGHT) {
        onGround = false;
    }
}

#include <iostream>
#include "Player.h"
#include "Constants.h"
#include <stdlib.h>


using namespace std;

Player::Player(sf::Sprite s) {
    xVel = 0;
    yVel = 0;
    speed = 10;
    onGround = false;
    sprite = s;

}
void Player::update(bool playerUp, bool playerDown, bool playerLeft, bool playerRight, Platform platform[]) {
    if(playerUp) {
//        dir = UP;
        yVel = -speed;
    }
    if(playerDown) {
//        dir = DOWN;
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
    Player::checkBoundaryCollision();
    for(int i = 0; i <= NUM_PLATFORMS; i++) {
        Player::checkPlatformCollision(platform[i]);
    }
}
void Player::checkBoundaryCollision() {
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
void Player::checkPlatformCollision(Platform p) {
    if((xPos + PLAYER_WIDTH >= p.left)&(xPos <= p.right)&(yPos + PLAYER_HEIGHT >=  p.top)&(yPos < p.bottom)) {
        if(yVel > 0 | yVel < 0) {
            yPos -= yVel;
            yVel = 0;
        }
        if(xVel > 0 | xVel < 0) {
            xPos -= xVel;
            xVel = 0;
        }

    }



}

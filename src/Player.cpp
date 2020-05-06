#include <iostream>
#include "Player.h"
#include "Constants.h"
#include <stdlib.h>
#include <cmath>


using namespace std;

Player::Player(sf::Sprite s) {
    xVel = 0;
    yVel = 0;
    speed = 10;
    onGround = false;
    onPlatform = false;
    sprite = s;
    float x = GRAVITY_ACCEL_INIT;

}
void Player::update(bool playerUp, bool playerDown, bool playerLeft, bool playerRight, Platform platform[]) {

    if(playerDown) {
//        dir = DOWN;
// !!! implement crouch or speedfall
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
    if(onGround | onPlatform) {
            x = GRAVITY_ACCEL_INIT;
//            yVel = speed;
        if(onGround) {
            yVel = 0;
        }
        if(playerUp) {
            yVel = -JUMP_HEIGHT;
        }
    } else {
        yVel += (GRAVITY_ACCEL+x);
        x+=GRAVITY_ACCEL;
    }

    onPlatform = false;

    sprite.move(sf::Vector2f(xVel, 0));
    for(int i = 0; i < NUM_PLATFORMS; i++) {
        Player::checkPlatformCollision(xVel, 0, platform[i]);
    }
    Player::checkBoundaryCollision(xVel, 0);

    sprite.move(sf::Vector2f(0, yVel));
    for(int i = 0; i < NUM_PLATFORMS; i++) {
        Player::checkPlatformCollision(0, yVel, platform[i]);
    }
    Player::checkBoundaryCollision(0, yVel);
//    cout <<onGround << onPlatform <<endl;
//    cout << yVel << endl;
cout <<x<<endl;
}
void Player::checkBoundaryCollision(float dx, float dy) {
    int playerX = sprite.getPosition().x;
    int playerY = sprite.getPosition().y;
    //right barrier
    if((playerX >= WINDOW_WIDTH-PLAYER_WIDTH) | (playerX <= 0)) {
        if(dx > 0) {
            sprite.setPosition(sf::Vector2f(WINDOW_WIDTH-PLAYER_WIDTH, playerY));
        }
        //left barrier
        if(dx < 0) {
            sprite.setPosition(sf::Vector2f(MARGIN, playerY));
        }
    }
    //top barrier
    if(playerY <= 0) {
        sprite.setPosition(sf::Vector2f(playerX, MARGIN));
    }
    if(playerY >= GROUND_HEIGHT-PLAYER_HEIGHT) {
        onGround = true;
        if(dy > 0) {
            sprite.setPosition(sf::Vector2f(playerX, GROUND_HEIGHT-PLAYER_HEIGHT));
        }
    } else if(playerY < GROUND_HEIGHT) {
        onGround = false;
    }
}
void Player::checkPlatformCollision(float dx, float dy, Platform p) {
    int playerX = sprite.getPosition().x;
    int playerY = sprite.getPosition().y;
    if((playerX + PLAYER_WIDTH > p.left)&(playerX < p.right)&(playerY + PLAYER_HEIGHT >  p.top)&(playerY < p.bottom)) {
        if(dy < 0) {
            sprite.setPosition(sf::Vector2f(playerX, p.bottom + MARGIN));
        }
        if(dy > 0) {
            sprite.setPosition(sf::Vector2f(playerX, p.top - PLAYER_HEIGHT));
            onPlatform = true;
        }
        if(dx > 0) {
            sprite.setPosition(sf::Vector2f(p.left - PLAYER_WIDTH - MARGIN, playerY));
        }
        if(dx < 0) {
            sprite.setPosition(sf::Vector2f(p.right + MARGIN, playerY));
        }

    }
}

void Player::checkFlagCollision() {
}

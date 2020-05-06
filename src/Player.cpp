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

    Player::checkBoundaryCollision();

    sprite.move(sf::Vector2f(xVel, 0));
    for(int i = 0; i < NUM_PLATFORMS; i++) {
        Player::checkPlatformCollision(xVel, 0, platform[i]);
    }
    sprite.move(sf::Vector2f(0, yVel));
    for(int i = 0; i < NUM_PLATFORMS; i++) {
        Player::checkPlatformCollision(0, yVel, platform[i]);
    }
}
void Player::checkBoundaryCollision() {
    int playerX = sprite.getPosition().x;
    int playerY = sprite.getPosition().y;
    //right barrier
    if((playerX >= WINDOW_WIDTH-PLAYER_WIDTH)) {
        sprite.setPosition(sf::Vector2f(WINDOW_WIDTH-PLAYER_WIDTH, playerY));
    }
    //left barrier
    if(playerX <= 0) {
        sprite.setPosition(sf::Vector2f(0, playerY));
    }
    //top barrier
    if(playerY <= 0) {
        sprite.setPosition(sf::Vector2f(playerX, 0));
    }
    if(playerY >= GROUND_HEIGHT-PLAYER_HEIGHT) {
        onGround = true;
    } else if(playerY < GROUND_HEIGHT) {
        onGround = false;
    }
}
void Player::checkPlatformCollision(float dx, float dy, Platform p) {
    int playerX = sprite.getPosition().x;
    int playerY = sprite.getPosition().y;
    if((playerX + PLAYER_WIDTH > p.left)&(playerX < p.right)&(playerY + PLAYER_HEIGHT >  p.top)&(playerY < p.bottom)) {
        if(dy < 0) {
            sprite.setPosition(sf::Vector2f(playerX, p.bottom + margin));
        }
        if(dy > 0) {
            sprite.setPosition(sf::Vector2f(playerX, p.top - PLAYER_HEIGHT - margin));
        }
        if(dx > 0) {
            sprite.setPosition(sf::Vector2f(p.left - PLAYER_WIDTH - margin, playerY));
        }
        if(dx < 0) {
            sprite.setPosition(sf::Vector2f(p.right + margin, playerY));
        }

    }



}

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <iomanip>
#include "Player.h"
#include "Platform.h"
#include "Constants.h"
#include "Timer.h"
#include <string>

using namespace std;


int startGame() {
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Coup de Grace");

    app.setFramerateLimit(45);

    bool p1up, p1down, p1left, p1right = false;
    bool p2up, p2down, p2left, p2right = false;
    bool p1fireBullet, p2fireBullet;
    bool gameStarted = false;
    bool gameEnded = false;
    bool firstEnterPress = true;
    int p1ShootTimer = 0;
    int p2ShootTimer = 0;

    // timer
    Timer timer;

    // fonts
    sf::Font agencyFont;
    agencyFont.loadFromFile("data/fonts/AGENCYB.TTF");

    // texts
    sf::Text timerText(to_string(TIME_ALLOWED), agencyFont, 50);
    sf::Text startText("Press Enter to Start", agencyFont, 50);
    sf::Text timesUpText("Time's Up!", agencyFont, 50);
    sf::Text declareP1WinnerText("Player 1 Wins!", agencyFont, 30);
    sf::Text declareP2WinnerText("Player 2 Wins!", agencyFont, 30);
    sf::Text restartText("Press Enter to Restart", agencyFont, 30);

    timerText.setPosition((WINDOW_WIDTH/2)-(timerText.getLocalBounds().width/2), 0);
    startText.setPosition((WINDOW_WIDTH/2)-(startText.getLocalBounds().width/2), (WINDOW_HEIGHT/2)-(startText.getLocalBounds().height));
    timesUpText.setPosition((WINDOW_WIDTH/2)-(timesUpText.getLocalBounds().width/2), (WINDOW_HEIGHT/2)-(timesUpText.getLocalBounds().height));
    restartText.setPosition((WINDOW_WIDTH/2)-(restartText.getLocalBounds().width/2), WINDOW_HEIGHT/2 + 50);
    declareP1WinnerText.setPosition((WINDOW_WIDTH/2)-(declareP1WinnerText.getLocalBounds().width/2), (WINDOW_HEIGHT/2)-(declareP1WinnerText.getLocalBounds().height));
    declareP2WinnerText.setPosition((WINDOW_WIDTH/2)-(declareP2WinnerText.getLocalBounds().width/2), (WINDOW_HEIGHT/2)-(declareP2WinnerText.getLocalBounds().height));

    // Load a sprite to display
    sf::Texture p1Texture;
    if (!p1Texture.loadFromFile("data/images/test.png"))
        return EXIT_FAILURE;
    sf::Sprite p1Sprite(p1Texture);

    sf::Texture p2Texture;
    if (!p2Texture.loadFromFile("data/images/test2.png"))
        return EXIT_FAILURE;
    sf::Sprite p2Sprite(p2Texture);

    sf::Texture platformLongTexture;
    if (!platformLongTexture.loadFromFile("data/images/platforms/Platform03.png"))
        return EXIT_FAILURE;
    sf::Sprite platformLongSprite(platformLongTexture);

    sf::Texture platformShortTexture;
    if (!platformShortTexture.loadFromFile("data/images/platforms/Platform01.png"))
        return EXIT_FAILURE;
    sf::Sprite platformShortSprite(platformShortTexture);

    sf::Texture platformDotTexture;
    if (!platformDotTexture.loadFromFile("data/images/platforms/Platform05.png"))
        return EXIT_FAILURE;
    sf::Sprite platformDotSprite(platformDotTexture);

    // shapes

    sf::RectangleShape ground(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT - GROUND_HEIGHT));
    sf::Color black(0, 0, 0);
    ground.setFillColor(black);
    ground.setPosition(0, GROUND_HEIGHT);



    // players
    Player p1(p1Sprite, RIGHT, sf::Color::White);
    Player p2(p2Sprite, LEFT, sf::Color::Black);

    // platforms
    Platform platformLong(WINDOW_WIDTH/2-(platformLongSprite.getLocalBounds().width/2), WINDOW_HEIGHT/2-(platformLongSprite.getLocalBounds().height/2), platformLongSprite);
    Platform platformShort0(100, 400, platformShortSprite);
    Platform platformDot(WINDOW_WIDTH/2-(platformDotSprite.getLocalBounds().width/2), GROUND_HEIGHT-platformDotSprite.getLocalBounds().height, platformDotSprite);
    Platform platformShort1(200, 300, platformShortSprite);
    Platform platformShort2(WINDOW_WIDTH-200-(platformShortSprite.getLocalBounds().width), 300, platformShortSprite);
    Platform platformShort3(WINDOW_WIDTH-100-(platformShortSprite.getLocalBounds().width), 400, platformShortSprite);


    Platform platformArr[NUM_PLATFORMS] = {platformShort0, platformShort1, platformShort2, platformShort3, platformLong, platformDot};

    // initialize positions;
    // p1 at bottom left, p2 at bottom right

    p1.sprite.setPosition(0, GROUND_HEIGHT-PLAYER_HEIGHT);
    p2.sprite.setPosition(WINDOW_WIDTH-PLAYER_WIDTH, GROUND_HEIGHT-PLAYER_HEIGHT);


    // Start the game loop
    while (app.isOpen()) {
        // Process events
        sf::Event event;
        while (app.pollEvent(event)) {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
        }

        // Clear screen
        sf::Color darkRed(179, 59, 68);
        app.clear(darkRed);

        //draw background and platforms
        app.draw(ground);
        for(Platform p : platformArr) {
            app.draw(p.image);

        }

        //game start
        if(gameStarted) {
            // Countdown timer
            timer.start();
            if(gameEnded) {
                timer.pause();
                timer.pause();
            }
            float countdown = TIME_ALLOWED - timer.getElapsedSeconds();
            string time = to_string(countdown).substr(0,4);
            timerText.setString(time);

            if(countdown < 0) {
                gameEnded = true;
                app.draw(timesUpText);
                timerText.setString("0.00");
            }
        } else {
            app.draw(startText);
        }


        if(p1.isDead | p2.isDead) {
            gameEnded = true;
            if(p1.isDead) {
                app.draw(declareP2WinnerText);
            }
            if(p2.isDead) {
                app.draw(declareP1WinnerText);
            }

        }

        if(gameEnded) {
            app.draw(restartText);

        }



        // Draw stuff
        // player turning in direction
        if(p1.dir == 2) {
            p1.sprite.setTextureRect(sf::IntRect(PLAYER_WIDTH, 0, -PLAYER_WIDTH, PLAYER_HEIGHT));
        }
        if(p1.dir == 3) {
            p1.sprite.setTextureRect(sf::IntRect(0, 0, PLAYER_WIDTH, PLAYER_HEIGHT));
        }
        if(p2.dir == 2) {
            p2.sprite.setTextureRect(sf::IntRect(0, 0, PLAYER_WIDTH, PLAYER_HEIGHT));
        }
        if(p2.dir == 3) {
            p2.sprite.setTextureRect(sf::IntRect(PLAYER_WIDTH, 0, -PLAYER_WIDTH, PLAYER_HEIGHT));
        }

        app.draw(p1.sprite);
        app.draw(p2.sprite);
        app.draw(timerText);


        for(Bullet b : p2.bullets) {
            app.draw(b.image);
        }

        for(Bullet b : p1.bullets) {
            app.draw(b.image);
        }


        // general controls

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Keyboard::Enter)) {
            gameStarted = true;
            if(firstEnterPress) {
                timer.reset();
            }
            if(gameEnded) {
                return 1;
            }
            firstEnterPress = false;
        }




        // player 1 controls
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Keyboard::W)) {
            p1up = true;
        } else {
            p1up = false;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Keyboard::S)) {
            p1down = true;
        } else {
            p1down = false;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Keyboard::D)) {
            p1right = true;
        } else {
            p1right = false;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Keyboard::A)) {
            p1left = true;
        } else {
            p1left = false;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Keyboard::C) & (p1ShootTimer >= SHOOT_TIMER)) {
            p1fireBullet = true;
            p1ShootTimer = 0;
        } else {
            p1fireBullet = false;
        }

        //player 2 controls
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Keyboard::O)) {
            p2up = true;
        } else {
            p2up = false;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Keyboard::L)) {
            p2down = true;
        } else {
            p2down = false;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Keyboard::Semicolon)) {
            p2right = true;
        } else {
            p2right = false;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Keyboard::K)) {
            p2left = true;
        } else {
            p2left = false;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Keyboard::BackSlash) & (p2ShootTimer >= SHOOT_TIMER)) {
            p2fireBullet = true;
            p2ShootTimer = 0;
        } else {
            p2fireBullet = false;
        }

        //game running
        if(gameStarted & !gameEnded) {
            p1.update(p1up, p1down, p1left, p1right, p1fireBullet, platformArr);
            p2.update(p2up, p2down, p2left, p2right, p2fireBullet, platformArr);

            for(size_t i = 0; i < p1.bullets.size(); i++) {
                if(p1.bullets[i].bulletDir == 3) {
                    p1.bullets[i].image.move(BULLET_SPEED, 0);
                }
                if(p1.bullets[i].bulletDir == 2) {
                    p1.bullets[i].image.move(-BULLET_SPEED, 0);
                }
                if((p1.bullets[i].image.getPosition().x > WINDOW_WIDTH) |(p1.bullets[i].image.getPosition().x < 0)|(p1.bullets[i].hittingPlatform(platformArr))) {
                    p1.bullets.erase(p1.bullets.begin() + i );
                }
                p2.checkBulletCollision(p1.bullets[i]);
            }
            for(size_t i = 0; i < p2.bullets.size(); i++) {
                if(p2.bullets[i].bulletDir == 3) {
                    p2.bullets[i].image.move(BULLET_SPEED, 0);
                }
                if(p2.bullets[i].bulletDir == 2) {
                    p2.bullets[i].image.move(-BULLET_SPEED, 0);
                }
                if((p2.bullets[i].image.getPosition().x > WINDOW_WIDTH) |(p2.bullets[i].image.getPosition().x < 0)|(p2.bullets[i].hittingPlatform(platformArr))) {
                    p2.bullets.erase(p2.bullets.begin() + i );
                }
                p1.checkBulletCollision(p2.bullets[i]);
            }
            p1ShootTimer++;
            p2ShootTimer++;
        }


        // Update the window
        app.display();

    }

    return EXIT_SUCCESS;
}

int main() {
    if(!startGame()) {
        return 0;
    } else {
        return main();
    }


    return 0;
}

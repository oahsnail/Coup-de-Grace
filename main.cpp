#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <iomanip>
#include "Player.h"
#include "Platform.h"
#include "Constants.h"
#include "Timer.h"

using namespace std;


int main() {
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Coup de Grace");

    app.setFramerateLimit(45);

    bool p1up, p1down, p1left, p1right = false;
    bool p2up, p2down, p2left, p2right = false;
    bool gameStarted = false;
    bool gameEnded = false;
    bool firstEnterPress = true;

    // timer
    Timer timer;

    // fonts
    sf::Font agencyFont;
    agencyFont.loadFromFile("data/fonts/AGENCYB.TTF");

    // texts
    sf::Text timerText("timer", agencyFont, 50);
    sf::Text startText("Press Enter to Start", agencyFont, 50);
    sf::Text timesUpText("Time's Up!", agencyFont, 50);
    sf::Text declareWinnerText("", agencyFont, 30);
    startText.setPosition((WINDOW_WIDTH/2)-(startText.getLocalBounds().width/2), (WINDOW_HEIGHT/2)-(startText.getLocalBounds().height));
    timesUpText.setPosition((WINDOW_WIDTH/2)-(timesUpText.getLocalBounds().width/2), (WINDOW_HEIGHT/2)-(timesUpText.getLocalBounds().height));

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
    Player p1(p1Sprite);
    Player p2(p2Sprite);

    // platforms
    Platform platformLong(WINDOW_WIDTH/2-(platformLongSprite.getLocalBounds().width/2), WINDOW_HEIGHT/2-(platformLongSprite.getLocalBounds().height/2), platformLongSprite);
    Platform platformShort(100, 400, platformShortSprite);
    Platform platformDot(WINDOW_WIDTH-200, 200, platformDotSprite);
    Platform platformShort2(200, 300, platformShortSprite);

    Platform platformArr[NUM_PLATFORMS] = {platformShort2, platformLong, platformShort};

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
//        app.draw(platformLong.image);
        for(Platform p : platformArr) {
            app.draw(p.image);

        }


        if(gameStarted) {

            // !!!Countdown timer
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
        }

        // Draw stuff
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
        if(!gameStarted) {
            app.draw(startText);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Keyboard::Enter)) {
            gameStarted = true;
            if(firstEnterPress) {
                timer.reset();
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

        if(gameStarted & !gameEnded) {
            p1.update(p1up, p1down, p1left, p1right, platformArr);
            p2.update(p2up, p2down, p2left, p2right, platformArr);
        } else {
            p2.update(false, false, false, false, platformArr);
            p1.update(false, false, false, false, platformArr);
        }

        // Update the window
        app.display();

    }

    return EXIT_SUCCESS;
}

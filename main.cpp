#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "Player.h"
#include "Constants.h"

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
    sf::Clock clock;


    Player p1;
    Player p2;

    sf::Font agencyFont;
    agencyFont.loadFromFile("data/fonts/AGENCYB.TTF");

    // texts
    sf::Text timerText("timer", agencyFont, 50);
    sf::Text startText("Press Enter to Start", agencyFont, 50);
    sf::Text timesUpText("Time's Up!", agencyFont, 50);
    sf::Text declareWinnerText("", agencyFont, 30);
    startText.setPosition(WINDOW_WIDTH/3, WINDOW_HEIGHT/2);

    // initialize positions;
    // p1 at bottom left, p2 at bottom right
    p1.xpos = 0;
    p1.ypos = GROUND_HEIGHT;
    p2.xpos = WINDOW_WIDTH-50;
    p2.ypos = GROUND_HEIGHT;

    // Load a sprite to display
    sf::Texture p1Texture;
    if (!p1Texture.loadFromFile("data/images/test.png"))
        return EXIT_FAILURE;
    sf::Sprite p1Sprite(p1Texture);

    sf::Texture p2Texture;
    if (!p2Texture.loadFromFile("data/images/test2.png"))
        return EXIT_FAILURE;
    sf::Sprite p2Sprite(p2Texture);

    p1Sprite.setPosition(p1.xpos, p1.ypos);
    p2Sprite.setPosition(p2.xpos, p2.ypos);

    // Start the game loop
    while (app.isOpen()) {
        // Process events
        sf::Event event;
        while (app.pollEvent(event)) {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
        }

        if(gameStarted) {

        // !!!Countdown timer
            sf::Time t = clock.getElapsedTime();
            string time = to_string(TIME_ALLOWED - t.asSeconds());
            timerText.setString(time);
            if(t.asSeconds() < 0) {
                gameEnded = true;
            }
        }
        if(gameEnded) {

        }




        // Clear screen
        app.clear();

        // Draw the sprite
        app.draw(p1Sprite);
        app.draw(p2Sprite);
        app.draw(timerText);
        if(!gameStarted) {
            app.draw(startText);
        }

        p1Sprite.move(sf::Vector2f(p1.xvel, p1.yvel));
        p2Sprite.move(sf::Vector2f(p2.xvel, p2.yvel));

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Keyboard::Enter)) {
            gameStarted = true;
            if(firstEnterPress) {
                clock.restart();
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
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Keyboard::Up)) {
            p2up = true;
        } else {
            p2up = false;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Keyboard::Down)) {
            p2down = true;
        } else {
            p2down = false;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Keyboard::Right)) {
            p2right = true;
        } else {
            p2right = false;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Keyboard::Left)) {
            p2left = true;
        } else {
            p2left = false;
        }

        if(gameStarted) {
            p1.update(p1up, p1down, p1left, p1right);
            p2.update(p2up, p2down, p2left, p2right);
        }


        // Update the window
        app.display();

    }

    return EXIT_SUCCESS;
}

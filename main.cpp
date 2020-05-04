#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"
#include "Constants.h"

using namespace std;


int main() {
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML window");
    app.setFramerateLimit(45);

    bool p1up, p1down, p1left, p1right = false;
    bool p2up, p2down, p2left, p2right = false;

    Player p1;
    Player p2;

    sf::Font agencyFont;
    agencyFont.loadFromFile("data/fonts/AGENCYB.TTF");

    sf::Text timerText("timer", agencyFont, 50);

    // initialize positions;
    // p1 at bottom left, p2 at bottom right
//    p1.xpos = 0;
//    p1.ypos = windowHeight;
//    p2.xpos = windowWidth;
//    p2.ypos = windowHeight;

    // Load a sprite to display
    sf::Texture p1Texture;
    if (!p1Texture.loadFromFile("data/images/test.png"))
        return EXIT_FAILURE;
    sf::Sprite p1Sprite(p1Texture);

    sf::Texture p2Texture;
    if (!p2Texture.loadFromFile("data/images/test2.png"))
        return EXIT_FAILURE;
    sf::Sprite p2Sprite(p2Texture);

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
        app.clear();

        // Draw the sprite
        app.draw(p1Sprite);
        app.draw(p2Sprite);
        app.draw(timerText);

        p1Sprite.move(sf::Vector2f(p1.xvel, p1.yvel));
        p2Sprite.move(sf::Vector2f(p2.xvel, p2.yvel));


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

        p1.update(p1up, p1down, p1left, p1right);


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

        p2.update(p2up, p2down, p2left, p2right);



        // Update the window
        app.display();

        cout << p1.ypos << endl;

    }

    return EXIT_SUCCESS;
}

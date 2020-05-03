#include <SFML/Graphics.hpp>
#include <iostream>


int windowWidth = 1000;
int windowHeight = 600;



using namespace std;

class Player {
public:
    float xvel;
    float yvel;
    float xpos;
    float ypos;
    float speed = 10;
    enum Direction {UP, DOWN, LEFT, RIGHT};
    Direction dir;
    Player() {
        xvel = 0;
        yvel = 0;
    }
    void update(bool playerUp, bool playerDown, bool playerLeft, bool playerRight) {
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
    }
    void collide(){
        if(xpos > windowWidth) {
            xvel = 0;
        }
    }
};

int main() {
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(windowWidth, windowHeight), "SFML window");
    app.setFramerateLimit(30);

    bool p1up, p1down, p1left, p1right = false;
    bool p2up, p2down, p2left, p2right = false;

    Player p1;
    Player p2;

    sf::Font agencyFont;
    agencyFont.loadFromFile("data/fonts/AGENCYB.TTF");

    sf::Text timerText("timer", agencyFont, 50);

    // initialize positions;
    // p1 at bottom left, p2 at bottom right
    p1.xpos = 0;
    p1.ypos = windowHeight;
    p2.xpos = windowWidth;
    p2.ypos = windowHeight;

    // Load a sprite to display
    sf::Texture testTexture;
    if (!testTexture.loadFromFile("data/images/test.png"))
        return EXIT_FAILURE;
    sf::Sprite p1Sprite(testTexture);

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
        app.draw(timerText);

        p1Sprite.move(sf::Vector2f(p1.xvel, p1.yvel));


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

        cout << p1.xvel << p1.yvel << endl;

    }

    return EXIT_SUCCESS;
}

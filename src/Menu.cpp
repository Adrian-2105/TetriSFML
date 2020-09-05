#include "../include/Menu.h"

// Window dimensions
#define widthWindow     575
#define heightWindow    600

#define numDisplacement 14

char runMainMenu(RenderWindow* window, Sprite* logo, Text* text) {
    bool menu = true;
    Event event;

    // Creating the image of the main menu
    window->clear(Color(10, 10, 50)); //  background
    logo->setPosition(widthWindow / 2 - 100, heightWindow / 2 - 225);
    window->draw(*logo);

    text->setString("            Press [ENTER] to start\n\n"
                    "        Press [ESC] to exit the game\n\n\n"
                    "Use the arrows to move, [ESC] to pause");
    text->setPosition(widthWindow / 2 - 270, heightWindow / 2);
    window->draw(*text);

    // Display it on screen
    window->display();

    // Main loop waiting for response
    while (menu && window->isOpen()) {
        // Event handling
        while (window->pollEvent(event)) {
            // Window closed
            if (event.type == Event::Closed) {
                window->close();
                return WindowClosed;
            }
                // Key pressed
            else if (event.type == Event::KeyPressed) {
                // Start game
                if (event.key.code == Keyboard::Enter)
                    menu = false;
                    // Quit
                else if (event.key.code == Keyboard::Escape) {
                    window->close();
                    return ExitGame;
                }
            }
        }
    }

    return Continue;
}


char runPauseMenu(RenderWindow* window, Text* text) {
    bool menu = true;
    Event event;

    // Creating the image of the main menu
    window->clear(Color::Black); //  background

    text->setString("Press [ENTER] to continue");
    text->setPosition(widthWindow / 2 - 180, heightWindow / 2 - 25);
    window->draw(*text);

    // Display it on screen
    window->display();

    // Main loop waiting for response
    while (menu && window->isOpen()) {
        // Event handling
        while (window->pollEvent(event)) {
            // Window closed
            if (event.type == Event::Closed) {
                window->close();
                return WindowClosed;
            }
            // Key pressed
            else if (event.type == Event::KeyPressed) {
                // Resume game
                if (event.key.code == Keyboard::Enter)
                    menu = false;
            }
        }
    }
    return Continue;
}

char runGameOverMenu(RenderWindow* window, Text* text, long long score) {
    bool menu = true;
    Event event;

    // Creating the image of the main menu
    window->clear(Color::Black); //  background

    text->setString("          Game Over!\n\n"
                    "          Your score:"
                    "\n\n\n\n\nPress [ENTER] to continue");
    text->setPosition(widthWindow / 2 - 175, heightWindow / 2 - 150);
    window->draw(*text);

    // Calculating the X axis of the score
    int x = widthWindow / 2 - 9;
    for (int i = 10; score / i > 0; i *= 10)
        x -= numDisplacement;
    text->setPosition(x, heightWindow / 2 - 10);
    text->setString(std::to_string(score));
    window->draw(*text);

    // Display it on screen
    window->display();

    // Main loop waiting for response
    while (menu && window->isOpen()) {
        // Event handling
        while (window->pollEvent(event)) {
            // Window closed
            if (event.type == Event::Closed) {
                window->close();
                return WindowClosed;
            }
            // Key pressed
            else if (event.type == Event::KeyPressed) {
                // Start game
                if (event.key.code == Keyboard::Enter)
                    menu = false;
            }
        }
    }

    return Continue;
}
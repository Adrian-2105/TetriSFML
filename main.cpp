#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "include/Menu.h"
#include "include/Game.h"

using namespace sf;
using namespace std;

// Debugger macros
//#define FPS

// FPS control
#define MAX_FPS 24

// Board dimensions
#define widthBoard      10
#define heightBoard     20

// Window dimensions
#define widthWindow     575
#define heightWindow    600

// Colors
#define DarkRed     80, 10, 10
#define DarkBlue    10, 10, 50

int main() {
    // Creating the window
    RenderWindow window(VideoMode(widthWindow, heightWindow), "TETRIS-C++&SFML");
    window.setFramerateLimit(MAX_FPS);
    // Creating the game configuration
    Game game(&window, widthBoard, heightBoard);

    // Main logo
    Texture logo_t;
    logo_t.loadFromFile("./resources/images/logo.png");
    Sprite logo;
    logo.setTexture(logo_t);

    // Main theme song
    SoundBuffer mainTheme_b;
    mainTheme_b.loadFromFile("./resources/audio/maintheme.wav");
    Sound mainTheme;
    mainTheme.setBuffer(mainTheme_b);
    mainTheme.setLoop(true);

    // Text
    Font font;
    font.loadFromFile("./resources/fonts/Pixellari.ttf");
    Text text;
    text.setFont(font);
    text.setCharacterSize(30);

    // Easter egg hehe
    Texture t;
    t.loadFromFile("./resources/images/sans.png");
    Sprite sans;
    sans.setTexture(t);
    sans.setPosition(387, 189);
    SoundBuffer megalovania_b;
    megalovania_b.loadFromFile("./resources/audio/megalovania.ogg");
    Sound megalovania;
    megalovania.setBuffer(megalovania_b);
    megalovania.setLoop(true);

    // Timer for falling of the piece
    Clock timer;
    float delay = game.getDelay();

    // FPS debugging
#ifdef FPS
    Clock timerFPS;
    int contFPS = 0, fps = 0;
#endif

    // Variable used to control the events that can happen in the game
    Event event{};
    // Main window loop
    while (window.isOpen()) {
        // Run the main menu and check if the windows has been closed or the player have exit the game
        switch (runMainMenu(&window, &logo, &text)) {
            case WindowClosed:
            case ExitGame:
                return 0;
        }

        // Flag for game over
        bool gameOver = false;
        bool easteregg = false;

        logo.setPosition(350, 207);

        // Start the background music
        mainTheme.play();

        // Main game loop
        while (!gameOver && window.isOpen()) {
            // Check if the timer has exceeded the delay time
            if (timer.getElapsedTime().asSeconds() > delay) {
                timer.restart();
                // Then move the piece down
                if (!game.movePieceDown()) {
                    // If it cannot be moved we generate a new piece
                    game.generateNewPiece();
                    // Update the delay
                    delay = game.getDelay();
                    // And check if the game is over
                    gameOver = game.isOver();
                }
            }

            // Event handling
            while (window.pollEvent(event)) {
                // Window closed
                if (event.type == Event::Closed) {
                    window.close();
                    return 0;
                }
                // Key pressed
                else if (event.type == Event::KeyPressed) {
                    if (event.key.code == Keyboard::Up)
                        game.rotatePiece();
                    else if (event.key.code == Keyboard::Left)
                        game.movePieceLeft();
                    else if (event.key.code == Keyboard::Right)
                        game.movePieceRight();
                    else if (event.key.code == Keyboard::Down)
                        game.movePieceDown();
                    else if (event.key.code == Keyboard::M && !easteregg) {
                        easteregg = true;
                        mainTheme.stop();
                        megalovania.play();
                    }
                    else if (event.key.code == Keyboard::Escape) {
                        // Pause music
                        if (easteregg)
                            megalovania.pause();
                        else
                            mainTheme.pause();
                        // Run pause menu and check the current status
                        switch (runPauseMenu(&window, &text)) {
                            case WindowClosed:
                                return 0;
                            case ExitGame:
                                gameOver = true;
                        }
                        // Resume music
                        if (easteregg)
                            megalovania.play();
                        else
                            mainTheme.play();
                    }
                }
            }

            // Finally, draw the current frame
            if (easteregg) {
                window.clear(Color(DarkRed));
                window.draw(sans);
            }
            else {
                window.clear(Color(DarkBlue));
                window.draw(logo);
            }

            // FPS debugging
#ifdef FPS
            if (timerFPS.getElapsedTime().asSeconds() > 1) {
                timerFPS.restart();
                fps = contFPS;
                contFPS = 0;
            }
            contFPS++;

            text.setString("FPS: " + to_string(fps));
            text.setPosition(0,0);
            window.draw(text);
#endif

            game.draw();
        }

        /* End of the game */
        mainTheme.stop();
        megalovania.stop();
        // Run the end game menu and check if the windows has been closed (end of the game)
        switch (runGameOverMenu(&window, &text, game.getScore())) {
            case WindowClosed:
                return 0;
        }

        game.restart();
    }

    return 0;
}
/**
 * Main class of the game.
 * It contains the board and the current piece and allows to do
 * the basic operations in the game. It also contains the needed
 * sprites of the GUI.
 */

#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Board.h"

using namespace sf;

/* Type of colors:
 * BLUE, DARKBLUE, RED, YELLOW, ORANGE, GREEN, PURPLE
 *
 * The order depends on the order of the colors in the sprite
 */
#define NUM_COLORS 7

// Score per type of action
#define SCORE_PER_MOVE_DOWN 1
#define SCORE_PER_LINE 100
#define incrementMultiplier 0.2

// Delay
#define initialDelay 1.0
#define delayDecrement 0.1
#define minimumDelay 0.1
#define initialDelayScore 400
#define incrementDelayScore 100

class Game {

private:
    // Properties
    RenderWindow* window;
    Board* board;
    Piece* currentPiece;
    Piece* nextPiece;
    long long score;
    int lines;

    // Sprites used in the game
    Texture* blocks_t;
    Texture* background_t;
    Sprite** blocks;
    Sprite* background;

    // Font and text used to print the score and the numLines
    Font* font;
    Text* text;

    // Audio
    SoundBuffer* lineSound_s;
    Sound* lineSound;

    // Methods to add to the actual window some elements
    void addNextPieceToDrawing();
    void addScoreToDrawing();
    void addNumLinesToDrawing();

    // Replace the next piece with the current one and generate the next piece
    Piece* createNewPiece();

    // Removes the current piece, freeing up memory
    void deleteCurrentPiece();

public:
    // Constructor and destroyer
    Game(RenderWindow* _window, int width, int height);
    ~Game();

    // Getters
    long long getScore() const;
    float getDelay();

    // Basic and classic moves of the pieces
    bool movePieceLeft();
    bool movePieceRight();
    bool movePieceDown();
    bool rotatePiece();

    // Generate a new piece, replacing the previous.
    void generateNewPiece();

    // Check if the game have finished
    bool isOver();

    // Reset the board and the rest of things to start a new game with the same settings
    void restart();

    // Draw the actual board with the current piece in the window
    void draw();
};


#endif //TETRIS_GAME_H

#include "../include/Game.h"
#include <random>

// The XY start coordinate of the board in my background is (50, 50)
#define margin 50

// Margin for next piece
#define nextPieceMarginX 400
#define nextPieceMarginY 75

// Margin for score and lines print
#define scoreMarginX 490
#define scoreMarginY 427
#define scorePosterMarginX 393
#define scorePosterMarginY 395
#define linesMarginX 490
#define linesMarginY 500
#define linesPosterMarginX 400
#define linesPosterMarginY 465

// Text configuration
#define charSize 36
#define numSize 40
#define numDisplacement 22

/* Constructors and destroyers */

Game::Game(RenderWindow* _window, int width, int height) {
    // Time Seed Initialization
    srand(time(nullptr));

    // Initialization of the principal properties
    window = _window;
    score = 0;
    lines = 0;
    board = new Board(width, height);
    currentPiece = createNewPiece();
    nextPiece = createNewPiece();

    // Initialization of the blocks texture and sprite
    blocks_t = new Texture;
    blocks_t->loadFromFile("./resources/images/blocks.png");
    blocks = new Sprite*[NUM_COLORS];
    for (int i = 0; i < NUM_COLORS; i++) {
        blocks[i] = new Sprite(*blocks_t);
        blocks[i]->setTextureRect(IntRect(i * 25, 0, 25, 25));
    }

    // Initialization of the background texture and sprite
    background_t = new Texture;
    background_t->loadFromFile("./resources/images/background.png");
    background = new Sprite(*background_t);

    // Initialization of the font and text used
    font = new Font;
    font->loadFromFile("./resources/fonts/Pixellari.ttf");
    text = new Text;
    text->setFont(*font);
    text->setCharacterSize(numSize);
    text->setFillColor(Color::White);

    // Initialization of the sounds effects
    lineSound_s = new SoundBuffer;
    lineSound_s->loadFromFile("./resources/audio/linecomplete.wav");
    lineSound = new Sound;
    lineSound->setBuffer(*lineSound_s);
}

Game::~Game() {
    delete board;
    delete currentPiece;
    delete nextPiece;
    delete blocks_t;
    for (int i = 0; i < NUM_COLORS; i++)
        delete blocks[i];
    delete[] blocks;
    delete background_t;
    delete background;
    delete lineSound;
    delete lineSound_s;
}

/* Getters */

long long Game::getScore() const {
    return score;
}

float Game::getDelay() {
    float delay = initialDelay;
    for (int i = initialDelayScore; i < score && delay > minimumDelay; i += i + incrementDelayScore)
        delay -= delayDecrement;
    return delay;
}

/* Movement of the pieces
 *
 * All the methods related with the movement of the pieces
 * checks at first if the actual position allows to make a move.
 * If it pass it, then we do a "virtual move" (change the XY coordinates
 * or the direction). Later, we check if it's a legal movement
 * with board->isCollision(). If it isn't, we revert that.
 */

bool Game::movePieceLeft() {
    currentPiece->moveLeft();
    if (board->isCollision(currentPiece)) {
        currentPiece->moveRight();
        return false;
    }
    return true;
}

bool Game::movePieceRight() {
    currentPiece->moveRight();
    if (board->isCollision(currentPiece)) {
        currentPiece->moveLeft();
        return false;
    }
    return true;
}

bool Game::movePieceDown() {
    currentPiece->moveDown();
    if (board->isCollision(currentPiece)) {
        currentPiece->moveUp();
        return false;
    }
    score += SCORE_PER_MOVE_DOWN;
    return true;
}

bool Game::rotatePiece() {
    currentPiece->rotateLeft();
    if (board->isCollision(currentPiece)) {
        currentPiece->rotateRight();
        return false;
    }
    return true;
}

/* Generation and destruction of pieces */

Piece* Game::createNewPiece() {
    return new Piece(rand() % NUM_PIECES, board->width / 2 - 1, 0);
}

void Game::deleteCurrentPiece() {
    delete currentPiece;
}

void Game::generateNewPiece() {
    // Add to the board the piece in his current position
    board->addPiece(currentPiece);

    // Remove lines and add score
    int deletedLines = board->deleteCompleteLines();
    lines += deletedLines;
    float multiplier = 1;
    for (int i = 1; i < deletedLines; i++)
        multiplier += incrementMultiplier;
    score += deletedLines * SCORE_PER_LINE * multiplier;
    // Sound effect
    if (deletedLines)
        lineSound->play();

    // Update the current piece
    deleteCurrentPiece();
    currentPiece = nextPiece;
    nextPiece = createNewPiece();
}

/* Game manipulation */

bool Game::isOver() {
    return board->isCollision(currentPiece);
}

void Game::restart() {
    board->clear();
    deleteCurrentPiece();
    createNewPiece();
    score = 0;
    lines = 0;
}

/* SFML functions */

void Game::draw() {
    // At first, we draw the background
    window->draw(*background);

    // Later, print the board with his current piece
    board->draw(window, blocks, currentPiece, margin, margin);

    // We draw to the next piece
    addNextPieceToDrawing();

    // We add to the score and line counter (with his respective posters)
    addScoreToDrawing();
    addNumLinesToDrawing();

    // And finally, we show it on the window
    window->display();
}

void Game::addNextPieceToDrawing() {
    int h = nextPiece->height, w = nextPiece->width;
    char type = nextPiece->type;
    bool** M = nextPiece->M;

    // Calculus of the margin X and Y
    int x = nextPieceMarginX;
    if (type == O)
        x += boxSize;
    else if (type != I)
        x += boxSize / 2;

    int y = nextPieceMarginY;
    if (type == I)
        y += boxSize / 2;

    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++) {
            if (M[i][j]) {
                blocks[type]->setPosition(x + j * boxSize, y + i * boxSize);
                window->draw(*blocks[type]);
            }
        }
}

void Game::addScoreToDrawing() {
    // Poster construction
    text->setCharacterSize(charSize);
    text->setString("SCORE");
    text->setPosition(scorePosterMarginX, scorePosterMarginY);
    window->draw(*text);

    // Score Num construction
    text->setCharacterSize(numSize);
    int x = scoreMarginX;
    for (int i = 10; score / i > 0; i *= 10)
        x -= numDisplacement;
    text->setString(std::to_string(score));
    text->setPosition(x, scoreMarginY);
    window->draw(*text);
}

void Game::addNumLinesToDrawing() {
    // Poster construction
    text->setCharacterSize(charSize);
    text->setString("LINES");
    text->setPosition(linesPosterMarginX, linesPosterMarginY);
    window->draw(*text);

    // Lines Num construction
    text->setCharacterSize(numSize);
    int x = linesMarginX;
    for (int i = 10; lines / i > 0; i *= 10)
        x -= numDisplacement;
    text->setString(std::to_string(lines));
    text->setPosition(x, linesMarginY);
    window->draw(*text);
}



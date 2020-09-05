#include "../include/Board.h"

// Empty box value
#define empty -1

/* Constructor and destroyer */

Board::Board(int w, int h) {
    this->width = w;
    this->height = h;

    // Reserve memory for tables
    table = new char*[h];
    printableTable = new char*[h];
    for (int i = 0; i < h; i++) {
        table[i] = new char[w];
        printableTable[i] = new char[w];
    }
    // Initialize the table
    this->clear();
}

Board::~Board() {
    for (int i = 0; i < height; i++) {
        delete table[i];
        delete printableTable[i];
    }
    delete[] table;
    delete[] printableTable;
}

/* Table control */

bool Board::isCollision(Piece* piece) {
    int x = piece->x, y = piece->y, w = piece->getWidth(), h = piece->getHeight();
    bool** M = piece->M;
    switch (piece->direction) {
        case UP:
            for (int i = 0; i < h; i++)
                for (int j = 0; j < w; j++) {
                    int Y = y + i, X = x + j;
                    if ((Y < 0 || Y >= height || X < 0 || X >= width) || (M[i][j] && table[Y][X] != empty))
                        return true;
                }
            break;
        case RIGHT:
            for (int i = 0; i < w; i++)
                for (int j = 0; j < h; j++) {
                    int Y = y + (h - j - 1), X = x + i;
                    if ((Y < 0 || Y >= height || X < 0 || X >= width) || (M[i][j] && table[Y][X] != empty))
                        return true;
                }
            break;
        case DOWN:
            for (int i = 0; i < h; i++)
                for (int j = 0; j < w; j++) {
                    int Y = y + (h - i - 1), X = x + (w - j - 1);
                    if ((Y < 0 || Y >= height || X < 0 || X >= width) || (M[i][j] && table[Y][X] != empty))
                        return true;
                }
            break;
        case LEFT:
            for (int i = 0; i < w; i++)
                for (int j = 0; j < h; j++) {
                    int Y = y + j, X = x + (w - i - 1);
                    if ((Y < 0 || Y >= height || X < 0 || X >= width) || (M[i][j] && table[Y][X] != empty))
                        return true;
                }
            break;
    }
    return false;
}

/* Table manipulation */

void Board::addPiece(char** _table, Piece* piece) const {
    int x = piece->x, y = piece->y, h = piece->getHeight(), w = piece->getWidth();
    char type = piece->type;
    bool** M = piece->M;

    /* It isn't checked if the box is occupied. We assume they aren't.
     * Check Game::isCollision() method
     * The key to understanding it is with a drawing, seeing how the boxes
     * are associated when rotating the matrix.
     */
    switch (piece->direction) {
        case UP:
            for (int i = 0; i < h; i++)
                for (int j = 0; j < w; j++) {
                    int Y = y + i, X = x + j;
                    if ((Y < 0 || Y >= height || X < 0 || X >= width) || M[i][j])
                        _table[Y][X] = type;
                }
            break;
        case RIGHT:
            for (int i = 0; i < w; i++)
                for (int j = 0; j < h; j++) {
                    int Y = y + (h - j - 1), X = x + i;
                    if ((Y < 0 || Y >= height || X < 0 || X >= width) || M[i][j])
                        _table[Y][X] = type;
                }
            break;
        case DOWN:
            for (int i = 0; i < h; i++)
                for (int j = 0; j < w; j++) {
                    int Y = y + (h - i - 1), X = x + (w - j - 1);
                    if ((Y < 0 || Y >= height || X < 0 || X >= width) || M[i][j])
                        _table[Y][X] = type;
                }
            break;
        case LEFT:
            for (int i = 0; i < w; i++)
                for (int j = 0; j < h; j++) {
                    int Y = y + j, X = x + (w - i - 1);
                    if ((Y < 0 || Y >= height || X < 0 || X >= width) || M[i][j])
                        _table[Y][X] = type;
                }
            break;
    }
}

void Board::addPiece(Piece *piece) {
    Board::addPiece(table, piece);
}

void Board::clear() {
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            table[i][j] = empty;
}

int Board::deleteCompleteLines() {
    int cont = 0;
    // For each line
    for (int i = 0; i < height; i++) {
        bool flag = true;
        // For each line checked if it is complete or not based on a flag
        for (int j = 0; j < width; j++) {
            if (table[i][j] == empty) {
                flag = false;
                break;
            }
        }
        // If is complete, then remove it
        if (flag) {
            deleteLine(i);
            cont++;
        }
    }
    return cont;
}

void Board::deleteLine(int line) {
    // We overwrite the cells of the line to be eliminated with the upper ones
    for (int i = line; i > 0; i--) {
        for (int j = 0; j < width; j++) {
            table[i][j] = table[i-1][j];
        }
    }
}

/* SFML methods */

void Board::copyToPrintable() {
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            printableTable[i][j] = table[i][j];
}

void Board::draw(RenderWindow* window, Sprite** blocks, Piece* piece, int x, int y) {
    // At first, we copy the "background"
    copyToPrintable();
    // And later we add the current piece to the board
    addPiece(printableTable, piece);
    // And draw all the matrix in the window depending on the color of each box
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) {
            char box = printableTable[i][j];
            if (box != empty) {
                blocks[box]->setPosition(x + j * boxSize, y + i * boxSize);
                window->draw(*blocks[box]);
            }
        }
}


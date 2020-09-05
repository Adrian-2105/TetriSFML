/**
 * Class representing a Tetris - C++ & SFML board.
 * Works directly with Piece and Game classes
 */

#ifndef TETRIS_BOARD_H
#define TETRIS_BOARD_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Piece.h"

// Size of each box in pixels
#define boxSize 25

using namespace sf;

class Board {

    friend class Game;

private:
    // Dimensions of the board
    int width, height;
    /* We use two different tables: one of them contains the immovable table
     * for the current piece, the other is built from that other table adding
     * the current piece to it. Each one contains the color of the piece that
     * corresponds to it. If it is empty it contains the value -1*/
    // Matrix which contains the used pieces
    char** table;
    // Matrix which will be printed in screen (original table + current piece)
    char** printableTable;

    // Helper method to add a piece to one of the tables
    void addPiece(char** table, Piece* piece) const;
    // Helper method to make a copy of the original table to the printable table
    void copyToPrintable();
    // Remove the entire indicated line and lower the top lines
    void deleteLine(int line);

public:
    // Constructor and destroyer
    Board(int w, int h);
    ~Board();

    // Initialize to empty all the table
    void clear();

    // Checks if the board and the piece collide with another pieces or
    // with the XY axis
    bool isCollision(Piece* piece);

    // Add a new piece to the principal table
    void addPiece(Piece* piece);

    // Method to remove the completed lines on the board
    int deleteCompleteLines();

    // Draw the board of the current frame in the window (only the matrix of pieces)
    void draw(RenderWindow* window, Sprite** blocks, Piece* piece, int x, int y);
};


#endif //TETRIS_BOARD_H

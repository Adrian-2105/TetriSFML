/**
 * Class representing a Tetris - C++ & SFML piece.
 * The Board and Game classes work with it by directly accessing
 * its private attributes, except with the widthBoard and heightBoard
 * (they vary with the direction of the piece and this must be a calculated property)
 */

#ifndef TETRIS_PIECE_H
#define TETRIS_PIECE_H

// Types of pieces
#define NUM_PIECES 7
enum PieceType {
    I, J, Z, O, L, S, T
};

// Types of directions
#define NUM_DIRECTIONS 4
enum Directions {
    UP, RIGHT, DOWN, LEFT
};

class Piece {

    friend class Game;
    friend class Board;

private:
    // Properties
    char type,           // type of piece (see enum PieceType)
         direction;      // direction the part is pointing
    int  width, height,  // dimensions of the piece
         x, y;           // XY axis of upper left corner position
    bool** M {};         // matrix representing the piece

    // Constructor and destroyer
    Piece(char _type, int _x, int _y);
    ~Piece();

    // Getters (calculate properties)
    int getWidth() const; // it depends of the current direction
    int getHeight() const; // this one too

    // Basic moves on the XY axis
    void moveLeft();
    void moveRight();
    void moveDown();
    void moveUp();

    /* Rotations (change the direction it's pointing)
     * That's a virtual move. the Board and Game classes are
     * in charge of reading the part matrix in the appropriate
     * way depending on its direction
     */
    void rotateRight();
    void rotateLeft();
};

#endif //TETRIS_PIECE_H

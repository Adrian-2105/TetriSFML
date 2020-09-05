#include "../include/Piece.h"

#define t true
#define f false

// Helper method to reserve the memory of the matrix of each piece
void reserve(bool** &M, int w, int h);

/* Constructor and destroyer */

Piece::Piece(char _type, int _x, int _y) {
    // Parameter properties
    type = _type;
    x = _x;
    y = _y;
    // Default properties
    direction = UP;

    // Creation of the piece based on its type
    switch (type) {
        case T:
            width = 3, height = 2;
            reserve(M, width, height);
            M[0][0] = f, M[0][1] = t, M[0][2] = f;
            M[1][0] = t, M[1][1] = t, M[1][2] = t;
            break;
        case L:
            width = 3, height = 2;
            reserve(M, width, height);
            M[0][0] = f, M[0][1] = f, M[0][2] = t;
            M[1][0] = t, M[1][1] = t, M[1][2] = t;
            break;
        case J:
            width = 3, height = 2;
            reserve(M, width, height);
            M[0][0] = t, M[0][1] = f, M[0][2] = f;
            M[1][0] = t, M[1][1] = t, M[1][2] = t;
            break;
        case I:
            width = 4, height = 1;
            reserve(M, width, height);
            M[0][0] = t, M[0][1] = t, M[0][2] = t, M[0][3] = t;
            break;
        case S:
            width = 3, height = 2;
            reserve(M, width, height);
            M[0][0] = f, M[0][1] = t, M[0][2] = t;
            M[1][0] = t, M[1][1] = t, M[1][2] = f;
            break;
        case Z:
            width = 3, height = 2;
            reserve(M, width, height);
            M[0][0] = t, M[0][1] = t, M[0][2] = f;
            M[1][0] = f, M[1][1] = t, M[1][2] = t;
            break;
        case O:
            width = 2, height = 2;
            reserve(M, width, height);
            M[0][0] = t, M[0][1] = t;
            M[1][0] = t, M[1][1] = t;
            break;
    }
}

Piece::~Piece() {
    for (int i = 0; i < height; i++)
        delete[] M[i];
    delete[] M;
}

/* Getters */

int Piece::getWidth() const {
    if (direction % 2 == 0)
        return width;
    return height;
}

int Piece::getHeight() const {
    if (direction % 2 == 0)
        return height;
    return width;
}

/* Piece movement */

void Piece::moveLeft() {
    x--;
}

void Piece::moveRight() {
    x++;
}

void Piece::moveDown() {
    y++;
}


void Piece::moveUp() {
    y--;
}

// Piece rotation

void Piece::rotateRight() {
    direction = (direction + 1) % NUM_DIRECTIONS;
}

void Piece::rotateLeft() {
    direction--;
    if (direction < 0)
        direction = LEFT;
}


/* Auxiliary functions */

void reserve(bool** &M, int w, int h) {
    M = new bool*[h];
    for (int i = 0; i < h; i++)
        M[i] = new bool[w];
}
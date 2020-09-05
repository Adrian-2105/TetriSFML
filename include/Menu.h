/*
 * Helper file to print and execute the three type of menu.
 * It has been designed quickly, so the interfaces are very crappy
 * and simple, as well as being able to contain a possible bug.
 */

#ifndef TETRIS_MENU_H
#define TETRIS_MENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

enum MenuActions {
    WindowClosed, Continue, ExitGame
};

using namespace sf;

char runMainMenu(RenderWindow* window, Sprite* logo, Text* text);
char runPauseMenu(RenderWindow* window, Text* text);
char runGameOverMenu(RenderWindow* window, Text* text, long long score);

#endif //TETRIS_MENU_H

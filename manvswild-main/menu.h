#ifndef MENU_H
#define MENU_H

#include "field.h"
#include "normalPlayer.h"

/**
 *  Represent the menu
 */
class menu {

public:
    menu(field &f);
    void showStartMenu(); // Show the menu
    void startGame(); // Start the game
    void endGame(int nbTurns, int nbWildcatsDead); // End the game

private:
    field &d_field;
};


#endif // MENU_H

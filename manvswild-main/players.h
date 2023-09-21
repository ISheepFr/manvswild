#ifndef PLAYERS_H_INCLUDED
#define PLAYERS_H_INCLUDED

#include <string>
#include "gameElement.h"

/** Abstract class
 *  Represent a player without difficulty level
 */
class players : public gameElement {
public:
    void setPosition(int x, int y, field *f) override = 0;
    char getElementName() const override = 0;

    int posX() const override = 0;
    int posY() const override = 0;

    virtual bool isValidMove(int& xD, int& yD, int& xA, int& yA, field *f) = 0;

};


#endif // PLAYERS_H_INCLUDED

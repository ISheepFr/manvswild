#ifndef NORMALPLAYER_H_INCLUDED
#define NORMALPLAYER_H_INCLUDED

#include "players.h"
#include "field.h"

/**
 *  Represent a player with normal difficulty
 */
class normalPlayer : public players{

public :
    normalPlayer(char playerName);
    normalPlayer(char playerName, int x, int y);

    void setPosition(int x, int y, field *f) override;
    char getElementName() const override;

    int posX() const override;
    int posY() const override;

    bool isValidMove(int& xD, int& yD, int& xA, int& yA, field *f) override;
private :
     char d_playerName;
     int d_posX;
     int d_posY;
};

#endif // NORMALPLAYER_H_INCLUDED

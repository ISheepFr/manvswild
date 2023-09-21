#ifndef LIONS_H_INCLUDED
#define LIONS_H_INCLUDED

#include "wildcats.h"
#include "field.h"

/**
 *  Represent a lion
 */
class lions : public wildcats{

public :

    lions(char species);
    lions(char species, int x, int y);

    void setPosition(int x, int y, field *f) override;
    char getElementName() const override;

    int posX() const override;
    int posY() const override;

    int nextPosX() const override;
    int nextPosY() const override;

    void nextPosition(field* f ,std::unique_ptr<players> p) override;
    bool isValidMove(field *field) override;

private :
     char d_wildcatSpecies = 'L';
     int d_posX;
     int d_posY;

     int d_nextposX;
     int d_nextposY;

     bool d_state;
};

#endif // LIONS_H_INCLUDED

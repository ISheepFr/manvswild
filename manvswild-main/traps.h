#ifndef TRAPS_H_INCLUDED
#define TRAPS_H_INCLUDED

#include "obstacles.h"

/**
 *  Represent a trap
 */
class traps : public obstacles{

public :
    traps(char obstacleName, int x, int y);
    void setPosition(int x, int y, field *f) override;
    char getElementName() const override;
    int posX() const override;
    int posY() const override;
private :
     char d_obstacleName;
     int d_posX;
     int d_posY;
};


#endif // TRAPS_H_INCLUDED

#ifndef ROCKS_H_INCLUDED
#define ROCKS_H_INCLUDED

#include "obstacles.h"

/**
 *  Represent a rock
 */
class rocks : public obstacles{

public :
    rocks(char obstacleName, int x, int y);
    void setPosition(int x, int y, field *f) override;
    char getElementName() const override;
    int posX() const override;
    int posY() const override;
private :
     char d_obstacleName;
     int d_posX;
     int d_posY;
};



#endif // ROCKS_H_INCLUDED

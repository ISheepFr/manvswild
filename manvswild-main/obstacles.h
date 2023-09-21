#ifndef OBSTACLES_H_INCLUDED
#define OBSTACLES_H_INCLUDED

#include <string>
#include "gameElement.h"
#include "field.h"

/** Abstract class
 *  Represent a obstacle
 */
class obstacles : public gameElement {

public:
    void setPosition(int x, int y, field *f) override = 0;
    char getElementName() const override = 0;
    int posX() const override = 0;
    int posY() const override = 0;

};



#endif // OBSTACLES_H_INCLUDED

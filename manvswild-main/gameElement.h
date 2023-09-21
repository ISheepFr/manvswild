#ifndef GAMEELEMENT_H_INCLUDED
#define GAMEELEMENT_H_INCLUDED

#include <iostream>

using std::string;
using std::cout;

/**
 * Used for the declaration of setPosition method
 */
class field;

/** Abstract class
 *  Represent a game element : wildcat, obstacle and player
 */
class gameElement {
public:
    virtual void setPosition(int x, int y, field *f) = 0;
    virtual ~gameElement() = default;
    virtual char getElementName() const = 0;
    virtual int posX() const = 0;
    virtual int posY() const = 0;
};

#endif // GAMEELEMENT_H_INCLUDED

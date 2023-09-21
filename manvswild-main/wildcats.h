#ifndef WILDCATS_H_INCLUDED
#define WILDCATS_H_INCLUDED

#include "gameElement.h"

#include "players.h"
#include <memory>

#include <cmath>
#include <string>

/** Abstract class
 *  Represent a wildcat
 */
class wildcats : public gameElement {

public:
    void setPosition(int x, int y, field *f) override = 0;
    char getElementName() const override = 0;

    int posX() const override = 0;
    int posY() const override = 0;

    virtual int nextPosX() const = 0;
    virtual int nextPosY() const = 0;

    virtual void nextPosition(field* f, std::unique_ptr<players> p) = 0;
    virtual bool isValidMove(field *field) = 0;

    virtual ~wildcats() = default;

    /**
     * Calculate the distance between the player and the wildcat
     * @param int x - Position x of the wildcat
     * @param int y - Position y of the wildcat
     * @param players* p - Player use for calculation
     */
    double distance(int x, int y, std::unique_ptr<players> p){
        int x_diff = x - p->posX();
        int y_diff = y - p->posY();

        return std::sqrt(x_diff * x_diff + y_diff * y_diff);
    };


};



#endif // WILDCATS_H_INCLUDED

#include "rocks.h"

/**
 * Constructor of a rock by it's name and positions
 * @param char obstacleName - Name of the rock
 * @param int x - Position x of the rock
 * @param int y - Position y of the rock
 */
rocks::rocks(char obstacleName, int x, int y) : d_obstacleName{obstacleName}, d_posX{x}, d_posY{y}
{}

/**
 * Set the position of the rock on the field
 * @param int x - Future position x of the rock
 * @param int y - Future position y of the rock
 * @param field* f - Field where the rock can be placed
 */
void rocks::setPosition(int x, int y, field *f){
    d_posX = x;
    d_posY = y;
}

/**
 * Get the name of the rock
 * @return char - Name of the rock
 */
char rocks::getElementName() const {
    return d_obstacleName;
}

/**
 * Get the position x of the rock
 * @return int - Position x of the rock
 */
int rocks::posX() const {
    return d_posX;
}

/**
 * Get the position y of the rock
 * @return int - Position y of the rock
 */
int rocks::posY() const {
    return d_posY;
}


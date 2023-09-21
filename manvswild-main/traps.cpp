#include "traps.h"

/**
 * Constructor of a trap by it's name and positions
 * @param char obstacleName - Name of the trap
 * @param int x - Position x of the trap
 * @param int y - Position y of the trap
 */
traps::traps(char obstacleName, int x, int y) : d_obstacleName{obstacleName}, d_posX{x}, d_posY{y}
{}

/**
 * Set the position of the trap on the field
 * @param int x - Future position x of the trap
 * @param int y - Future position y of the trap
 * @param field* f - Field where the trap can be placed
 */
void traps::setPosition(int x, int y, field *f){
    d_posX = x;
    d_posY = y;
}

/**
 * Get the name of the trap
 * @return char - Name of the trap
 */
char traps::getElementName() const {
    return d_obstacleName;
}

/**
 * Get the position x of the trap
 * @return int - Position x of the trap
 */
int traps::posX() const {
    return d_posX;
}

/**
 * Get the position y of the trap
 * @return int - Position y of the trap
 */
int traps::posY() const {
    return d_posY;
}


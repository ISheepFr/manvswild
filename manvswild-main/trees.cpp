#include "trees.h"

/**
 * Constructor of a tree by it's name and positions
 * @param char obstacleName - Name of the tree
 * @param int x - Position x of the tree
 * @param int y - Position y of the tree
 */
trees::trees(char obstacleName, int x, int y) : d_obstacleName{obstacleName}, d_posX{x}, d_posY{y}
{}

/**
 * Set the position of the tree on the field
 * @param int x - Future position x of the tree
 * @param int y - Future position y of the tree
 * @param field* f - Field where the tree can be placed
 */
void trees::setPosition(int x, int y, field *f){
    d_posX = x;
    d_posY = y;
}

/**
 * Get the name of the tree
 * @return char - Name of the tree
 */
char trees::getElementName() const {
    return d_obstacleName;
}

/**
 * Get the position x of the tree
 * @return int - Position x of the tree
 */
int trees::posX() const {
    return d_posX;
}

/**
 * Get the position y of the tree
 * @return int - Position y of the tree
 */
int trees::posY() const {
    return d_posY;
}

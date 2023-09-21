#include "lions.h"

/**
 * Constructor of a lion by it's name
 * @param char species - Species of the lion
 */
lions::lions(char species) : d_wildcatSpecies{species}, d_posX{0}, d_posY{0}
{}

/**
 * Constructor of a lion by it's name and positions
 * @param char species - Species of the lion
 * @param int x - Position x of the lion
 * @param int y - Position y of the lion
 */
lions::lions(char species, int x, int y) : d_wildcatSpecies{species}, d_posX{x}, d_posY{y}
{}

/**
 * Set the position of the lion on the field
 * @param int x - Future position x of the lion
 * @param int y - Future position y of the lion
 * @param field* f - Field where the lion moves on
 */
void lions::setPosition(int x, int y, field *f){
    f->setLionInField(d_posX,d_posY,x,y);
    d_posX = x;
    d_posY = y;
}

/**
 * Get the species of the lion
 * @return char - Species of the lion
 */
char lions::getElementName() const {
    return d_wildcatSpecies;
}

/**
 * Get the position x of the lion
 * @return int - Position x of the lion
 */
int lions::posX() const {
    return d_posX;
}

/**
 * Get the position y of the lion
 * @return int - Position y of the lion
 */
int lions::posY() const {
    return d_posY;
}

/**
 * Get the next position x of the lion
 * @return int - Next position x of the lion
 */
int lions::nextPosX() const {
    return d_nextposX;
}

/**
 * Get the next position y of the lion
 * @return int - Next position y of the lion
 */
int lions::nextPosY() const{
    return d_nextposY;
}

/**
 * Set the best next position x and y for the lion
 * @param field* f - Field where the lion moves on
 * @param players* p - Player used for the best move for lion
 */
void lions::nextPosition(field* f, std::unique_ptr<players> p)
{
    int ind_x = d_posX;
    int ind_y = d_posY;
    double cost = distance(d_posX, d_posY, std::move(p));

    for(int i = d_posY-1 ; i <= d_posY+1 ; i++) // Pour toutes les cases de y-1 a y+1
    {
        for(int j = d_posX-1 ; j <= d_posX+1 ; j++) // Pour toutes les cases de x-1 a x+1
        {

            if((j == d_posX && i != d_posY) || (j != d_posX && i == d_posY))  //
            {


                if( !(j<0 || j>MAP_SIZE-1 || i<0 || i>MAP_SIZE-1) )   //SI position est dans la grille
                {

                    char type = f->getElementType(j,i);
                    if( type != 'R' && type != 'W') //SI la case d'arrivée n'est pas un obstacle
                    {
                        std::unique_ptr<players> cp = f->getNormalPlayer();
                        double newcost = distance(j,i,std::move(cp));
                        if ( newcost <= cost)   //Si la distance tigre - joueur est meilleur
                        {

                            ind_x = j;
                            ind_y = i;
                            cost = newcost;     // nouveau cout

                        }
                    }
                }
            }
        }
    }

    //retourne la meilleur pos X et Y
    d_nextposX = ind_x;
    d_nextposY = ind_y;

}

/**
 * Verify if a lion can move where he wants to on the field
 * @param field* f - Field where the lion moves on
 * @return bool - True if the move can be realised / False if not
 */
bool lions::isValidMove(field *f)
{

    char type = f->getElementType(d_nextposX,d_nextposY);
            //Vérifier si obstacle sur la case arrivée
            if (type != '\0')
            {

                if (type == d_wildcatSpecies)
                {

                    return false;
                }
            }
            else
            {
                return true;
            }

    return true;
}


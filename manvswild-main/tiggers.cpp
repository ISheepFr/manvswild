#include "tiggers.h"

/**
 * Constructor of a tigger by it's name
 * @param char species - Species of the tigger
 */
tiggers::tiggers(char species) : d_wildcatSpecies{species}, d_posX{0}, d_posY{0}
{}

/**
 * Constructor of a tigger by it's name and positions
 * @param char species - Species of the tigger
 * @param int x - Position x of the tigger
 * @param int y - Position y of the tigger
 */
tiggers::tiggers(char species, int x, int y) : d_wildcatSpecies{species}, d_posX{x}, d_posY{y}
{}

/**
 * Set the position of the tigger on the field
 * @param int x - Future position x of the tigger
 * @param int y - Future position y of the tigger
 * @param field* f - Field where the tigger moves on
 */
void tiggers::setPosition(int x, int y, field *f){
    f->setTiggerInField(d_posX,d_posY,x,y);
    d_posX = x;
    d_posY = y;
}

/**
 * Get the species of the tigger
 * @return char - Species of the tigger
 */
char tiggers::getElementName() const {
    return d_wildcatSpecies;
}

/**
 * Get the position x of the tigger
 * @return int - Position x of the tigger
 */
int tiggers::posX() const {
    return d_posX;
}

/**
 * Get the position y of the tigger
 * @return int - Position y of the tigger
 */
int tiggers::posY() const {
    return d_posY;
}

/**
 * Get the next position x of the tigger
 * @return int - Next position x of the tigger
 */
int tiggers::nextPosX() const {
    return d_nextposX;
}

/**
 * Get the next position y of the tigger
 * @return int - Next position y of the tigger
 */
int tiggers::nextPosY() const{
    return d_nextposY;
}

/**
 * Set the best next position x and y for the tigger
 * @param field* f - Field where the tigger moves on
 * @param players* p - Player used for the best move for tigger
 */
void tiggers::nextPosition(field* f, std::unique_ptr<players> p)
{

    int ind_x = d_posX;
    int ind_y = d_posY;

    double cost = distance(d_posX, d_posY, std::move(p));


   // cout << "DISTANCE TO PLAYER :" << cost;
    for(int i = d_posY-1 ; i <= d_posY+1 ; i++) // Pour toutes les cases de y-1 a y+1
    {
        for(int j = d_posX-1 ; j <= d_posX+1 ; j++) // Pour toutes les cases de x-1 a x+1
        {
            if( !(j<0 || j>MAP_SIZE-1 || i<0 || i>MAP_SIZE-1) )   //SI position est dans la grille
            {

                char type = f->getElementType(j,i);

                if( type != 'R' && type != 'W') //SI la case d'arrivée n'est pas un obstacle
                {
                    std::unique_ptr<players> cp = f->getNormalPlayer();
                    double newcost = distance(j,i,std::move(cp));
                    //cout << "DISTANCE TO PLAYER :" << newcost;
                    if ( newcost <= cost)   //Si la distance tigre - joueur est meilleur
                    {
                        if(type != d_wildcatSpecies)
                        {


                        //cout <<"DANS LE IF";
                        ind_x = j;
                        ind_y = i;
                        cost = newcost;     // nouveau cout
                        //cout << "New distance = " << cost;
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
 * Verify if a tigger can move where he wants to on the field
 * @param field* f - Field where the tigger moves on
 * @return bool - True if the move can be realised / False if not
 */
bool tiggers::isValidMove(field* f)
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






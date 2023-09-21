#include "normalPlayer.h"

/**
 * Constructor of a normal player by it's name
 * @param char playerName - Name of the player
 */
normalPlayer::normalPlayer(char playerName) : d_playerName{playerName}, d_posX{0}, d_posY{0}
{}

/**
 * Constructor of a normal player by it's name and positions
 * @param char playerName - Name of the player
 * @param int x - Position x of the normal player
 * @param int y - Position y of the normal player
 */
normalPlayer::normalPlayer(char playerName, int x, int y) : d_playerName{playerName}, d_posX{x}, d_posY{y}
{}

/**
 * Get the name of the normal player
 * @return char - Name of the normal player
 */
char normalPlayer::getElementName() const {
    return d_playerName;
}

/**
 * Get the position x of the normal player
 * @return int - Position x of the normal player
 */
int normalPlayer::posX() const {
    return d_posX;
}

/**
 * Get the position y of the normal player
 * @return int - Position y of the normal player
 */
int normalPlayer::posY() const {
    return d_posY;
}

/**
 * Verify if a normalPlayer can move where he wants to on the field
 * @param int& xD - Current position x of the normal player
 * @param int& yD - Current position y of the normal player
 * @param int& xA - Future position x of the normal player
 * @param int& yA - Future position y of the normal player
 * @param field* f - Field where the normal player moves on
 * @return bool - True if the move can be realised / False if not
 */
bool normalPlayer::isValidMove(int& xD, int& yD, int& xA, int& yA, field *f){

    if (xA<0 || xA>MAP_SIZE-1 || yA<0 || yA>MAP_SIZE-1){
        cout << "Vous ne pouvez pas sortir de la grille !\n";
        return false;
    }
    else{

        //Vérifier qu'on se déplace d'une seule case
        if ((abs(xA - xD) <= 1) && (abs(yA - yD) <= 1))
        {
            char type = f->getElementType(xA,yA);
            //Vérifier si obstacle sur la case arrivée
            if (f->getElementType(xA,yA) != '\0')
            {
                if (type == 'R' || type == 'W')
                {
                    cout << "Le mouvement est invalide : c'est fait pour bloquer ...\n";
                    return false;
                }
                else if (type == 'T' || type == 'L')
                {
                    cout << "Le mouvement est invalide : vous voulez pas vous faire bouffer !? \n";
                    return false;
                }
                else if (type == 'H')
                {
                    cout << "Vous ne survivez pas au piege. Vous mourrez instantanement. \n";
                    return true;
                }
            }
            else
            {
                cout << "Le mouvement est valide \n";
                return true;
            }
        }
        else {
            cout << "Vous ne pouvez vous deplacer que d'une case autour de vous !\n";
            return false;
        }
    }
}

/**
 * Set the position of the normal player on the field
 * @param int x - Future position x of the normal player
 * @param int y - Future position y of the normal player
 * @param field* f - Field where the normal player moves on
 */
void normalPlayer::setPosition(int x, int y, field *f){
    if (isValidMove(this->d_posX, this->d_posY, x, y, f)){
        f->setNormalPlayerInField(d_posX,d_posY,x,y);
        d_posX = x;
        d_posY = y;
    }
}

#include "menu.h"

#include <iostream>

using std::cout;
using std::cin;

/**
 * Constructor of a menu
 * @param field - the field where we will play
 */
menu::menu(field &f) : d_field{f} { }

/**
 * Show the start menu
 */
void menu::showStartMenu() {
    cout << "\n";

    cout << "\t\t\t---------------------------------------" << "\n";
    cout << "\t\t\t| Bienvenue dans Man VS Wild : le jeu |" << "\n";
    cout << "\t\t\t---------------------------------------" << "\n";

    int choice {-1};

    while(choice < 1 || choice > 5) {
        cout << "\n";
        cout << "1) Jouer \t 2) Afficher un terrain \t 3) Creer un terrain \t 4) Modifier un terrain \t 5) Quitter \n\n";
        cout << " \x10 "; // affiche un caractère spécial (sorte de flèche)
        cin >> choice;
    }

    switch(choice) {

        case 1:
            startGame();
            break;

        case 2:
            d_field.selectField();
            showStartMenu();
            break;

        case 3: {
            std::string fieldName;

            cout << "\n Comment souhaitez-vous nommer votre terrain (ajouter l'extension .txt a la fin du nom)?\n";
            cout << " \x10 ";
            cin >> fieldName;

            d_field.createField(fieldName);
            showStartMenu();
            break;
        }

        case 4:
            d_field.selectField();
            d_field.editField(d_field.getFieldName());
            showStartMenu();
            break;

        case 5:
            cout << "\nOn esp\x8Are vous revoir tr\x8As vite\n";
            break;

        default:
            break;
    }

}

/**
 * Main loop of the game
 */
void menu::startGame(){
    bool gameState = true;
    int nbTurns = 1;
    int nbWildcatsDead = 0;

    d_field.selectField();

    cout << "La partie va commencer, vous tacherez de survivre !\n";

    while (d_field.isNormalPlayer() == true && d_field.isWildcats() == true ){
        cout << "Tour " << nbTurns << '\n' << "Veuillez choisir un deplacement : \n" ;
        int x,y;
        cin >> x >> y;

        std::unique_ptr<players> player = d_field.getNormalPlayer();
        int pX = player->posX();
        int pY = player->posY();

        while (!player->isValidMove(pX, pY, x, y, &d_field)){
            cout << "Veuillez choisir un deplacement : \n" ;
            cin >> x >> y;
        }
        player->setPosition(x,y,&d_field);

        d_field.showMap();

        std::vector<std::unique_ptr<wildcats>> t = d_field.getTiggers();
        std::vector<std::unique_ptr<wildcats>> l = d_field.getLions();

        for(const auto& wc : t)
        {
            std::unique_ptr<players> pCP = d_field.getNormalPlayer();

            wc->nextPosition(&d_field , std::move(pCP));

            if(wc->isValidMove(&d_field))
            {
                if(d_field.getElementType(wc->nextPosX(),wc->nextPosY()) == 'H')
                {
                    nbWildcatsDead++;
                }
                wc->setPosition(wc->nextPosX(), wc->nextPosY(), &d_field);



            }
            if(d_field.isNormalPlayer() == false)
            {
                break;
            }
        }

                if(d_field.isNormalPlayer() == false)
            {
                break;
            }

        for(const auto& wc_l : l)
        {

            std::unique_ptr<players> pCP = d_field.getNormalPlayer();

            wc_l->nextPosition(&d_field , std::move(pCP));
            if(wc_l->isValidMove(&d_field))
            {
                if(d_field.getElementType(wc_l->nextPosX(),wc_l->nextPosY()) == 'H')
                {
                    nbWildcatsDead++;
                }
                wc_l->setPosition(wc_l->nextPosX(), wc_l->nextPosY(), &d_field);

            }

            if(d_field.isNormalPlayer() == false)
            {
                break;
            }


        }
        d_field.showMap();



        nbTurns += 1;
    }

    endGame(nbTurns-1, nbWildcatsDead);
}

/**
 * End the game and print results
 * @param nbTurns - Number of turns passed until the end
 * @param nbWildcatsDead - Number of wildcats dead at the end
 */
void menu::endGame(int nbTurns, int nbWildcatsDead){
    cout << "La partie est finie ! Voici vos scores :\n";
    cout << "Nombre de tours : " << nbTurns << '\n';
    cout << "Nombre de fauves morts : " << nbWildcatsDead << '\n';
}

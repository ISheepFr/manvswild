#include "doctest.h"
#include "normalPlayer.h"
#include "field.h"

void leJoueurEstExactement(const normalPlayer& p, char nom, int x, int y) {
    REQUIRE( p.getElementName() == nom );
    REQUIRE( p.posX() == x );
    REQUIRE( p.posY() == y );
}

void lesCoordonnesDuJoueurSontExactement(const normalPlayer& p, int x, int y) {
    REQUIRE_EQ( p.posX(), x );
    REQUIRE_EQ( p.posY(), y );
}

void lesCoordonnesDuJoueurSont(const normalPlayer& p, int x, int y) {
    REQUIRE( p.posX() == doctest::Approx(x) );
    REQUIRE( p.posY() == doctest::Approx(y) );
}



TEST_CASE("[normalPlayer] Les joueurs normaux sont bien construits") {
    SUBCASE("Le constructeur avec des coordonnées est correct" ) {
        char n{'P'};
        int x {3}, y {3};
        normalPlayer p1{n, x, y};
        leJoueurEstExactement(p1, n, x, y);
    }

    SUBCASE("Le constructeur par défaut est correct" ) {
        char n{'P'};
        normalPlayer p2 {n};
        leJoueurEstExactement(p2, n, 0, 0);
    }
}


TEST_CASE("Déplacements des joueurs normaux") {
    int x {1}, y {4};
    normalPlayer p{'P',x,y};
    field f;
    f.importMap("default.txt");

    SUBCASE( "La copie est correcte" ) {
        int x2 {x+1}, y2 {y-1};
        p = normalPlayer{'P', x2, y2};
        lesCoordonnesDuJoueurSontExactement(p, x2, y2);
    }
    SUBCASE( "Le changement est correct" ) {
        int dx = 2, dy = 4;
        p.setPosition(dx,dy,&f);
        lesCoordonnesDuJoueurSont(p, dx, dy);
    }
    SUBCASE( "Le changement est incorrect : Déplacement trop loin x" ) {
        int dx = 3, dy = 4;
        p.setPosition(dx,dy,&f);
        REQUIRE_EQ(p.posX(),x);
    }
    SUBCASE( "Le changement est incorrect : Déplacement trop loin y" ) {
        int dx = 1, dy = 6;
        p.setPosition(dx,dy,&f);
        REQUIRE_EQ(p.posY(),y);
    }
    SUBCASE( "Le changement est incorrect : Sortie du terrain en haut" ) {
        int x {4}, y {1};
        normalPlayer p{'P',x,y};
        int dx = 4, dy = -1;
        f.importMap("defaultTestSortieEnHaut.txt");
        p.setPosition(dx,dy,&f);
        REQUIRE_EQ(p.posY(),y);
        REQUIRE_EQ(p.posX(),dx);
    }
    SUBCASE( "Le changement est incorrect : Sortie du terrain en bas" ) {
        int x {4}, y {8};
        normalPlayer p{'P',x,y};
        int dx = 4, dy = 9;
        f.importMap("defaultTestSortieEnBas.txt");
        p.setPosition(dx,dy,&f);
        REQUIRE_EQ(p.posY(),y);
        REQUIRE_EQ(p.posX(),dx);
    }
    SUBCASE( "Le changement est incorrect : Sortie du terrain a droite" ) {
        int x {7}, y {5};
        normalPlayer p{'P',x,y};
        int dx = 8, dy = 5;
        f.importMap("defaultTestSortieADroite.txt");
        p.setPosition(dx,dy,&f);
        REQUIRE_EQ(p.posX(),x);
        REQUIRE_EQ(p.posY(),dy);
    }
    SUBCASE( "Le changement est incorrect : Sortie du terrain a gauche" ) {
        int x {0}, y {7};
        normalPlayer p{'P',x,y};
        int dx = -1, dy = 7;
        f.importMap("defaultTestSortieAGauche.txt");
        p.setPosition(dx,dy,&f);
        REQUIRE_EQ(p.posX(),x);
        REQUIRE_EQ(p.posY(),dy);
    }
    SUBCASE( "Le changement est correct : le joueur tombe dans un trou" ) {
        int x {0}, y {1};
        normalPlayer p{'P',x,y};
        int dx = 0, dy = 0;
        f.importMap("defaultTestSortieAGauche.txt");
        p.setPosition(dx,dy,&f);
        REQUIRE_EQ(p.posX(),dx);
        REQUIRE_EQ(p.posY(),dy);
    }
}



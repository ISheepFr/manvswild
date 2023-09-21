#include "doctest.h"
#include "lions.h"
#include "players.h"
#include "normalPlayer.h"
#include <memory>


void leLionEstExactement(const lions& l, char nom, int x, int y) {
    REQUIRE( l.getElementName() == nom );
    REQUIRE( l.posX() == x );
    REQUIRE( l.posY() == y );
}

void lesCoordonnesDuLionSontExactement(const lions& l, int x, int y) {
    REQUIRE_EQ( l.posX(), x );
    REQUIRE_EQ( l.posY(), y );
}

void lesCoordonnesDuLionSont(const lions& l, int x, int y) {
    REQUIRE( l.posX() == doctest::Approx(x) );
    REQUIRE( l.posY() == doctest::Approx(y) );
}



TEST_CASE("[lions] Les lions sont bien construits") {
    SUBCASE("Le constructeur avec des coordonnées est correct" ) {
        char l{'L'};
        int x {3}, y {3};
        lions l1{l, x, y};
        leLionEstExactement(l1, l, x, y);
    }

    SUBCASE("Le constructeur par défaut est correct" ) {
        char l{'L'};
        lions l2 {l};
        leLionEstExactement(l2, l, 0, 0);
    }
}

TEST_CASE("[lions] Les déplacements des lions sont correctes") {

    int x {7}, y {7};
    lions l{'L',x,y};
    std::unique_ptr<players> np = std::make_unique<normalPlayer>('P',1,4);
    field f;
    f.importMap("default.txt");

    SUBCASE( "La copie est correcte" ) {
        int x2 {x+1}, y2 {y-1};
        l = lions{'L', x2, y2};
        lesCoordonnesDuLionSontExactement(l, x2, y2);
    }

    SUBCASE( "Le changement en fonction du joueur est correct" ) {
        int dx = 6, dy = 6;
        l.nextPosition(&f, std::move(np));
        l.setPosition(dx,dy,&f);
        lesCoordonnesDuLionSont(l, dx, dy);

    }
    SUBCASE( "Le changement est correct : le tiggre tombe dans un trou" ) {
        int x {1}, y {2};
        lions l{'L',x,y};
        int dx = 2, dy = 2;
        f.importMap("trou_fauve.txt");
        l.nextPosition(&f, std::move(np));
        l.setPosition(dx,dy,&f);
        REQUIRE_EQ(l.posX(),dx);
        REQUIRE_EQ(l.posY(),dy);
    }
}

#include "doctest.h"
#include "tiggers.h"
#include "players.h"
#include "normalPlayer.h"
#include <memory>

void leTigreEstExactement(const tiggers& t, char nom, int x, int y) {
    REQUIRE( t.getElementName() == nom );
    REQUIRE( t.posX() == x );
    REQUIRE( t.posY() == y );
}

void lesCoordonnesDuTigreSontExactement(const tiggers& t, int x, int y) {
    REQUIRE_EQ( t.posX(), x );
    REQUIRE_EQ( t.posY(), y );
}

void lesCoordonnesDuTigreSont(const tiggers& t, int x, int y) {
    REQUIRE( t.posX() == doctest::Approx(x) );
    REQUIRE( t.posY() == doctest::Approx(y) );
}



TEST_CASE("[tiggers] Les tiggers sont bien construits") {
    SUBCASE("Le constructeur avec des coordonnées est correct" ) {
        char t{'T'};
        int x {7}, y {7};
        tiggers t1{t, x, y};
        leTigreEstExactement(t1, t, x, y);
    }

    SUBCASE("Le constructeur par défaut est correct" ) {
        char t{'T'};
        tiggers t2 {t};
        leTigreEstExactement(t2, t, 0, 0);
    }
}

TEST_CASE("[tiggers] Les déplacements des tiggers sont correctes") {
    int x {7}, y {7};
    tiggers t{'T',x,y};
    std::unique_ptr<players> np = std::make_unique<normalPlayer>('P',1,4);
    field f;
    f.importMap("default.txt");

    SUBCASE( "La copie est correcte" ) {
        int x2 {x+1}, y2 {y-1};
        t = tiggers{'T', x2, y2};
        lesCoordonnesDuTigreSontExactement(t, x2, y2);
    }

    SUBCASE( "Le changement en fonction du joueur est correct" ) {
        int dx = 6, dy = 6;
        t.nextPosition(&f, std::move(np));
        t.setPosition(dx,dy,&f);
        lesCoordonnesDuTigreSont(t, dx, dy);

    }
    SUBCASE( "Le changement est correct : le tiggre tombe dans un trou" ) {
        int x {1}, y {2};
        tiggers t{'T',x,y};
        int dx = 2, dy = 2;
        f.importMap("trou_fauve.txt");
        t.nextPosition(&f, std::move(np));
        t.setPosition(dx,dy,&f);
        REQUIRE_EQ(t.posX(),dx);
        REQUIRE_EQ(t.posY(),dy);
    }





}


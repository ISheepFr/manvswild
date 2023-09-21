#include "doctest.h"
#include "trees.h"

void lArbreEstExactement(const trees& t, char nom, int x, int y) {
    REQUIRE( t.getElementName() == nom );
    REQUIRE( t.posX() == x );
    REQUIRE( t.posY() == y );
}

void lesCoordonnesDeLArbreSontExactement(const trees& t, int x, int y) {
    REQUIRE_EQ( t.posX(), x );
    REQUIRE_EQ( t.posY(), y );
}

void lesCoordonnesDeLArbreSont(const trees& t, int x, int y) {
    REQUIRE( t.posX() == doctest::Approx(x) );
    REQUIRE( t.posY() == doctest::Approx(y) );
}


TEST_CASE("[trees] Les arbres sont bien construits") {
    SUBCASE("Le constructeur avec des coordonn�es est correct" ) {
        char t{'W'};
        int x {3}, y {3};
        trees t1{t, x, y};
        lArbreEstExactement(t1, t, x, y);
    }
}

TEST_CASE("[trees] Les d�placements des arbres sont correctes") {
    /** Si un syst�me d'�v�nements est mis en place (Ex : association qui d�place les arbres et en plante de nouveaux
    */
}


#include "doctest.h"
#include "traps.h"

void lePiegeEstExactement(const traps& t, char nom, int x, int y) {
    REQUIRE( t.getElementName() == nom );
    REQUIRE( t.posX() == x );
    REQUIRE( t.posY() == y );
}

void lesCoordonnesDuPiegeSontExactement(const traps& t, int x, int y) {
    REQUIRE_EQ( t.posX(), x );
    REQUIRE_EQ( t.posY(), y );
}

void lesCoordonnesDuPiegeSont(const traps& t, int x, int y) {
    REQUIRE( t.posX() == doctest::Approx(x) );
    REQUIRE( t.posY() == doctest::Approx(y) );
}



TEST_CASE("[traps] Les pi�ges sont bien construits") {
    SUBCASE("Le constructeur avec des coordonn�es est correct" ) {
        char t{'H'};
        int x {3}, y {3};
        traps t1{t, x, y};
        lePiegeEstExactement(t1, t, x, y);
    }
}

TEST_CASE("[traps] Les d�placements des pi�ges sont correctes") {
    /** Si un syst�me d'�v�nements est mis en place (Ex : tornade qui d�place les pi�ges
    */
}


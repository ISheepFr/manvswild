#include "doctest.h"
#include "rocks.h"

void leRocherEstExactement(const rocks& r, char nom, int x, int y) {
    REQUIRE( r.getElementName() == nom );
    REQUIRE( r.posX() == x );
    REQUIRE( r.posY() == y );
}

void lesCoordonnesDuRocherSontExactement(const rocks& r, int x, int y) {
    REQUIRE_EQ( r.posX(), x );
    REQUIRE_EQ( r.posY(), y );
}

void lesCoordonnesDuRocherSont(const rocks& r, int x, int y) {
    REQUIRE( r.posX() == doctest::Approx(x) );
    REQUIRE( r.posY() == doctest::Approx(y) );
}


TEST_CASE("[rocks] Les arbres sont bien construits") {
    SUBCASE("Le constructeur avec des coordonnées est correct" ) {
        char r{'R'};
        int x {3}, y {3};
        rocks r1{r, x, y};
        leRocherEstExactement(r1, r, x, y);
    }
}

TEST_CASE("[rocks] Les déplacements des rochers sont correctes") {
    /** Si un système d'événements est mis en place (Ex : ingénieurs en bâtiment qui déplace les rochers
    */
}


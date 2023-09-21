#include "menu.h"
#include "field.h"

#include <vector>
#include <memory>
#include <iostream>

int main()
{
    field f;
    menu m {f};
    m.showStartMenu();

    return 0;
}

#include "Console/Console.h"
#include "Menu/Menu.h"

int main() {
    Console::init();
    Menu menu;
    menu.startMenu();

    return 0;
}
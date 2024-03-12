
#include "player.h"
#include "menu.h"
#include <limits>
#include <vector>

// the game's entry point: the principal menu!
int main() {

    // clear the terminal: try windows command and if error, then linux command
    int res = system("cls");
    if (res != 0) {
        res = system("clear");
    }
    int choice;
    do {
        // displaying the menu
        choice = menu::getMenuChoice("------------ Adventure ------------", std::vector<std::string>{"New Game", "Quit"});
        switch (choice) {
            case 1:
                // let's begin the adventure
                player::creationMenu();
                break;
            case 2:
                // bye bye! See you soon!
                break;
        }

    // until you want to quit
    } while (choice != 2);

    return 0;
}

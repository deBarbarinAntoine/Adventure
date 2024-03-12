
#include "player.h"
#include "menu.h"
#include <limits>
#include <vector>

int main() {
    int res = system("cls");
    if (res != 0) {
        system("clear");
    }
    int choice;
    do {
        choice = menu::getMenuChoice("------------ Adventure ------------", std::vector<std::string>{"New Game", "Quit"});
        switch (choice) {
            case 1:
                player::creationMenu();
                break;
            case 2:
                break;
        }
    } while (choice != 2);

    return 0;
}

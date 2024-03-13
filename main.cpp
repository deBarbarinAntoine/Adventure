
#include "player.h"
#include "menu.h"
#include <limits>
#include <vector>
#include <chrono>
#include <thread>

// the game's entry point: the principal menu!
int main() {

    int choice;
    do {
        // clear the terminal: try windows command and if error, then linux command
        int res = system("cls");
        if (res != 0) {
            res = system("clear");
        }

        // displaying the menu
        choice = menu::getMenuChoice("------------ Adventure ------------", std::vector<std::string>{"New Game", "Quit"});
        switch (choice) {
            case 1:
                // let's begin the adventure
                player::creationMenu();
                break;
            case 2:
                // clear the terminal: try windows command and if error, then linux command
                res = system("cls");
                if (res != 0) {
                    res = system("clear");
                }
                // bye bye! See you soon!
                std::cout << "Hope to see you soon, adventurer!\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(1800));
                break;
        }

    // until you want to quit
    } while (choice != 2);

    return 0;
}

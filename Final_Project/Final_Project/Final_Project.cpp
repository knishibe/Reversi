// Final_Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Reversi.h"
#include <iostream>
using namespace std;

int main()
{
    char choice = NULL;
    Reversi* game = new Reversi();
    while (choice != 'y' && choice != 'n') {
        cout << "Would you like to go first? (y/n): ";
        cin >> choice;
    }

    int computer = 0;
    (choice == 'y') ? computer = 2 : computer = 1;

    if (computer == 1) {
        cout << "Computer Goes First! You are WHITE\n";
    }
    else {
        cout << "You Go First! You are BLACK\n";
    }

    cout << "\n";
    game->display_moves();
    while (!game->terminate()) {
        if (game->getPlayer() == computer) {
            game->computer_turn(false, false, false);
            game->display_board();
        }
        else {
            game->human_turn();
            game->display_board();
        }
        game->change_turn();
    }
    return 0;
}

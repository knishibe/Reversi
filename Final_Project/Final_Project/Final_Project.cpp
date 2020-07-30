// Final_Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Reversi.h"
#include <iostream>
using namespace std;

int main()
{
    char choice = NULL;
    while (choice != 'y' && choice != 'n') {
        cout << "Would you like to go first? (y/n): ";
        cin >> choice;
    }

    int player = 0;
    (choice == 'y') ? player = 2 : player = 1;
    Reversi* game = new Reversi(player);

    cout << "\n";
    game->display_moves();
    while (!game->terminate()) {
        if (game->getPlayer() == 1) {
            game->computer_turn(false, false, false);
            game->display_board();
        }
        else {
            game->human_turn();
            game->display_board();
        }
    }
    return 0;
}

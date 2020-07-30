// Final_Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Reversi.h"
#include <iostream>
using namespace std;

int main()
{
    Reversi* game = new Reversi();
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

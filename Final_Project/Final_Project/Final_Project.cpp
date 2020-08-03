// Final_Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Reversi.h"
#include <iostream>
using namespace std;

int main()
{
    /*char version = NULL;
    cout << "1. Play with Version 1 (MCTS - random playouts)\n";
    cout << "2. Play with Version 2 (MCTS - with heuristics)\n";
    cout << "3. Observe a computer played game between Versions 1 and 2\n\n";
  
    while (version != '1' && version != '2' && version != '3') {
        cout << "Please choose one of the options (1,2,3): ";
        cin >> version;
    }

    if (version == '1' || version == '2') {
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

        while (!game->terminate()) {
            if (game->getPlayer() == computer) {
                version == 1 ? game->computer_turn(false) : game->computer_turn(true);
                game->display_board();
            }
            else {
                game->human_turn();
                game->display_board();
            }
            game->change_turn();
        }
    }
    else {
        Reversi* game = new Reversi();
        int computer = 1;

        game->display_moves();
        while (!game->terminate()) {
            if (game->getPlayer() == computer) {
                game->computer_turn(true);
                game->display_board();
            }
            else {
                game->computer_turn(false);
                game->display_board();
            }
            game->change_turn();
        }
    }*/

    // Test Run 50 games to compare Versions
    int v1_Wins = 0;
    int v2_Wins = 0;
    int ties = 0;
    for (int i = 0; i < 25; i++) {
        Reversi* game = new Reversi();
        int computer = 1;
        
        game->display_moves();
        while (!game->terminate()) {
            if (game->getPlayer() == computer) {
                game->computer_turn(true);
                game->display_board();
            }
            else {
                game->computer_turn(false);
                game->display_board();
            }
            game->change_turn();
        }
        game->change_turn();
        int win = game->checkWin();
        if (win == 1) {
            v1_Wins++;
        }
        else if (win == 0) {
            v2_Wins++;
        }
        else {
            ties++;
        }
    }
    cout << "V1 Wins: " << v1_Wins << endl;
    cout << "V2 Wins: " << v2_Wins << endl;
    cout << "Ties: " << ties << endl;

    return 0;
}

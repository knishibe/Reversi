// ====================================================================================================
// Final_Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
// ====================================================================================================

#include "Reversi.h"
#include <iostream>
using namespace std; 

int main()
{
    char version = NULL;
    cout << "1. Play with Version 1 (MCTS - random playouts)\n";
    cout << "2. Play with Version 2 (MCTS - with heuristics)\n";
    cout << "3. Observe a computer played game between Versions 1 and 2\n\n";
  
    while (version != '1' && version != '2' && version != '3') {
        cout << "Please choose one of the options (1,2,3): ";
        cin >> version;
    }

    // Computer vs Human
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
        game->display_board();
        while (!game->terminate()) {
            if (game->getPlayer() == computer) {
                cout << "Computer's Turn...\n";
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
    // Computer Version 1 vs Computer Version 2
    else{ 
        Reversi* game = new Reversi();
        int computer = 1;

        game->display_board();
        while (!game->terminate()) {
            cout << "Computer V" << game->getPlayer() % 2 + 1 << "'s Turn...\n";
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
    }

     //Test Run 50 games to compare Computer versions 1 and 2
     //To run, please comment out the code block above and uncomment the code block below
     //========================================================================================
    //int v1_Wins = 0;
    //int v2_Wins = 0;
    //int ties = 0;
    //vector<tuple<int, int>> won_by;
    //tuple<int, int, int> win_results;
    //for (int i = 0; i < 50; i++) {
    //    Reversi* game = new Reversi();
    //    int computer = 1;
    //    
    //    game->display_board();
    //    while (!game->terminate()) {
    //        cout << "Computer V" << game->getPlayer()%2+1 << "'s Turn...\n"; 
    //        if (game->getPlayer() == computer) { 
    //            game->computer_turn(true); // Heuristic = Player 1
    //            game->display_board();
    //        }
    //        else {
    //            game->computer_turn(false); // Pure Random Playouts = Player 2
    //            game->display_board();
    //        }
    //        game->change_turn();
    //    }
    //    game->change_turn();
    //    
    //    win_results = game->checkWin();
    //    int win = get<0>(win_results);
    //    int player = game->getPlayer();
    //    if ((player == 1 && win == 1) || (player == 2 && win == 0)) {
    //        v2_Wins++;
    //        won_by.push_back(make_tuple(1, abs(get<1>(win_results) - get<2>(win_results))));
    //    }
    //    else if ((player == 2 && win == 1) || (player == 1 && win == 0)) {
    //        v1_Wins++;
    //        won_by.push_back(make_tuple(2, abs(get<2>(win_results) - get<1>(win_results))));
    //    }
    //    else {
    //        ties++;
    //    }
    //}
    //cout << "V1 Wins: " << v1_Wins << endl;
    //cout << "V2 Wins: " << v2_Wins << endl;
    //cout << "Ties: " << ties << endl;
    //cout << "\n\n";
    //for (int i = 0; i < won_by.size(); i++) {
    //    cout << "Game: " << i << "\n";
    //    cout << "Winner: " << get<0>(won_by[i]) << "\n";
    //    cout << "Won by: " << get<1>(won_by[i]) << "\n\n";
    //}

    //return 0;
}

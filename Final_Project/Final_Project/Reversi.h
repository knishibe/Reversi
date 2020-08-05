// =================================================================================
//									Reversi Class .h
// =================================================================================

#include <iostream>
#include <tuple>
#include <vector>
#include <stdio.h>

using namespace std;

const int BOARD_SIZE = 8;

class Reversi {

public:
	Reversi();
	int getPlayer();
	void display_board();
	void computer_turn(bool static_weight_Heuristic);
	tuple<int, int, int> checkWin();
	void human_turn();
	void change_turn();
	bool terminate();

protected:
	int board[BOARD_SIZE][BOARD_SIZE] = { 0 };
	int player;
	bool game_terminate;
	char first; 
	int no_valid_moves;
	tuple<int, int, int> checkWin(int game_board[8][8], int turn);
	void flip(int square);
	void flip(int square, int game_board[8][8], int turn);
	void display_moves();
	vector<int> possible_moves();
	vector<int> possible_moves(int game_board[8][8], int turn);
	tuple<int, int> nextSpot(tuple<int, int> currentSpot, string direction);
	vector<tuple<int, int>> find_pieces(int game_board[8][8]);
	int best_static_weight_move(vector<int> moves); // Heuristic function
	int pure_move(vector<int> moves); // Choose random move
	tuple<int, int, int> playouts(int move, bool static_weight_heuristic, float time_per_move);
};

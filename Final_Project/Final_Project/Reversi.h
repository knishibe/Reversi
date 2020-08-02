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
	int checkWin();
	int checkWin(int game_board[8][8], int turn);
	void flip(int square);
	void flip(int square, int game_board[8][8], int turn);
	void display_board();
	void display_moves();
	void computer_turn(bool static_weight_Heuristic);
	void human_turn();
	void change_turn();
	bool terminate();

	tuple<int, int, int> randomPlayouts(int move);
	tuple<int, int, int> static_weight_Playouts(int move);

	int capture_corners_heuristic();

protected:
	int board[BOARD_SIZE][BOARD_SIZE] = { 0 };
	int player;
	bool game_terminate;
	char first; 
	int no_valid_moves;
	//int heuristic();
	vector<int> possible_moves();
	vector<int> possible_moves(int game_board[8][8], int turn);
	tuple<int, int> nextSpot(tuple<int, int> currentSpot, string direction);
	vector<tuple<int, int>> find_pieces(int game_board[8][8]);
};


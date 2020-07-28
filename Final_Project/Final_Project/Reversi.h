#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

const int BOARD_SIZE = 8;

class Reversi {

public:
	Reversi();
	int getPlayer();
	bool checkWin();
	bool checkWin(int game_board[8][8]);
	void flip(int square);
	void flip(int square, int game_board[8][8]);
	void display_board();
	void display_moves();
	void computer_turn(bool withHeuristic); 
	void human_turn();
	void change_turn();

protected:
	int board[BOARD_SIZE][BOARD_SIZE] = { 0 };
	int turn;
	int player;
	//int heuristic();
	//tuple<int, int, int> randomPlayouts(int move); //Emily
	vector<int> possible_moves();
	vector<int> possible_moves(int game_board[8][8]);
	tuple<int, int> nextSpot(tuple<int, int> currentSpot, string direction);
	vector<tuple<int, int>> find_pieces(int game_board[8][8]);
};


#include <stdio.h>
#include <tuple>
#include <vector>

using namespace std;

const int BOARD_SIZE = 8;

class Reversi {

public:
	Reversi();
	bool checkWin(int player);
	void flip();
	void display_board();
	void display_moves();
	void computer_turn(bool withHeuristic); 
	void human_turn();
	void change_turn();

protected:
	int board[BOARD_SIZE][BOARD_SIZE] = { 0 };
	int turn;
	int heuristic();
	tuple<int, int, int> randomPlayouts(int move); //Emily
	vector<int> possible_moves();
};


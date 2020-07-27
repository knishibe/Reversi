#include <stdio.h>
#include <tuple>
#include <vector>

using namespace std;

class Reversi {

public:
	Reversi();
	bool checkWin();
	void flip();
	void display_board();
	void display_moves();
	void computer_turn(bool withHeuristic); 
	void human_turn();
	void change_turn();

protected:
	int board[8][8];
	int turn;
	int heuristic();
	tuple<int, int, int> randomPlayouts(int move); //Emily
	vector<int> possible_moves();
};


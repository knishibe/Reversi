#include "Reversi.h"

Reversi::Reversi() {
	board[3][3] = 1;
	board[3][4] = 2;
	board[4][3] = 2;
	board[4][4] = 1;
	turn = 1;
	return;
}

bool Reversi::checkWin(int player) {
	int one = 0;
	int two = 0;

	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (board[i][j] == 1) {
				one++
			} else if(board[i][j] == )
		}
	}
}

void Reversi::flip() {

}

void Reversi::display_board() {

}

void Reversi::display_moves() {

}

void Reversi::computer_turn(bool withHeuristic) {

}

void Reversi::human_turn() {

}

void Reversi::change_turn() {

}

int Reversi::heuristic() {

}

tuple<int, int, int> Reversi::randomPlayouts(int move) {

}

vector<int> Reversi::possible_moves() {

}
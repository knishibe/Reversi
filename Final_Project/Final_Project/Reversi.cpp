#include "Reversi.h"

Reversi::Reversi() {
	board[3][3] = 1;
	board[3][4] = 2;
	board[4][3] = 2;
	board[4][4] = 1;
	player = 1;
	return;
}

int Reversi::getPlayer() { 
	return player; 
}

bool Reversi::checkWin() {
	return checkWin(board);
}

bool Reversi::checkWin(int game_board[8][8]) {
	int squares = 0;

	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (game_board[i][j] == player) {
				squares++;
			}
		}
	}

	if (squares > (BOARD_SIZE * BOARD_SIZE / 2)) {
		return true;
	} else {
		return false;
	}

}

void Reversi::flip(int square) {
	flip(square, board);
	return;
}

void Reversi::flip(int square, int game_board[8][8]) {
	int current_row = (square-1)/8;
	int current_column = (square-1) % 8;
	int row = 0;
	int column = 0;
	tuple<int, int> next_square;
	bool opposite_player = false;
	bool flip = false;
	string directions[] = { "up", "down", "left", "right", "upper_right", "upper_left", "lower_right", "lower_left" };

	for (int i = 0; i < sizeof(directions) / sizeof(directions[0]); i++) {
		row = current_row;
		column = current_column;
		flip = false;
		opposite_player = false;
		while (true) {
			next_square = nextSpot(make_tuple(row, column), directions[i]);
			row = get<0>(next_square);
			column = get<1>(next_square);
			if (board[row][column] == player && opposite_player == true) {
				flip = true;
				break;
			}
			else if (board[row][column] == (player % 2) + 1) {
				opposite_player = true;
			}
			else {
				break;
			}
		}
		if (flip) {
			next_square = nextSpot(make_tuple(current_row, current_column), directions[i]);
			current_row = get<0>(next_square);
			current_column = get<1>(next_square);
			board[current_row][current_column] = player;
			while (!(current_row == row && current_column == column)) {
				next_square = nextSpot(make_tuple(current_row, current_column), directions[i]);
				current_row = get<0>(next_square);
				current_column = get<1>(next_square);
				board[current_row][current_column] = player;
			}
		}

	}

}

void Reversi::display_board() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			cout << " ";
			if (board[i][j] == 1) {
				cout << " W";
			} else if (board[i][j] == 2) {
				cout << " B";
			} else {
				cout << "  ";
			}
			if (j != BOARD_SIZE - 1) {
				cout << " |";
			}
		}
		cout << "\n";
		if (i != BOARD_SIZE - 1) {
			cout << "---------------------------------------\n";
		} 
	}
}

void Reversi::display_moves() {
	vector<int> moves = possible_moves();
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			cout << " ";
			if (board[i][j] == 1) {
				cout << " W";
			}
			else if (board[i][j] == 2) {
				cout << " B";
			}
			else if (find(moves.begin(), moves.end(), i * 8 + j + 1) != moves.end() && i * 8 + j + 1 < 9) {
				cout << " " << i * 8 + j + 1;
			}
			else if (find(moves.begin(), moves.end(), i * 8 + j + 1) != moves.end() && i * 8 + j + 1 > 9) {
				cout << i * 8 + j + 1;
			}
			else {
				cout << "  ";
			}
			if (j != BOARD_SIZE - 1) {
				cout << " |";
			}
		}
		cout << "\n";
		if (i != BOARD_SIZE - 1) {
			cout << "---------------------------------------\n";
		}
	}
}

void Reversi::computer_turn(bool withHeuristic) {

}

void Reversi::human_turn() {
	int square = 0;
	int row = 0;
	int column = 0;
	cout << "The following are legal moves\n";
	display_moves();
	cout << "Please select the square you would like to play: ";
	cin >> square;
	row = (square - 1) / 8;
	column = (square - 1) % 8;
	board[row][column] = player;
}

void Reversi::change_turn() {
	player = (player % 2) + 1;
}

//int Reversi::heuristic() {
//
//}
//
//tuple<int, int, int> Reversi::randomPlayouts(int move) {
//
//}


vector<int> Reversi::possible_moves() {
	return possible_moves(board);
}

vector<int> Reversi::possible_moves(int game_board[8][8]) {
	vector<int> moves;
	vector<tuple<int, int>> pieces = find_pieces(game_board);
	tuple<int, int> square;
	bool opposite_player;
	string directions[] = {"up", "down", "left", "right", "upper_right", "upper_left", "lower_right", "lower_left"};
	int current_row = 0;
	int current_column = 0;
	int row = 0;
	int column = 0;
	for(auto& i : pieces)  {
		current_row = get<0>(i);
		current_column = get<1>(i);
		for (int j = 0; j < sizeof(directions)/sizeof(directions[0]); j++) {
			row = current_row;
			column = current_column;
			opposite_player = false;
			while (true) {
				square = nextSpot(make_tuple(row, column), directions[j]);
				row = get<0>(square);
				column = get<1>(square);
				if (board[row][column] == 0 && opposite_player == true) {
					moves.push_back(row * 8 + column + 1);
					break;
				} else if (board[row][column] == (player % 2) + 1) {
					opposite_player = true;
				} else {
					break;
				}
			}

		}
	}

	return moves;
}

tuple<int, int> Reversi::nextSpot(tuple<int, int> currentSpot, string direction) {
	int i = get<0>(currentSpot);
	int j = get<1>(currentSpot);

	if (direction == "up") {
		if (i - 1 >= 0) {
			return make_tuple(i - 1, j);
		}
	} else if (direction == "down") {
		if (i + 1 < BOARD_SIZE) {
			return make_tuple(i + 1, j);
		}
	} else if (direction == "left") {
		if (j - 1 >= 0) {
			return make_tuple(i, j - 1);
		}
	} else if (direction == "right") {
		if (j + 1 < BOARD_SIZE) {
			return make_tuple(i, j + 1);
		}
	} else if (direction == "upper_right") {
		if (i + 1 < BOARD_SIZE && j + 1 < BOARD_SIZE) {
			return make_tuple(i + 1, j + 1);
		}
	} else if (direction == "upper_left") {
		if (i + 1 < BOARD_SIZE && j - 1 >= 0) {
			return make_tuple(i + 1, j - 1);
		}
	} else if (direction == "lower_right") {
		if (i - 1 >= 0 && j + 1 < BOARD_SIZE) {
			return make_tuple(i - 1, j + 1);
		}
	} else if (direction == "lower_left") {
		if (i - 1 >= 0 && j - 1 >= 0) {
			return make_tuple(i - 1, j - 1);
		}
	}
	return make_tuple(NULL, NULL);
}

vector<tuple<int, int>> Reversi::find_pieces(int game_board[8][8]) {
	vector<tuple<int, int>> pieces;
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (game_board[i][j] == player) { 
				pieces.push_back(make_tuple(i, j));
			}
		}
	}
	return pieces;
}
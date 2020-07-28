#include "Reversi.h"
#include <algorithm>
#include <iostream>
#include <ctime>
#include <map>
using namespace std;

Reversi::Reversi() {
	board[3][3] = 1;
	board[3][4] = 2;
	board[4][3] = 2;
	board[4][4] = 1;
	player = 1;
	game_terminate = false;
	return;
}

int Reversi::getPlayer() { 
	return player; 
}

bool Reversi::checkWin() {
	return checkWin(board, player);
}

bool Reversi::terminate() {
	return game_terminate;
}

bool Reversi::checkWin(int game_board[8][8], int turn) {
	int squares = 0;

	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (game_board[i][j] == turn) {
				squares++;
			}
		}
	}

	if (squares > (BOARD_SIZE * BOARD_SIZE / 2)) {
		return true;
		game_terminate = true;
	} else {
		return false;
	}
}

void Reversi::flip(int square) {
	flip(square, board, player);
	return;
}

void Reversi::flip(int square, int game_board[8][8], int turn) {
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
			if (board[row][column] == turn && opposite_player == true) {
				flip = true;
				break;
			}
			else if (board[row][column] == (turn % 2) + 1) {
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
			board[current_row][current_column] = turn;
			while (!(current_row == row && current_column == column)) {
				next_square = nextSpot(make_tuple(current_row, current_column), directions[i]);
				current_row = get<0>(next_square);
				current_column = get<1>(next_square);
				board[current_row][current_column] = turn;
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
	cout << "\n\n\n";
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
	cout << "\n\n\n";
}

void Reversi::computer_turn(bool capture_Corners_Heuristic, bool stability_Heuristic, bool corners_and_stability_Heuristic) {
	map<int, int> results;
	int next_move = 0;
	
	if (capture_Corners_Heuristic) {

	}
	else if (stability_Heuristic) {

	}
	else if (corners_and_stability_Heuristic) {

	}
	else {
		vector<int> moves = possible_moves();
		for (int i=0; i<moves.size(); i++){
			tuple<int, int, int> stat = randomPlayouts(moves[i]);
			results[moves[i]] = get<1>(stat); // can modify equation 
		}
		
		// get move resulting in the smallest amount of ties
		int next_move = results.begin()->first;
		int min_Ties = results.begin()->second;
		int test_move = 0;
		map<int, int>::iterator it;
		for (it = results.begin(); it != results.end(); it++)
		{
			test_move = it->second; // get dict value
			if (test_move < min_Ties) {
				min_Ties = test_move;
				next_move = it->first;
			}
		}

		board[(next_move - 1) / BOARD_SIZE][(next_move - 1) % BOARD_SIZE] = player;
		flip(next_move);
		change_turn();
	}
}

// Returns the move with the highest corner heuristic value
int Reversi::capture_corners_heuristic() {
	//int computer_score = 0;
	//vector<int> moves = possible_moves();
	//vector<pair<int, int>> move_coord;
	//
	//// Create a vector of move coordinates
	//for (int i = 0; i < moves.size(); i++) {
	//	int row = (moves[i] - 1) / 8;
	//	int column = (moves[i] - 1) % 8;
	//	move_coord.push_back(pair<int, int>(row, column));
	//}

	//// Score captured corners
	//if (board[0][0] != 0 || board[0][7] != 0 || board[7][0] != 0 || board[7][7] != 0) {
	//	(board[0][0] == 1) ? computer_score += 4 : computer_score;
	//	(board[0][7] == 1) ? computer_score += 4 : computer_score;
	//	(board[7][0] == 1) ? computer_score += 4 : computer_score;
	//	(board[7][7] == 1) ? computer_score += 4 : computer_score;
	//}

	//// Check if corners can be partially captured
	//for (int i = 0; i < move_coord.size(); i++) {
	//	if (move_coord[i].first == 0 and move_coord[i].second == 0) {
	//		computer_score += 2;
	//	}
	//	if (move_coord[i].first == 0 and move_coord[i].second == 7) {
	//		computer_score += 2;
	//	}
	//	if (move_coord[i].first == 7 and move_coord[i].second == 0) {
	//		computer_score += 2;
	//	}
	//	if (move_coord[i].first == 7 and move_coord[i].second == 7) {
	//		computer_score += 2;
	//	}
	//}

	return 0;
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
	flip(square);
	change_turn();
}

void Reversi::change_turn() {
	player = (player % 2) + 1;
}

//int Reversi::heuristic() {
//
//}
//


tuple<int, int, int> Reversi::randomPlayouts(int move) {
	int wins = 0;
	int ties = 0;
	int losts = 0;

	int col = (move - 1) % BOARD_SIZE;
	int row = (move - 1) / BOARD_SIZE;

	int turn = 0;

	srand(time(nullptr));

	for (int i = 0; i < 10000; i++) {
		// Create simulation board
		int sim_board[BOARD_SIZE][BOARD_SIZE] = { 0 };
		copy(&board[0][0], &board[0][0] + BOARD_SIZE * BOARD_SIZE, &sim_board[0][0]);

		// Computers makes the theoretical move
		sim_board[row][col] = 1;
		turn = 0; // player's turn

		vector<int> moves = possible_moves(sim_board, turn);
		bool win = false;

		while (moves.size() > 0) {
			int index = rand() % moves.size();
			int nextMove = moves[index];

			if (turn == 1) {
				sim_board[(nextMove - 1) / BOARD_SIZE][(nextMove - 1) % BOARD_SIZE] = 1;
				flip(nextMove, sim_board, 1);
			}
			else {
				sim_board[(nextMove - 1) / BOARD_SIZE][(nextMove - 1) % BOARD_SIZE] = 0;
				flip(nextMove, sim_board, 0);
			}

			win = checkWin(sim_board, turn);
			if (win and turn == 1) {
				wins += 1;
				break;
			}
			else if (win and turn == 0) {
				losts += 1;
				break;
			}

			(turn == 0) ? turn = 1 : turn = 0;
			moves = possible_moves(sim_board, turn);
		}

		if (!win and moves.size() == 0) {
			ties += 1;
		}
	}
	return tie(wins, ties, losts);
}

vector<int> Reversi::possible_moves() {
	return possible_moves(board, player);
}

vector<int> Reversi::possible_moves(int game_board[8][8], int turn) {
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
				} else if (board[row][column] == (turn % 2) + 1) {
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
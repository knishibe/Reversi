#include "Reversi.h"
#include <algorithm>
#include <iostream>
#include <ctime>
#include <map>
#include <iomanip>
using namespace std;

Reversi::Reversi() {
	board[3][3] = 2;
	board[3][4] = 1;
	board[4][3] = 1;
	board[4][4] = 2;
	player = 1;
	game_terminate = false;

	cout << "\n==================================================================\n\n";
	cout << setw(37)<< "REVERSI\n\n";
	cout << "==================================================================\n\n";
	return;
}

int Reversi::getPlayer() { 
	return player; 
}

tuple<int, int, int> Reversi::checkWin() {
	return checkWin(board, player);
}

bool Reversi::terminate() {
	return game_terminate;
}

tuple<int, int, int> Reversi::checkWin(int game_board[8][8], int turn) {
	int player = 0;
	int opponent = 0;

	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (game_board[i][j] == turn) {
				player++;
			}
			else if (game_board[i][j] == (turn%2)+1) {
				opponent++;
			}
		}
	}

	if (player > opponent) {
		return make_tuple(1, player, opponent);
		game_terminate = true;
	} 
	else if (player == opponent) {
		return make_tuple(2, player, opponent);
	}
	else {
		return make_tuple(0, player, opponent);
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
	int flip_row = 0;
	int flip_column = 0;
	int counter = 0;
	tuple<int, int> next_square;
	bool opposite_player = false;
	bool flip = false;
	string directions[] = { "up", "down", "left", "right", "upper_right", "upper_left", "lower_right", "lower_left" };

	for (int i = 0; i < sizeof(directions) / sizeof(directions[0]); i++) {
		row = current_row;
		column = current_column;
		flip = false;
		counter = 0;
		opposite_player = false;
		while (true) {
			next_square = nextSpot(make_tuple(row, column), directions[i]);
			row = get<0>(next_square);
			column = get<1>(next_square);
			if (game_board[row][column] == turn && opposite_player == true) {
				flip = true;
				break;
			}
			else if (game_board[row][column] == (turn % 2) + 1) {
				opposite_player = true;
				counter++;
			}
			else {
				break;
			}
		}
		if (flip) {
			next_square = nextSpot(make_tuple(current_row, current_column), directions[i]);
			flip_row = get<0>(next_square);
			flip_column = get<1>(next_square);
			game_board[flip_row][flip_column] = turn;
			counter--;
			for(counter; counter > 0; counter--) {
				next_square = nextSpot(make_tuple(flip_row, flip_column), directions[i]);
				flip_row = get<0>(next_square);
				flip_column = get<1>(next_square);
				game_board[flip_row][flip_column] = turn;
			}
		}
	}
}

void Reversi::display_board() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			cout << " ";
			if (board[i][j] == 1) {
				cout << " B";
			} else if (board[i][j] == 2) {
				cout << " W";
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
				cout << " B";
			}
			else if (board[i][j] == 2) {
				cout << " W";
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
	cout << "\n\n";
}

void Reversi::computer_turn(bool static_weight_Heuristic) {
	map<int, int> results;

	if (no_valid_moves >= 2) {
		tuple<int, int, int> win_results = checkWin();
		int win = get<0>(win_results);
		if (win == 1) {
			cout << "Player " << player << " won ";
			cout << get<1>(win_results) << ":" << get<2>(win_results) << " !\n";
		}
		else if (win == 0) {
			cout << "Player " << (player%2)+1 << " won ";
			cout << get<2>(win_results) << ":" << get<1>(win_results) << " !\n";
		}
		else {
			cout << "Tie!\n";
		}
		game_terminate = true;
		return;
	}

	vector<int> moves = possible_moves();
	if (moves.empty()) {// no valid moves. Change turn
		cout << "No valid moves available\n";
		no_valid_moves++;
		return;
	}
	no_valid_moves = 0;

	moves.clear();
	moves = possible_moves();
	float time_per_move = 5.0 / (moves.size());
		
	if (static_weight_Heuristic) {
		for (int i = 0; i < moves.size(); i++) {
			tuple<int, int, int> stat = playouts(moves[i], true, time_per_move);
			results[moves[i]] = get<1>(stat); // can modify equation 
		}
	}
	else { // pure random playouts
		for (int i = 0; i < moves.size(); i++) {
			tuple<int, int, int> stat = playouts(moves[i], false, time_per_move);
			results[moves[i]] = get<1>(stat); // can modify equation
		}
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
}


void Reversi::human_turn() {
	int square = 0;
	int row = 0;
	int column = 0;
	bool valid_move = false;
	cout << "User's Turn...\n";

	if (no_valid_moves >= 2) {
		tuple<int, int, int> win_results = checkWin();
		int win = get<0>(win_results);
		if (win == 1) {
			cout << "Player " << player << " won ";
			cout << get<1>(win_results) << ":" << get<2>(win_results) << " !\n";
		}
		else if (win == 0) {
			cout << "Player " << (player % 2) + 1 << " won ";
			cout << get<2>(win_results) << ":" << get<1>(win_results) << " !\n";
		}
		else {
			cout << "Tie!\n";
		}
		game_terminate = true;
		return;
	}

	while (!valid_move) {
		vector<int> moves = possible_moves();
		if (moves.empty()) {// no valid moves. Change turn
			cout << "No valid moves available\n";
			no_valid_moves++;
			return;
		}
		no_valid_moves = 0;
		cout << "The numbered squares below are the possible moves that you can make.\n\n";
		display_moves();
		cout << "Please select the square you would like to play: ";

		if (cin >> square && find(moves.begin(), moves.end(), square) != moves.end()) {
			valid_move = true;
		}
		else {
			if (!cin.eof()) {
				cin.clear();
				cin.ignore();
			}
			cout << "\nERROR: The square that you have chosen is not valid. Please select a valid move.\n";
		}
	}

	row = (square - 1) / 8;
	column = (square - 1) % 8;
	board[row][column] = player;
	flip(square);
}

void Reversi::change_turn() {
	player = (player % 2) + 1;
}

tuple<int, int, int> Reversi::playouts(int move, bool static_weight_heuristic, float time_per_move) {
	int wins = 0;
	int ties = 0;
	int losts = 0;

	int col = (move - 1) % BOARD_SIZE;
	int row = (move - 1) / BOARD_SIZE;

	int turn = 0;

	int i = 0;
	time_t start_time = time(NULL);

	while (difftime(time(NULL), start_time) < time_per_move) {
		// Create simulation board
		int sim_board[BOARD_SIZE][BOARD_SIZE] = { 0 };
		copy(&board[0][0], &board[0][0] + BOARD_SIZE * BOARD_SIZE, &sim_board[0][0]);
		turn = getPlayer();

		// Computers makes the theoretical move
		sim_board[row][col] = turn;
		turn = (turn % 2) + 1; // player's turn

		vector<int> moves = possible_moves(sim_board, turn);
		bool win = false;

		int no_valid_moves = 0;
		while (moves.empty() && no_valid_moves < 2) {
			no_valid_moves++;
			turn = (turn % 2) + 1;
			moves.clear();
			moves = possible_moves(sim_board, turn);
		}

		while (moves.size() > 0 && no_valid_moves < 2) {
			int nextMove = 0;
			if (static_weight_heuristic) {
				nextMove = best_static_weight_move(moves);
			}
			else {
				nextMove = pure_move(moves);
			}

			if (turn == 1) {
				sim_board[(nextMove - 1) / BOARD_SIZE][(nextMove - 1) % BOARD_SIZE] = 1;
				flip(nextMove, sim_board, 1);
			}
			else {
				sim_board[(nextMove - 1) / BOARD_SIZE][(nextMove - 1) % BOARD_SIZE] = 2;
				flip(nextMove, sim_board, 2);
			}

			(turn == 2) ? turn = 1 : turn = 2;
			moves.clear();
			moves = possible_moves(sim_board, turn);

			int no_valid_moves = 0;
			// Player has no valid moves. Change turn. Only exit the outer while loop if 
			// there are no valid moves two turns in a row.
			while (moves.empty() && no_valid_moves < 2) {
				no_valid_moves++;
				(turn == 2) ? turn = 1 : turn = 2;
				moves.clear();
				moves = possible_moves(sim_board, turn);
			}

			if (no_valid_moves >= 2) {
				break;
			}
		}

		win = get<0>(checkWin(sim_board, turn));
		if (win == 1 && turn == 1) {
			wins += 1;
		}
		else if (win == 1 && turn == 2) {
			losts += 1;
		}
		else {
			ties += 1; // no win or loss
		}
		i++;
	}
	return tie(wins, ties, losts);
}

int Reversi::best_static_weight_move(vector<int> moves) {
	const int STATIC_WEIGHT_1[8][8] = { { 4,-3, 2, 2, 2, 2,-3, 4},
										{-3,-4,-1,-1,-1,-1,-4,-3},
										{ 2,-1, 1, 0, 0, 1,-1, 2},
										{ 2,-1, 0, 1, 1, 0,-1, 2},
										{ 2,-1, 0, 1, 1, 0,-1, 2},
										{ 2,-1, 1, 0, 0, 1,-1, 2},
										{-3,-4,-1,-1,-1,-1,-4,-3},
										{ 4,-3, 2, 2, 2, 2,-3, 4} };

	int best_move_score = STATIC_WEIGHT_1[(moves[0] - 1) / BOARD_SIZE][(moves[0] - 1) % BOARD_SIZE];
	int best_index = 0;

	for (int j = 1; j < moves.size(); j++) {
		int r = (moves[j] - 1) / BOARD_SIZE;
		int c = (moves[j] - 1) % BOARD_SIZE;
		if (STATIC_WEIGHT_1[r][c] > best_move_score) {
			best_move_score = STATIC_WEIGHT_1[r][c];
			best_index = j;
		}
	}
	int nextMove = moves[best_index];
	return nextMove;
}

int Reversi::pure_move(vector<int> moves) {
	srand(time(nullptr));
	int index = rand() % moves.size();
	int nextMove = moves[index];
	return nextMove;
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
	int move = 0;
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
				if (row == -1 || column == -1) {
					break; // no more moves
				}
				else if (game_board[row][column] == 0 && opposite_player == true) {
					move = row * 8 + column + 1;
					if (find(moves.begin(), moves.end(), move) == moves.end()) {
						moves.push_back(move);
					}
					break;
				} 
				else if (game_board[row][column] == (turn % 2) + 1) {
					opposite_player = true;
				} 
				else {
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
		if (i - 1 >= 0 && j + 1 < BOARD_SIZE) {
			return make_tuple(i - 1, j + 1);
		}
	} else if (direction == "upper_left") {
		if (i - 1 >= 0 && j - 1 >= 0) {
			return make_tuple(i - 1, j - 1);
		}
	} else if (direction == "lower_right") {
		if (i + 1 < BOARD_SIZE && j + 1 < BOARD_SIZE) {
			return make_tuple(i + 1, j + 1);
		}
	} else if (direction == "lower_left") {
		if (i + 1 < BOARD_SIZE && j - 1 >= 0) {
			return make_tuple(i + 1, j - 1);
		}
	}
	return make_tuple(-1, -1);
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
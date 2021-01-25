#include <iostream>
#include <vector>
#include <array>
#include <exception>

struct move {
	int r, c, score;
};

struct TicTacToe {
	char player{}, computer{};

	std::vector<std::vector<char>> grid;
	//char grid[3][3]{};

	TicTacToe() {

		grid = std::vector<std::vector<char>>(3, std::vector<char>(3, ' '));
		//for(int i = 0; i < 3; i++)
		//	for(int j = 0; j < 3; j++)
		//		grid[i][j] = ' ';

	}

	bool win() {

		//	Winning configurations:
		int win_statess[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};
		//		\/ \/ \/		//	slower
		//std::vector<std::vector<int>> win_states = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};

		for(int i = 0; i < 3; i++) {
			int first_r = win_statess[i][0] / 3;
			int first_c = win_statess[i][0] % 3;
		//		\/ \/ \/		//	slower
		//for(auto i : win_states) {
		//	int first_r = i[0] / 3;
		//	int first_c = i[0] % 3;

			bool win = true;	// Let's assume that there's win, and if there is a contradiction (dowod nie w prost), change it to flalse
			
			for(int j = 0; j < 3; j++) {
				int r = win_statess[i][j] / 3;
				int c = win_statess[i][j] % 3;
			//		\/ \/ \/		// slower
			//for(auto j : i) {
				//int r = j / 3;
				//int c = j % 3;

				//	If the first element in a configuration is empty
				//		or if elements in a configuration are
				//		not the same, than there's no win:
				if (grid[first_r][first_c] == ' '
					|| grid[first_r][first_c] != grid[r][c]) {
					win = false;
				}
			}
			if (win)
				return true;
		}
		return false;
	}

	bool tie() {
		if(win())
			return false;
		for(int i = 0; i < 3; i++) {
			for(int j = 0; j < 3; j++) {
				if(grid[i][j] == ' ') {
					return false;
				}
			}
		}
	//		\/ \/ \/		// slower
	//	for (auto i : grid) {
	//		for (auto j :  i) {
	//			if (j == ' ') {
	//				return false;
	//			}
	//		}
	//	}
		return true;
	}

	void player_move() {
		while (true) {
			std::cout << "Enter an empty cell (1 - 9): ";
			int cell;
			try {
				std::cin >> cell;
				//std::cout << cell --> display wha is in the cell
				// cin.fail() --> fail if type is not correct
				// static_cast<int>(cell) != a --> check if a is integer or not
				if(std::cin.fail() || (static_cast<int>(cell) != cell)) {
					std::cout << "\nWrong input. Please enter one integer\n";
					std::cin.clear();
					std::cin.ignore(256, '\n');   // ignore the line change
					//std::cin >> cell;
				}
			} catch(std::exception& e) {
				std::cout << "\nYou entered: " << e.what() << "\nAnd you were ment to enter a number from range 1 to 9\n";
				//player_move();
			}
			int r = (cell - 1) / 3;
			int c = (cell - 1) % 3;
			if (cell >= 1 && cell <= 9 && grid[r][c] == ' ') {
				grid[r][c] = player;
				break;
			} else {
				player_move();
			}
		}
	}

	void computer_move() {
		move best_move = minimax();
		grid[best_move.r][best_move.c] = computer;
	}

	// First we check if the player is maximizing_player;
	//	If you are the maximizing_player then we will try 
	//		to maximize your score, but if y're not then
	//		we want to harm you as much as posible:
	move minimax(bool maximizing_player = true) {
		move best_move;
		if (win()) {
			// If maximizing_player wins we can return 1
			//		and if maximizing_player loses we
			//		returns -1;
			if (maximizing_player) {
				best_move.score = -1;
			} else {
				best_move.score = 1;
			}
			return best_move;
		} else if (tie()) {
			best_move.score = 0;
			return best_move;
		}
		
		best_move.score = maximizing_player ? -2 : 2;
		// -2 and 2 acts just like as -inf and inf

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (grid[i][j] == ' ') {
					//	Ai tries to maximize it's score and player
					//		is tring to minimize AI's score
					grid[i][j] = maximizing_player ? computer : player;
					move board_state = minimax(!maximizing_player);
					if (maximizing_player) {
						//	if the move is better than the move we'd
						//		already found or if we haven't found it yet:
						if (board_state.score > best_move.score) {
							// best move is the found one:
							best_move.score = board_state.score;
							best_move.r = i;
							best_move.c = j;
						}
					} else {
						// if we search for the worst move for player:
						if (board_state.score < best_move.score) {
							best_move.score = board_state.score;
							best_move.r = i;
							best_move.c = j;
						}
					}
					grid[i][j] = ' ';	// reset analised pole
				}
			}
		}
		return best_move;
	}

	void play() {
		while (true) {
			std::cout << "Which symbol (X or O, X goes first)? ";
			std::cin >> player;
			if (player == 'X' || player == 'O'
				|| player == 'x' || player == 'o') {
				break;
			}
		}
		
		if(player == 'x') player = 'X';
		if(player == 'o') player = 'O';
		computer = player == 'X' ? 'O' : 'X';
		
		if (player == 'O') {
			computer_move();
		}
		
		print();
		
		while (true) {
			player_move();
			print();
			
			if (win()) {
				std::cout << "Player wins!\n";
				return;
			} else if (tie()) {
				std::cout << "Tie!\n";
				return;
			}
			
			std::cout << "Computer is making a move...\n";
			computer_move();
			print();
			
			if (win()) {
				std::cout << "Computer wins!\n";
				return;
			} else if (tie()) {
				std::cout << "Tie!\n";
				return;
			}
		}
	}

	void print() {
		std::cout << '\n';
		
		for (int i = 0; i < 3; i++) {
			if (i) {
				std::cout << "-----------\n";
			}
			
			for (int j = 0; j < 3; j++) {
				if (j) std::cout << "|";
				std::cout << ' ';
				
				if (grid[i][j] == ' ') {
					std::cout << 3 * i + j + 1;
				} else {
					std::cout << grid[i][j];
				}
				std::cout << ' ';
			}
			std::cout << '\n';
		}
		std::cout << '\n';
	}
};

int main() {
	TicTacToe game;
	game.play();
}
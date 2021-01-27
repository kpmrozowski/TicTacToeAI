#include "AI.hpp"
#include "Move.hpp"
#include "GameState.hpp"
#include "DEFINITIONS.hpp"

#include <iostream>

using namespace std;

namespace mro {
	AI::AI(int playerPiece, GameDataRef data) {
		this->_data = data;

		this->playerPiece = playerPiece;

		if(O_PIECE == playerPiece) {
			aiPiece = X_PIECE;
		} else {
			aiPiece = O_PIECE;
		}

		checkMatchVector.push_back({0, 2, 1, 2, 2, 2});
		checkMatchVector.push_back({0, 2, 0, 1, 0, 0});
		checkMatchVector.push_back({0, 2, 1, 1, 2, 0});
		checkMatchVector.push_back({2, 2, 1, 2, 0, 2});
		checkMatchVector.push_back({2, 2, 2, 1, 2, 0});
		checkMatchVector.push_back({2, 2, 1, 1, 0, 0});
		checkMatchVector.push_back({0, 0, 0, 1, 0, 2});
		checkMatchVector.push_back({0, 0, 1, 0, 2, 0});
		checkMatchVector.push_back({0, 0, 1, 1, 2, 2});
		checkMatchVector.push_back({2, 0, 2, 1, 2, 2});
		checkMatchVector.push_back({2, 0, 1, 0, 0, 0});
		checkMatchVector.push_back({2, 0, 1, 1, 0, 2});
		checkMatchVector.push_back({0, 1, 1, 1, 2, 1});
		checkMatchVector.push_back({1, 2, 1, 1, 1, 0});
		checkMatchVector.push_back({2, 1, 1, 1, 0, 1});
		checkMatchVector.push_back({1, 0, 1, 1, 1, 2});
		checkMatchVector.push_back({0, 1, 2, 1, 1, 1});
		checkMatchVector.push_back({1, 2, 1, 0, 1, 1});
		checkMatchVector.push_back({0, 2, 2, 0, 1, 1});
		checkMatchVector.push_back({2, 2, 0, 0, 1, 1});
		checkMatchVector.push_back({0, 2, 2, 2, 1, 2});
		checkMatchVector.push_back({0, 0, 2, 0, 1, 0});
		checkMatchVector.push_back({0, 2, 0, 0, 0, 1});
		checkMatchVector.push_back({2, 2, 2, 0, 2, 1});
	}

	void AI::PlacePiece(std::vector<std::vector<int>>& gridArray, sf::Sprite gridPieces[3][3], int& gameState) {
		try {
			Move best_move = minimax(gridArray);
			std::cout << "\nBest move is: (" << best_move.r << ", " << best_move.c << ")";
			if(best_move.r < 3 && best_move.c < 3 && best_move.r > -1 && best_move.c > -1)
				CheckIfPieceIsEmpty(best_move.r, best_move.c, gridArray, gridPieces);

		} catch(int error) {
			switch(error) {
				case -1:
				std:
					cout << "\nthrow -1: 2 pieces match\n";
				case -2:
					std::cout << "\nthrow -2: a piece is empty\n";
			}
		}

		gameState = STATE_PLAYING;
	}

	bool AI::win(std::vector<std::vector<int>>& gridArray) {

		std::vector<std::vector<int>> win_states = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};

		for(auto i : win_states) {
			int first_r = i[0] / 3;
			int first_c = i[0] % 3;

			bool win = true; // Let's assume that there's win, and if there is a contradiction (dowod nie w prost), change it to flalse

			for(auto j : i) {
				int r = j / 3;
				int c = j % 3;

				//	If the first element in a configuration is empty or if elements in a configuration are not the same, than there's no win:
				if(gridArray[first_r][first_c] == -1 || gridArray[first_r][first_c] != gridArray[r][c]) {
					win = false;
				}
			}
			if(win)
				return true;
		}
		return false;
	}

	bool AI::tie(std::vector<std::vector<int>>& gridArray) {
		if(win(gridArray))
			return false;
		for(auto i : gridArray) {
			for(auto j : i) {
				if(j == -1) {
					return false;
				}
			}
		}
		return true;
	}

	// First we check if the player is maximizing_player;
	//	If you are the maximizing_player then we will try to maximize your score, but if y're not then we want to harm you as much as posible:
	Move AI::minimax(std::vector<std::vector<int>>& gridArray, bool maximizing_player) {
		Move best_move;
		if(win(gridArray)) {
			// If maximizing_player wins we can return 1
			//		and if maximizing_player loses we
			//		returns -1;
			if(maximizing_player) {
				best_move.score = -1;
			} else {
				best_move.score = 1;
			}
			return best_move;
		} else if(tie(gridArray)) {
			best_move.score = 0;
			return best_move;
		}

		best_move.score = maximizing_player ? -2 : 2;
		// -2 and 2 acts just like as -inf and inf

		for(int i = 0; i < 3; i++) {
			for(int j = 0; j < 3; j++) {
				if(gridArray[i][j] == -1) {
					//	Ai tries to maximize it's score and player is tring to minimize AI's score
					gridArray[i][j] = maximizing_player ? AI_PIECE : PLAYER_PIECE;
					//print();	uncomment to see AI's analizes
					Move board_state = minimax(gridArray, !maximizing_player);
					if(maximizing_player) {
						//	if the move is better than the move we'd already found or if we haven't found it yet:
						if(board_state.score > best_move.score) {
							// best move is the found one:
							best_move.score = board_state.score;
							best_move.r = i;
							best_move.c = j;
						}
					} else {
						// if we search for the worst move for player:
						if(board_state.score < best_move.score) {
							best_move.score = board_state.score;
							best_move.r = i;
							best_move.c = j;
						}
					}
					gridArray[i][j] = EMPTY_PIECE; // reset analised pole
				}
			}
		}
		return best_move;
	}

	void AI::CheckIfPieceIsEmpty(int X, int Y, std::vector<std::vector<int>>& gridArray, sf::Sprite gridPieces[3][3]) {
		// check if
		if(EMPTY_PIECE == gridArray[X][Y]) {
			gridArray[X][Y] = AI_PIECE;
			gridPieces[X][Y].setTexture(this->_data->assets.GetTexture("O Piece"));

			gridPieces[X][Y].setColor(sf::Color(255, 255, 255, 255));


			throw -2;
		}
	}

}

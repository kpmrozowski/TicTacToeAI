#include "AI.hpp"
#include "Move.hpp"
#include "GameState.hpp"
#include "DEFINITIONS.hpp"

#include <iostream>
#include <algorithm>

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

	void AI::PlacePiece(std::vector<std::vector<int>>& gridArray, sf::Sprite gridPieces[3][3], int& gameState, int turn) {
		try {
			Move best_move;
			movesVect.empty();
			//movesVect.push_back(Move(0));
			if(aiPiece == turn)
				best_move = minimax(gridArray, true);
			else
				best_move = minimax(gridArray, false);
			bestMovesVect.empty();
			bestMovesVect = std::vector<Move>(9, Move(0));
			//std::cout << "\n\nAll posibble AI moves:";
			int licz = 1;
			for(Move move : movesVect) {
				if(gridArray[move.column][move.row] == EMPTY_PIECE) {
					bestMovesVect[move.column + 3 * move.row].score += move.score;
					bestMovesVect[move.column + 3 * move.row].win += move.win;
					bestMovesVect[move.column + 3 * move.row].lose += move.lose;
					bestMovesVect[move.column + 3 * move.row].tie += move.tie;
					bestMovesVect[move.column + 3 * move.row].column = move.column;
					bestMovesVect[move.column + 3 * move.row].row = move.row;
					//std::cout << "\n" << licz << ".\trow = " << move.row+1 << "   column = " << move.column+1 << "   score = " << move.score;
					licz++;
				}
			}
			std::sort(bestMovesVect.begin(), bestMovesVect.end(), [](const auto& lhs, const auto& rhs) {
				return lhs.score > rhs.score;
			});
			
			std::cout << "\n\nBest moves (sorted best to worst):";
			licz = 1;
			for(Move move : bestMovesVect) {
				if(gridArray[move.column][move.row] == EMPTY_PIECE)
					std::cout << "\n|" << move.row + 3 * move.column +1 << "| row=" << move.row+1 << "  column=" << move.column+1 << "  wins=" << move.win << "  tie=" << move.tie << "  lose=" << move.lose << "   score=" << move.score;
				licz++;
			}

			std::cout << "\nBest move is: (r" << best_move.row+1 << ", c" << best_move.column+1 << ")";
			if(best_move.column < 3 && best_move.row < 3 && best_move.column > -1 && best_move.row > -1)
				CheckAndPlace(best_move.row, best_move.column, gridArray, gridPieces, turn);

		} catch(int error) {
			switch(error) {
				case -1:
				std:
					cout << "\nthcolumn -1: 2 pieces match\n";
				case -2:
					std::cout << "\nthcolumn -2: a piece is empty\n";
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
				if(gridArray[first_r][first_c] == EMPTY_PIECE || gridArray[first_r][first_c] != gridArray[r][c]) {
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
				if(j == EMPTY_PIECE) {
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

		for(int i = 2; i >= 0; i--) {
			for(int j = 2; j >= 0; j--) {
				if(gridArray[i][j] == EMPTY_PIECE) {
					//	Ai tries to maximize it's score and player is tring to minimize AI's score
					gridArray[i][j] = maximizing_player ? aiPiece : playerPiece;
					//print(gridArray);	uncomment to see AI's analizes
					Move board_state = minimax(gridArray, !maximizing_player);
					if(maximizing_player) {
						//	if the move is better than the move we'd already found or if we haven't found it yet:
						if(board_state.score > best_move.score) {
							// best move is the found one:
							best_move.score = board_state.score;
							best_move.row = i;
							best_move.column = j;
							best_move.win = best_move.score == 1 ? 1 : 0;
							best_move.lose = best_move.score == -1 ? 1 : 0;
							best_move.tie = best_move.score == 0 ? 1 : 0;
							if(board_state.score != -1)
								movesVect.push_back(board_state);
						}
					} else {
						// if we search for the worst move for player:
						if(board_state.score < best_move.score) {
							best_move.score = board_state.score;
							best_move.row = i;
							best_move.column = j;
							best_move.win = best_move.score == 1 ? 1 : 0;
							best_move.lose = best_move.score == -1 ? 1 : 0;
							best_move.tie = best_move.score == 0 ? 1 : 0;
							if(board_state.score != 1)
								movesVect.push_back(board_state);
						}
					}
					gridArray[i][j] = EMPTY_PIECE; // reset analised pole
				}
			}
		}
		//movesVect.push_back(best_move);
		return best_move;
	}

	void AI::CheckAndPlace(int row, int column, std::vector<std::vector<int>>& gridArray, sf::Sprite gridPieces[3][3], int turn) {
		try {
			//std::cout << "\nCheckAndPlace";
			if(EMPTY_PIECE == gridArray[row][column]) {
				gridArray[row][column] = turn;
				gridPieces[column][row].setTexture(this->_data->assets.GetTexture(turn == O_PIECE ? "O Piece" : "X Piece"));

				gridPieces[column][row].setColor(sf::Color(255, 255, 255, 255));


				throw -2;
			}
		} catch(int error) {}
	}

}

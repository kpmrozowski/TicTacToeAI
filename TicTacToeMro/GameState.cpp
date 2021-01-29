#pragma once

#include <random>
#include <sstream>
#include "GameState.hpp"
#include "MainMenuState.hpp"
#include "DEFINITIONS.hpp"
#include "PauseState.hpp"
#include "GameOverState.hpp"

#include <iostream>

namespace mro {
	GameState::GameState(GameDataRef data, int playerPiece) : _data(data) {
		PLAYER_PIECE = playerPiece;
		grid = std::vector<std::vector<int>>(3, std::vector<int>(3, -1));
	}

	void GameState::Init() {
		gameState = STATE_PLAYING;
		turn = X_PIECE;

		this->ai = new AI(turn, this->_data);

		this->_data->assets.LoadTexture("Background", GAME_BACKGROUND_FILEPATH);
		this->_data->assets.LoadTexture("Pause Button", PAUSE_BUTTON);
		this->_data->assets.LoadTexture("Grid Sprite", GRID_SPRITE_FILEPATH);
		this->_data->assets.LoadTexture("X Piece", X_PIECE_FILEPATH);
		this->_data->assets.LoadTexture("O Piece", O_PIECE_FILEPATH);
		this->_data->assets.LoadTexture("X Winning Piece", X_WINNING_PIECE_FILEPATH);
		this->_data->assets.LoadTexture("O Winning Piece", O_WINNING_PIECE_FILEPATH);

		//	Reusing background, which was loaded in MainMenu.cpp (had no time for creating exclusive background, so.. let's be happy that sth is here):
		_background.setTexture(this->_data->assets.GetTexture("Background"));
		_pauseButton.setTexture(this->_data->assets.GetTexture("Pause Button"));
		_gridSprite.setTexture(this->_data->assets.GetTexture("Grid Sprite"));

		_pauseButton.setPosition(this->_data->window.getSize().x - _pauseButton.getLocalBounds().width, _pauseButton.getPosition().y);
		_gridSprite.setPosition(SCREEN_WIDTH / 2 - _gridSprite.getGlobalBounds().width / 2, SCREEN_HEIGHT / 2 - _gridSprite.getGlobalBounds().height / 2);

		InitGridPieces();

		for(int x = 0; x < 3; x++)
			for(int y = 0; y < 3; y++)
				grid[x][y] = EMPTY_PIECE;

		if(X_PIECE == PLAYER_PIECE) {
			std::cout << "\n1st: X_PIECE == PLAYER_PIECE";
			AI_PIECE = O_PIECE;
			turn = PLAYER_PIECE;
			this->HandleInput();
		} else if(O_PIECE == PLAYER_PIECE) {
			std::cout << "\n1st: O_PIECE == PLAYER_PIECE";
			AI_PIECE = X_PIECE;
			turn = AI_PIECE;
			makeRandomMove();
			turnNr++;
			print(grid);
			turn = PLAYER_PIECE;
			gameState = STATE_PLAYING;
			this->HandleInput();
		}
	}

	void GameState::HandleInput() {
		sf::Event event;

		while(this->_data->window.pollEvent(event)) {
			if(sf::Event::Closed == event.type)
				this->_data->window.close();

			if(this->_data->input.IsSpriteClicked(this->_pauseButton, sf::Mouse::Left, this->_data->window)) {
				// Switch To Pause State
				this->_data->machine.AddState(StateRef(new PauseState(_data)), false);
			} else if(this->_data->input.IsSpriteClicked(this->_gridSprite, sf::Mouse::Left, this->_data->window))
				if(STATE_PLAYING == gameState) {
						turn = PLAYER_PIECE;
						this->PlayerMove();
					}
		}
	}

	void GameState::makeRandomMove() {
		gameState = STATE_AI_PLAYING;
		turn = AI_PIECE;
		std::mt19937 mt(std::random_device{}());
		std::uniform_int_distribution<int> dist(0, 2);
		int column{dist(mt)};
		int row{dist(mt)};
		ai->CheckAndPlace(column, row, grid, _gridPieces, turn);
		std::cout << "\nRandom Move = (" << row << ", " << column << ")";
	}

	void GameState::Update(float dt) {
		if(STATE_DRAW == gameState || STATE_LOSE == gameState || STATE_WON == gameState) {
			if(this->_clock.getElapsedTime().asSeconds() > TIME_BEFORE_SHOWING_GAME_OVER) {
				// Switch To Main Menu
				this->_data->machine.AddState(StateRef(new GameOverState(_data, PLAYER_PIECE)), true);
			}
		}
	}

	void GameState::Draw(float dt) {
		this->_data->window.clear(sf::Color::Red);
		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_pauseButton);
		this->_data->window.draw(this->_gridSprite);

		for(int x = 0; x < 3; x++) {
			for(int y = 0; y < 3; y++) {
				this->_data->window.draw(this->_gridPieces[y][x]);
			}
		}

		this->_data->window.display();
	}

	void GameState::InitGridPieces() {
		sf::Vector2u tempSpriteSize = this->_data->assets.GetTexture("X Piece").getSize();

		for(int x = 0; x < 3; x++) {
			for(int y = 0; y < 3; y++) {
				_gridPieces[x][y].setTexture(this->_data->assets.GetTexture("X Piece"));
				_gridPieces[x][y].setPosition(_gridSprite.getPosition().x + (tempSpriteSize.x * x) - 7, _gridSprite.getPosition().y + (tempSpriteSize.y * y) - 7);
				_gridPieces[x][y].setColor(sf::Color(255, 255, 255, 0));
			}
		}
	}

	void GameState::PlayerMove() {
		sf::Vector2i touchPoint = this->_data->input.GetMousePosition(this->_data->window);
		sf::FloatRect gridSize = _gridSprite.getGlobalBounds();
		sf::Vector2f gapOutsideOfGrid = sf::Vector2f((SCREEN_WIDTH - gridSize.width) / 2, (SCREEN_HEIGHT - gridSize.height) / 2);

		sf::Vector2f gridLocalTouchPos = sf::Vector2f(touchPoint.x - gapOutsideOfGrid.x, touchPoint.y - gapOutsideOfGrid.y);

		sf::Vector2f gridSectionSize = sf::Vector2f(gridSize.width / 3, gridSize.height / 3);

		int row{}, column{};

		// Check which row the user has clicked
		if(gridLocalTouchPos.x < gridSectionSize.x) // First row
		{
			row = 1;
		} else if(gridLocalTouchPos.x < gridSectionSize.x * 2) // Second row
		{
			row = 2;
		} else if(gridLocalTouchPos.x < gridSize.width) // Third row
		{
			row = 3;
		}

		// Check which column the user has clicked
		if(gridLocalTouchPos.y < gridSectionSize.y) // First column
		{
			column = 1;
		} else if(gridLocalTouchPos.y < gridSectionSize.y * 2) // Second column
		{
			column = 2;
		} else if(gridLocalTouchPos.y < gridSize.height) // Third column
		{
			column = 3;
		}

		if(grid[column - 1][row - 1] == EMPTY_PIECE) {
			grid[column - 1][row - 1] = PLAYER_PIECE;
			std::cout << "\nPlayerMove(c" << column << ", r" << row << ")";
			print(grid);

			if(PLAYER_PIECE == turn) {
				_gridPieces[row - 1][column - 1].setTexture(this->_data->assets.GetTexture(PLAYER_PIECE == X_PIECE ? "X Piece" : "O Piece"));
				CheckWon();
				turn = AI_PIECE;
				if(STATE_WON != gameState)
					this->AiMove();
			}

			_gridPieces[row - 1][column - 1].setColor(sf::Color(255, 255, 255, 255));
		}
	}

	void GameState::AiMove() {
		std::cout << "\nAI is making a move... ";
		gameState = STATE_AI_PLAYING;
		turn = AI_PIECE;
		if(turnNr != 0) {
			ai->PlacePiece(grid, _gridPieces, gameState, turn);
			turnNr++;
		} else {
			turnNr = 1;
			// Find player's first move:
			Move playerFirstMove{};
			for(int i = 0; i < 3; i++)
				for(int j = 0; j < 3; j++)
					if(grid[i][j] == PLAYER_PIECE) {
						playerFirstMove.column = i;
						playerFirstMove.row = j;
					}

			//	In the AI's first turn: place "O" on the oposite side of "X"
			std::mt19937 mt(std::random_device{}());
			std::uniform_int_distribution<int> dist(0, 1);
			switch(playerFirstMove.column * 3 + playerFirstMove.row) {
				break;
				case 1:
					ai->CheckAndPlace(2, 1, grid, _gridPieces, turn);
					break;
				case 3:
					ai->CheckAndPlace(1, 2, grid, _gridPieces, turn);
					break;
				case 4:
					ai->CheckAndPlace(2 * dist(mt), 2 * dist(mt), grid, _gridPieces, turn);
					break;
				case 5:
					ai->CheckAndPlace(1, 0, grid, _gridPieces, turn);
					break;
				case 7:
					ai->CheckAndPlace(0, 1, grid, _gridPieces, turn);
					break;
				default:
					ai->CheckAndPlace(1, 1, grid, _gridPieces, turn);
			};
			gameState = STATE_PLAYING;
		}
		print(grid);
		CheckWon();
	}

	void GameState::CheckWon() {
		Check3PiecesForMatch(0, 0, 1, 0, 2, 0, AI_PIECE);
		Check3PiecesForMatch(0, 1, 1, 1, 2, 1, AI_PIECE);
		Check3PiecesForMatch(0, 2, 1, 2, 2, 2, AI_PIECE);
		Check3PiecesForMatch(0, 0, 0, 1, 0, 2, AI_PIECE);
		Check3PiecesForMatch(1, 0, 1, 1, 1, 2, AI_PIECE);
		Check3PiecesForMatch(2, 0, 2, 1, 2, 2, AI_PIECE);
		Check3PiecesForMatch(0, 0, 1, 1, 2, 2, AI_PIECE);
		Check3PiecesForMatch(0, 2, 1, 1, 2, 0, AI_PIECE);

		int emptyNum = 9;

		for(int x = 0; x < 3; x++) {
			for(int y = 0; y < 3; y++) {
				if(EMPTY_PIECE != grid[x][y]) {
					emptyNum--;
				}
			}
		}

		// check if the game is a draw
		if(0 == emptyNum && (STATE_WON != gameState) && (STATE_LOSE != gameState)) {
			gameState = STATE_DRAW;
			std::cout << "Remis! (*_*)";
		}

		// check if AI won
		if(gameState == STATE_WON)
			std::cout << "AI won! (-_-)";

		// check if the game is over
		if(STATE_DRAW == gameState || STATE_LOSE == gameState || STATE_WON == gameState) {
			// show game over
			this->_clock.restart();
		}
	}

	void GameState::print(std::vector<std::vector<int>>& gridArray) {
		std::cout << '\n';

		for(int i = 0; i < 3; i++) {
			if(i) {
				std::cout << "-----------\n";
			}

			for(int j = 0; j < 3; j++) {
				if(j)
					std::cout << "|";
				std::cout << ' ';

				if(gridArray[i][j] == -1) {
					std::cout << 3 * i + j + 1;
				} else if(gridArray[i][j] == 0) {
					std::cout << 'O';
				} else {
					std::cout << 'X';
				}
				std::cout << ' ';
			}
			std::cout << '\n';
		}
		std::cout << '\n';
	}

	void GameState::Check3PiecesForMatch(int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck) {
		if(pieceToCheck == grid[x1][y1] && pieceToCheck == grid[x2][y2] && pieceToCheck == grid[x3][y3]) {
			std::string winningPieceStr;

			if(O_PIECE == pieceToCheck) {
				winningPieceStr = "O Winning Piece";
			} else {
				winningPieceStr = "X Winning Piece";
			}

			_gridPieces[y1][x1].setTexture(this->_data->assets.GetTexture(winningPieceStr));
			_gridPieces[y2][x2].setTexture(this->_data->assets.GetTexture(winningPieceStr));
			_gridPieces[y3][x3].setTexture(this->_data->assets.GetTexture(winningPieceStr));

			gameState = STATE_WON;
		}
	}
}

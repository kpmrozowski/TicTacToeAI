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
	GameState::GameState(GameDataRef data, int playerPiece) : _data(data), turn{X_PIECE} {
		grid = std::vector<std::vector<int>>(3, std::vector<int>(3, -1));
		PLAYER_piece = playerPiece;
		AI_PIECE = playerPiece == O_PIECE ? X_PIECE : O_PIECE;		std::cout<<"17\n";
	}

	void GameState::Init() {
		gameState = STATE_PLAYING;	std::cout<<"39\n";

		this->_data->assets.LoadTexture("Background", GAME_BACKGROUND_FILEPATH);
		this->_data->assets.LoadTexture("Pause Button", PAUSE_BUTTON);
		this->_data->assets.LoadTexture("Grid Sprite", GRID_SPRITE_FILEPATH);
		this->_data->assets.LoadTexture("X Winning Piece", X_WINNING_PIECE_FILEPATH);
		this->_data->assets.LoadTexture("O Winning Piece", O_WINNING_PIECE_FILEPATH);

		//	Reusing background, which was loaded in MainMenu.cpp (had no time for creating exclusive background, so.. let's be happy that there is pause state):
		_background.setTexture(this->_data->assets.GetTexture("Background"));
		_pauseButton.setTexture(this->_data->assets.GetTexture("Pause Button"));
		_gridSprite.setTexture(this->_data->assets.GetTexture("Grid Sprite"));

		_pauseButton.setPosition(this->_data->window.getSize().x - _pauseButton.getLocalBounds().width, _pauseButton.getPosition().y);
		_gridSprite.setPosition(SCREEN_WIDTH / 2 - _gridSprite.getGlobalBounds().width / 2, SCREEN_HEIGHT / 2 - _gridSprite.getGlobalBounds().height / 2);

		InitGridPieces();	std::cout<<"63\n";

		for(int x = 0; x < 3; x++)
			for(int y = 0; y < 3; y++)
				grid[x][y] = EMPTY_PIECE;
		
		if(AI_PIECE == X_PIECE) {
			this->_data->assets.LoadTexture("X Piece", X_PIECE_FILEPATH);
			this->_data->assets.LoadTexture("O Piece", O_PIECE_FILEPATH);
			//turn = AI_PIECE;
			this->ai = new AI(this->PLAYER_piece, this->_data);
			makeRandomMove();
			//this->_data->window.draw(this->_gridPieces[1][1]);
			for(int x = 0; x < 3; x++) {
				for(int y = 0; y < 3; y++) {
					this->_data->window.draw(this->_gridPieces[x][y]);
				}
			}
			this->_data->window.display();
			std::cout << "34\n";
		}
		//play();	// Choose a piece, x begins
		if(PLAYER_piece == X_PIECE) {
			this->ai = new AI(PLAYER_piece, this->_data);
			std::cout << "46\n";
		}
	}

	void GameState::HandleInput() {
		sf::Event event;	//std::cout<<"71\n";

		while(this->_data->window.pollEvent(event)) {
			if(sf::Event::Closed == event.type)
				this->_data->window.close();		std::cout<<"75\n";

			if(this->_data->input.IsSpriteClicked(this->_pauseButton, sf::Mouse::Left, this->_data->window)) {
				// Choose Xes or Ohs

				// Switch To Game State
				this->_data->machine.AddState(StateRef(new PauseState(_data)), false);	std::cout<<"83\n";
			} else if(this->_data->input.IsSpriteClicked(this->_gridSprite, sf::Mouse::Left, this->_data->window))
				if(STATE_PLAYING == gameState) {
					this->Play();	std::cout<<"86\n";
				}
		}
	}

	void GameState::Update(float dt) {
		if(STATE_DRAW == gameState || STATE_LOSE == gameState || STATE_WON == gameState) {
			if(this->_clock.getElapsedTime().asSeconds() > TIME_BEFORE_SHOWING_GAME_OVER) {
				// Switch To Main Menu
				this->_data->machine.AddState(StateRef(new GameOverState(_data, PLAYER_piece)), true); 	std::cout<<"95\n";
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
				this->_data->window.draw(this->_gridPieces[x][y]);
			}
		}

		this->_data->window.display();
	}

	void GameState::InitGridPieces() {
		this->_data->assets.LoadTexture("X Piece", X_PIECE_FILEPATH);
		this->_data->assets.LoadTexture("O Piece", O_PIECE_FILEPATH);
		sf::Vector2u tempSpriteSize = this->_data->assets.GetTexture("X Piece").getSize();		std::cout<<"116\n";

		for(int x = 0; x < 3; x++) {
			for(int y = 0; y < 3; y++) {
				_gridPieces[x][y].setTexture(this->_data->assets.GetTexture("X Piece"));
				_gridPieces[x][y].setPosition(_gridSprite.getPosition().x + (tempSpriteSize.x * x) - 7, _gridSprite.getPosition().y + (tempSpriteSize.y * y) - 7);
				_gridPieces[x][y].setColor(sf::Color(255, 255, 255, 0));	std::cout<<"122\n";
			}
		}
	}

	void GameState::Play() {
		sf::Vector2i touchPoint = this->_data->input.GetMousePosition(this->_data->window);	std::cout<<"128\n";
		sf::FloatRect gridSize = _gridSprite.getGlobalBounds();
		sf::Vector2f gapOutsideOfGrid = sf::Vector2f((SCREEN_WIDTH - gridSize.width) / 2, (SCREEN_HEIGHT - gridSize.height) / 2);

		sf::Vector2f gridLocalTouchPos = sf::Vector2f(touchPoint.x - gapOutsideOfGrid.x, touchPoint.y - gapOutsideOfGrid.y);

		//std::cout << gridLocalTouchPos.x << ", " << gridLocalTouchPos.y << std::endl;

		sf::Vector2f gridSectionSize = sf::Vector2f(gridSize.width / 3, gridSize.height / 3);

		int column{}, row{};

		// Check which column the user has clicked
		if(gridLocalTouchPos.x < gridSectionSize.x) // First Column
		{
			column = 1;	std::cout<<"143\n";
		} else if(gridLocalTouchPos.x < gridSectionSize.x * 2) // Second Column
		{
			column = 2;	std::cout<<"146\n";
		} else if(gridLocalTouchPos.x < gridSize.width) // Third Column
		{
			column = 3;	std::cout<<"149\n";
		}

		// Check which row the user has clicked
		if(gridLocalTouchPos.y < gridSectionSize.y) // First Row
		{
			row = 1;		std::cout<<"155\n";
		} else if(gridLocalTouchPos.y < gridSectionSize.y * 2) // Second Row
		{
			row = 2;	std::cout<<"158\n";
		} else if(gridLocalTouchPos.y < gridSize.height) // Third Row
		{
			row = 3;	std::cout<<"161\n";
		}

		if(grid[column - 1][row - 1] == EMPTY_PIECE) {
			grid[column - 1][row - 1] = PLAYER_piece;	std::cout<<"165\n";

			if(PLAYER_piece == turn) {
				_gridPieces[column - 1][row - 1].setTexture(this->_data->assets.GetTexture(PLAYER_piece == X_PIECE ? "X Piece" : "O Piece"));

				this->Check3WhoWon(turn);	std::cout<<"170\n";
			}

			if(AI_PIECE == turn) {
				_gridPieces[column - 1][row - 1].setTexture(this->_data->assets.GetTexture(AI_PIECE == X_PIECE ? "X Piece" : "O Piece"));

				this->Check3WhoWon(turn);	std::cout<<"172\n";
			}

			_gridPieces[column - 1][row - 1].setColor(sf::Color(255, 255, 255, 255));	std::cout<<"173\n";	
		}
	}

	void GameState::Check3WhoWon(int player) {
		Check3WhoWon(0, 0, 1, 0, 2, 0, player);	std::cout<<"178\n";
		Check3WhoWon(0, 1, 1, 1, 2, 1, player);
		Check3WhoWon(0, 2, 1, 2, 2, 2, player);
		Check3WhoWon(0, 0, 0, 1, 0, 2, player);
		Check3WhoWon(1, 0, 1, 1, 1, 2, player);
		Check3WhoWon(2, 0, 2, 1, 2, 2, player);
		Check3WhoWon(0, 0, 1, 1, 2, 2, player);
		Check3WhoWon(0, 2, 1, 1, 2, 0, player);

		if(STATE_WON != gameState) {
			gameState = STATE_AI_PLAYING;		std::cout<<"188\n";
			std::cout << "\nturnNr = " << turnNr << "\n";
			if(turnNr > 0) {
				ai->PlacePiece(grid, _gridPieces, gameState, turn);
				std::cout << "191: AI_PIECE?\n";
				turnNr++;
			} else {
				// Find player's first move:
				Move playerFirstMove{};	std::cout<<"195\n";
				for(int i = 0; i < 3; i++)
					for(int j = 0; j < 3; j++)
						if(grid[i][j] == PLAYER_piece) {
							playerFirstMove.row = i;
							playerFirstMove.column = j;	std::cout<<"200\n";
						}

				//	In the AI's first turn: place "O" on the oposite side of "X"
				std::mt19937 mt(std::random_device{}());
				std::uniform_int_distribution<int> dist(0, 1);
				switch(playerFirstMove.row * 3 + playerFirstMove.column) {
					break;
					case 1:
						ai->CheckAndPlace(2, 1, grid, _gridPieces, AI_PIECE);
						break;
					case 3:
						ai->CheckAndPlace(1, 2, grid, _gridPieces, AI_PIECE);
						break;
					case 4:
						ai->CheckAndPlace(2 * dist(mt), 2 * dist(mt), grid, _gridPieces, AI_PIECE);
						break;
					case 5:
						ai->CheckAndPlace(1, 0, grid, _gridPieces, AI_PIECE);
						break;
					case 7:
						ai->CheckAndPlace(0, 1, grid, _gridPieces, AI_PIECE);
						break;
					default:
						ai->CheckAndPlace(1, 1, grid, _gridPieces, AI_PIECE);
				};
				gameState = STATE_PLAYING;
				turnNr++;	std::cout<<"227\n";
			}

			Check3WhoWon(0, 0, 1, 0, 2, 0, AI_PIECE);
			Check3WhoWon(0, 1, 1, 1, 2, 1, AI_PIECE);
			Check3WhoWon(0, 2, 1, 2, 2, 2, AI_PIECE);
			Check3WhoWon(0, 0, 0, 1, 0, 2, AI_PIECE);
			Check3WhoWon(1, 0, 1, 1, 1, 2, AI_PIECE);
			Check3WhoWon(2, 0, 2, 1, 2, 2, AI_PIECE);
			Check3WhoWon(0, 0, 1, 1, 2, 2, AI_PIECE);
			Check3WhoWon(0, 2, 1, 1, 2, 0, AI_PIECE);	std::cout<<"237\n";
		}

		int emptyNum = 9;

		for(int x = 0; x < 3; x++) {
			for(int y = 0; y < 3; y++) {
				if(EMPTY_PIECE != grid[x][y]) {
					emptyNum--;	std::cout<<"245\n";
				}
			}
		}

		// check if the game is a draw
		if(0 == emptyNum && (STATE_WON != gameState) && (STATE_LOSE != gameState)) {
			gameState = STATE_DRAW;	std::cout<<"252\n";
		}

		// check if the game is over
		if(STATE_DRAW == gameState || STATE_LOSE == gameState || STATE_WON == gameState) {
			// show game over
			this->_clock.restart();	std::cout<<"258\n";
		}

		std::cout << "\ngameState = " << gameState << std::endl;
		std::cout << "261\n";
		turn = turn == X_PIECE ? O_PIECE : X_PIECE;
	}

	void GameState::makeRandomMove() {
		std::cout << "\nRandom Move";
		std::mt19937 mt(std::random_device{}());
		std::uniform_int_distribution<int> dist(0, 2);
		int row{dist(mt)};
		int column{dist(mt)};
		gameState = STATE_PLAYING;
		_gridPieces[row][column].setTexture(_data->assets.GetTexture("X Piece"));
		turn = AI_PIECE;
		ai->CheckAndPlace(row, column, grid, _gridPieces, turn);
		_data->window.draw(_gridPieces[row][column]);
		_data->window.draw(this->_background);
		_data->window.display();	std::cout<<"275\n";
	}

	//void GameState::play() {
	//	char imput{};
	//	int turnNr{0};

	//	while(true) {
	//		std::cout << "Which symbol (X or O, X goes first)? ";
	//		std::cin >> imput;
	//		if(imput == 'X' || imput == 'O' || imput == 'x' || imput == 'o') {
	//			break;
	//		}
	//	}
	//	if(imput == 'x' || imput == 'X')
	//		PLAYER_piece = X_PIECE;
	//	if(imput == 'o' || imput == 'O')
	//		PLAYER_piece = O_PIECE;
	//	AI_PIECE = PLAYER_piece == X_PIECE ? O_PIECE : X_PIECE;
	//}

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

	void GameState::Check3WhoWon(int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck) {
		if(pieceToCheck == grid[x1][y1] && pieceToCheck == grid[x2][y2] && pieceToCheck == grid[x3][y3]) {
			std::string winningPieceStr;	std::cout<<"325\n";

			if(O_PIECE == pieceToCheck) {
				winningPieceStr = "O Winning Piece";	std::cout<<"328\n";
			} else {
				winningPieceStr = "X Winning Piece";	std::cout<<"330\n";
			}

			_gridPieces[x1][y1].setTexture(this->_data->assets.GetTexture(winningPieceStr));
			_gridPieces[x2][y2].setTexture(this->_data->assets.GetTexture(winningPieceStr));
			_gridPieces[x3][y3].setTexture(this->_data->assets.GetTexture(winningPieceStr));


			if(PLAYER_piece == pieceToCheck) {
				gameState = STATE_WON;	std::cout<<"339\n";
			} else {
				gameState = STATE_LOSE;	std::cout<<"341\n";
			}
		}
	}
}

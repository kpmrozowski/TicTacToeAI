#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

#include "AI.hpp"

namespace mro {
	class GameState : public State {
		public:
		GameState(GameDataRef data, int playerPiece);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);
		void makeRandomMove();
		//void play();
		static void print(std::vector<std::vector<int>>& gridArray);

		int gameState{};
		std::vector<std::vector<int>> grid; //	The array keeps track of what is actually in the grid at the moment (EMPTY_PIECE, O_PIECE, X_PIECE)

		int PLAYER_piece;
		int AI_PIECE;

		private:
		void InitGridPieces();	// Loading pices: X and O
		
		void Play();

		void Check3WhoWon(int turn);
		void Check3WhoWon(int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck);

		GameDataRef _data;

		sf::Sprite _background;
		sf::Sprite _pauseButton;
		sf::Sprite _gridSprite;

		sf::Sprite _gridPieces[3][3];

		int turn{};
		int turnNr{0};

		AI* ai{};

		sf::Clock _clock;
	};
}

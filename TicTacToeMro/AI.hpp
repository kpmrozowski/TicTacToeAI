#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include "Game.hpp"

namespace mro
{
	class AI
	{
	public:
		AI(int playerPiece, GameDataRef data);

		void PlacePiece(std::vector<std::vector<int>>& gridArray, sf::Sprite gridPieces[3][3], int& gameState);

	private:
		void CheckSection(int x1, int y1, int x2, int y2, int X, int Y, int pieceToCheck, std::vector<std::vector<int>>& gridArray, sf::Sprite gridPieces[3][3]);
		void CheckIfPieceIsEmpty(int X, int Y, std::vector<std::vector<int>>& gridArray, sf::Sprite gridPieces[3][3]);

		int aiPiece;
		int playerPiece;

		std::vector<std::array<int, 6>> checkMatchVector;

		GameDataRef _data;

	};
}
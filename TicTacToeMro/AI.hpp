#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include "Game.hpp"
#include "Move.hpp"

namespace mro
{
	class AI
	{
	public:
		AI(int playerPiece, GameDataRef data);

		void PlacePiece(std::vector<std::vector<int>>& gridArray, sf::Sprite gridPieces[3][3], int& gameState);

		bool win(std::vector<std::vector<int>>& gridArray);

		bool tie(std::vector<std::vector<int>>& gridArray);

		Move minimax(std::vector<std::vector<int>>& gridArray, bool maximizing_player = true);

		void CheckAndPlace(int X, int Y, std::vector<std::vector<int>>& gridArray, sf::Sprite gridPieces[3][3]);

	private:
		int aiPiece;
		int playerPiece;

		std::vector<std::vector<int>> checkMatchVector{};

		GameDataRef _data;

	};
}
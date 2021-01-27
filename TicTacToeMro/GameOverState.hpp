#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace mro
{
	class GameOverState : public State
	{
	public:
		GameOverState(GameDataRef data, int playerPiece);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		int PLAYER_PIECE;
		GameDataRef _data;

		sf::Sprite _retryButton;
		sf::Sprite _homeButton;

	};
}
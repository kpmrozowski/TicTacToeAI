#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace mro {
	class SplashState: public State {
		public:
		SplashState( GameDataRef data);

		void Init(); // initialises class

		void HandleImput();
		void Update(float dt);
		void Draw(float dt);

		private:
		GameDataRef _data;

		sf::Clock _clock; //how long the application is running

		sf::Sprite _background;
	};
}
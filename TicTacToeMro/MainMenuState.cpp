#include <sstream>
#include "MainMenuState.hpp"
#include "DEFINITIONS.hpp"
#include "GameState.hpp"

#include <iostream>

namespace mro {
	MainMenuState::MainMenuState(GameDataRef data) : _data(data) {
	}

	void MainMenuState::Init() {
		this->_data->assets.LoadTexture("Background", MAIN_MENU_BACKGROUND_FILEPATH);
		this->_data->assets.LoadTexture("Play Button X", MAIN_MENU_PLAY_BUTTON_X);
		this->_data->assets.LoadTexture("Play Button O", MAIN_MENU_PLAY_BUTTON_O);
		this->_data->assets.LoadTexture("Play Button Outer", MAIN_MENU_PLAY_BUTTON_OUTER);
		this->_data->assets.LoadTexture("Game Title", MAIN_MENU_TITLE_FILEPATH);

		this->_background.setTexture(this->_data->assets.GetTexture("Background"));
		this->_playButtonX.setTexture(this->_data->assets.GetTexture("Play Button X"));
		this->_playButtonO.setTexture(this->_data->assets.GetTexture("Play Button O"));
		this->_playButtonOuter.setTexture(this->_data->assets.GetTexture("Play Button Outer"));
		this->_title.setTexture(this->_data->assets.GetTexture("Game Title"));

		this->_playButtonX.setPosition(SCREEN_WIDTH / 2 - this->_playButtonX.getGlobalBounds().width - XY_BUTTONS_OFFSET / 2, SCREEN_HEIGHT / 2 - this->_playButtonX.getGlobalBounds().height / 2);
		this->_playButtonO.setPosition(SCREEN_WIDTH /2 + XY_BUTTONS_OFFSET /2, SCREEN_HEIGHT / 2 - this->_playButtonO.getGlobalBounds().height / 2);
		this->_playButtonOuter.setPosition(SCREEN_WIDTH / 2 - this->_playButtonOuter.getGlobalBounds().width / 2, SCREEN_HEIGHT / 2 - this->_playButtonOuter.getGlobalBounds().height / 2);

		this->_title.setPosition((SCREEN_WIDTH / 2) - (this->_title.getGlobalBounds().width / 2), this->_title.getGlobalBounds().height * 0.1);
	}

	void MainMenuState::HandleInput() {
		sf::Event event;

		while(this->_data->window.pollEvent(event)) {
			if(sf::Event::Closed == event.type)
				this->_data->window.close();

			if(this->_data->input.IsSpriteClicked(this->_playButtonX, sf::Mouse::Left, this->_data->window)) {
				// Switch To Game State
				this->_data->machine.AddState(StateRef(new GameState(_data, X_PIECE)), true);
			}

			if(this->_data->input.IsSpriteClicked(this->_playButtonO, sf::Mouse::Left, this->_data->window)) {
				// Switch To Game State
				this->_data->machine.AddState(StateRef(new GameState(_data, O_PIECE)), true);
			}
		}
	}

	void MainMenuState::Update(float dt) {
		//	Here will be future animation, but for Prograowanie Objektowe w Jezyku C++ there wasn't enough time... :(
	}

	void MainMenuState::Draw(float dt) {
		this->_data->window.clear(sf::Color::Red);

		this->_data->window.draw(this->_background);
		this->_data->window.draw(this->_title);
		this->_data->window.draw(this->_playButtonOuter);
		this->_data->window.draw(this->_playButtonX);
		this->_data->window.draw(this->_playButtonO);

		this->_data->window.display();
	}
}

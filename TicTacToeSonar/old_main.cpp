#include <SFML\Graphics.hpp>
#include <iostream>
#include "Game.hpp"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 1024

int main() {
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Awesome Game");
	while(window.isOpen()) {
		sf::Event event;

		while(window.pollEvent(event)) {
			switch(event.type) {
				case sf::Event::Closed:
					window.close();

					break;
			}
		}
		window.clear();
		window.display();
	}
	return 0;
}

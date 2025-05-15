#include "game.h"

#include "../../core/include/map_generation.h"
#include "SFML/Graphics.hpp"

namespace game{

	namespace{
	  sf::RenderWindow window_;
	  sf::Texture grass_texture_("../assets/sprites/grass.png");
	  sf::Sprite sprite(grass_texture_);

	  void Setup() {
	    window_.create(sf::VideoMode({800,600}), "SFML window");

	  }
	}

	void Loop() {

	  Setup();


		//Start the game loop
		while (window_.isOpen())
		{
			//Process events
			while (const std::optional event = window_.pollEvent())
			{
				//Close window: exit
				if (event->is<sf::Event::Closed>()) {
					window_.close();
				}
			}

			window_.clear();

			window_.draw(sprite);

			window_.display();
		}
	}
}
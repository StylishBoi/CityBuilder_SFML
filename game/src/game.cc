#include "game.h"

#include <iostream>

#include "SFML/Graphics.hpp"
#include "ai/npc.h"
#include "graphics/tilemap.h"

namespace game{

	namespace{
	  sf::RenderWindow window_;
	  TileMap tilemap_;
	  Npc npc_;

	  void Setup() {
	    window_.create(sf::VideoMode({kWindowWidth,kWindowHeight}), "SFML window");

	    tilemap_.Setup();
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

		        npc_.Draw(window_);
			tilemap_.Draw(window_);

			window_.display();
		}
	}
}
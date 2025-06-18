#include "game.h"

#include <iostream>

#include "SFML/Graphics.hpp"
#include "ai/npc.h"
#include "graphics/tilemap.h"

namespace game{

	namespace{
	  sf::Clock clock_;

	  sf::RenderWindow window_;
	  TileMap tilemap_;

	  api::ai::Npc npc_;

	  void Setup() {
	    window_.create(sf::VideoMode({kWindowWidth,kWindowHeight}), "SFML window");

	    tilemap_.Setup();
	    npc_.Setup(&tilemap_);
	  }
	}

	void Loop() {

	  Setup();


		//Start the game loop
		while (window_.isOpen())
		{
		        //Reset the clock each frame
		        float deltaTime = clock_.restart().asSeconds();

			//Process events
			while (const std::optional event = window_.pollEvent())
			{
				//Close window: exit
				if (event->is<sf::Event::Closed>()) {
					window_.close();
				}
			}

		        npc_.Update(deltaTime);

			window_.clear();

			tilemap_.Draw(window_);
		        npc_.Draw(window_);

			window_.display();
		}
	}
}
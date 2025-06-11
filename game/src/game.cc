#include "game.h"

#include <iostream>

#include "SFML/Graphics.hpp"
#include "ai/npc.h"
#include "graphics/tilemap.h"

namespace game{

	namespace{
	  sf::RenderWindow window_;
	  sf::Clock clock_;
	  TileMap tilemap_;

	  api::ai::Npc npc_;

	  void Setup() {
	    window_.create(sf::VideoMode({kWindowWidth,kWindowHeight}), "SFML window");

	    tilemap_.Setup();
	    npc_.Setup();
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

		        npc_.Draw(window_);
			tilemap_.Draw(window_);

			window_.display();
		}
	}
}
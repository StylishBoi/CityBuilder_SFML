#include "game.h"

#include <iostream>

#include "SFML/Graphics.hpp"
#include "ai/npc_manager.h"
#include "graphics/resources.h"
#include "graphics/tilemap.h"

namespace game{

	namespace{
	inline sf::Clock clock_;

	inline sf::RenderWindow window_;
	inline auto tilemap_ptr_= std::make_unique<TileMap>();
	// inline TileMap tilemap_obj_;
	inline api::ai::NpcManager npc_manager_;
	Resources resources_;

	  void Setup() {
	    window_.create(sf::VideoMode({kWindowWidth,kWindowHeight}), "SFML window");

	    tilemap_ptr_->Setup();
	    resources_.Setup(tilemap_ptr_.get());
	    npc_manager_.Add(api::ai::NpcType::kGreen, tilemap_ptr_.get());
	    npc_manager_.Add(api::ai::NpcType::kBlue, tilemap_ptr_.get());
	    npc_manager_.Add(api::ai::NpcType::kRed, tilemap_ptr_.get());
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

		        npc_manager_.Update(deltaTime);

			window_.clear();

			tilemap_ptr_->Draw(window_);
		        resources_.Draw(window_);
		        npc_manager_.Draw(window_);

			window_.display();
		}
	}
}
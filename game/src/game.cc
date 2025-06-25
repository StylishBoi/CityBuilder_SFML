#include "game.h"

#include <iostream>

#include "SFML/Graphics.hpp"

#include "ai/npc_manager.h"
#include "graphics/resources.h"
#include "graphics/tilemap.h"
#include "ui/clickable.h"

namespace game{

	namespace{

	//Inline makes it so that it is compiled on the spot
	inline sf::Clock clock_;
	inline sf::RenderWindow window_;
	inline auto tilemap_ptr_= std::make_unique<TileMap>();
	inline api::ai::NpcManager npc_manager_;

	inline api::ui::Clickable clickable_;

	inline sf::RectangleShape rect_;

	Resources resources_;

	  void Setup() {
	    window_.create(sf::VideoMode({kWindowWidth,kWindowHeight}), "SFML window");

	    tilemap_ptr_->Setup();
	    resources_.Setup(tilemap_ptr_.get());
	    npc_manager_.Add(api::ai::NpcType::kGreen, tilemap_ptr_.get());
	    npc_manager_.Add(api::ai::NpcType::kBlue, tilemap_ptr_.get());
	    npc_manager_.Add(api::ai::NpcType::kRed, tilemap_ptr_.get());

	    rect_.setPosition({static_cast<float>(25), static_cast<float>(window_.getSize().y - 75)});
	    rect_.setSize({50, 50});

	    clickable_.SetZone(sf::IntRect(
                {static_cast<int>(rect_.getPosition().x), static_cast<int>(rect_.getPosition().y)},
                {100, 100})
                );

	    clickable_.OnReleasedLeft = [] () {std::cout << "Left Released" << std::endl;};
	    clickable_.OnReleasedRight = [] () {std::cout << "Right Released" << std::endl;};
	    clickable_.OnPressedLeft = [] () {std::cout << "Left Pressed" << std::endl;};
	    clickable_.OnPressedRight = [] () {std::cout << "Right Pressed" << std::endl;};
	    clickable_.OnHoverEnter = [] () {std::cout << "Hover Enter" << std::endl;};
	    clickable_.OnHoverExit = [] () {std::cout << "Hover Exit" << std::endl;};
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

			        clickable_.HandleEvent(event);
			}

		        npc_manager_.Update(deltaTime);

			window_.clear();

			tilemap_ptr_->Draw(window_);
		        resources_.Draw(window_);
		        npc_manager_.Draw(window_);

		        window_.draw(rect_);

			window_.display();
		}
	}
}
#include "game.h"

#include "SFML/Graphics.hpp"
#include "ai/npc_manager.h"
#include "graphics/building_manager.h"
#include "graphics/resources_manager.h"
#include "graphics/tilemap.h"
#include "ui/button.h"
#include "ui/button_factory.h"
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

	inline Resources resources_;
	inline BuildingManager building_manager_;

	// UI Elements
	std::unique_ptr<api::ui::Button> btnBlue;
	std::unique_ptr<api::ui::Button> btnRed;
	std::unique_ptr<api::ui::Button> btnGreen;

        api::ui::ButtonFactory btn_factory;


	  void Setup() {
	    window_.create(sf::VideoMode({kWindowWidth,kWindowHeight}), "SFML window");

	    tilemap_ptr_->Setup();
	    resources_.Setup(tilemap_ptr_.get());
	    building_manager_.Setup(tilemap_ptr_.get());
	    npc_manager_.Add(api::ai::NpcType::kGreen, tilemap_ptr_.get(), &resources_);
	    npc_manager_.Add(api::ai::NpcType::kBlue, tilemap_ptr_.get(), &resources_);
	    npc_manager_.Add(api::ai::NpcType::kRed, tilemap_ptr_.get(), &resources_);

	    rect_.setPosition({static_cast<float>(25), static_cast<float>(window_.getSize().y - 75)});
	    rect_.setSize({50, 50});

	    clickable_.SetZone(sf::IntRect(
                {static_cast<int>(rect_.getPosition().x), static_cast<int>(rect_.getPosition().y)},
                {100, 100})
                );

	    btnBlue = btn_factory.CreateButton(sf::Vector2f(100.f, window_.getSize().y - 100.f), "Blue");

	    btnRed = btn_factory.CreateButton(sf::Vector2f(200.f, window_.getSize().y - 100.f), "Red");

	    btnGreen = btn_factory.CreateButton(sf::Vector2f(300.f, window_.getSize().y - 100.f), "Green");

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
		        building_manager_.Draw(window_);

		        window_.draw(rect_);

		        btnBlue->Draw(window_);
		        btnRed->Draw(window_);
		        btnGreen->Draw(window_);

			window_.display();
		}
	}
//1 - Make button to place house
//2 - House automatically spawns one NPC

}
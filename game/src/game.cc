#include "game.h"

#include "../include/resources_manager.h"
#include "SFML/Graphics.hpp"
#include "ai/npc_manager.h"
#include "graphics/building_manager.h"
#include "graphics/tilemap.h"
#include "ui/button.h"
#include "ui/button_factory.h"
#include "ui/clickable.h"

namespace game{

	namespace{

	//Inline makes it so that it is compiled on the spot
	sf::Clock clock_;
	sf::RenderWindow window_;

	auto tilemap_ptr_= std::make_unique<TileMap>();
	api::ai::NpcManager npc_manager_;

	ResourceManager resources_;
	BuildingManager building_manager_;

	// UI Elements
	std::unique_ptr<api::ui::Button> btnBlue;
	std::unique_ptr<api::ui::Button> btnRed;
	std::unique_ptr<api::ui::Button> btnGreen;

        api::ui::ButtonFactory btn_factory;

        //api::ai::NpcType npc_adding_type = building_manager_;


	  void Setup() {
	    window_.create(sf::VideoMode({kWindowWidth,kWindowHeight}), "SFML window");

	    tilemap_ptr_->Setup();
	    resources_.Setup(tilemap_ptr_.get());
	    building_manager_.Setup(tilemap_ptr_.get());

	    /*building_manager_.OnReleasedLeft = []() {
	      std::cout << "Clicked tilemap" << "\n";
	      building_manager_.Add({32,48});
	    };*/

	    npc_manager_.Add(api::ai::NpcType::kGreen, tilemap_ptr_.get(), &resources_);
	    npc_manager_.Add(api::ai::NpcType::kBlue, tilemap_ptr_.get(), &resources_);
	    npc_manager_.Add(api::ai::NpcType::kRed, tilemap_ptr_.get(), &resources_);

	    btnBlue = btn_factory.CreateButton(sf::Vector2f(50.f, static_cast<float>(window_.getSize().y) - 50.f), "Blue");
            //btnBlue->OnReleasedLeft = []() { npc_adding_type = api::ai::NpcType::kBlue; };

	    btnRed = btn_factory.CreateButton(sf::Vector2f(150.f, static_cast<float>(window_.getSize().y)  - 50.f), "Red");
            //btnRed->OnReleasedLeft = []() { npc_adding_type = api::ai::NpcType::kRed; };

	    btnGreen = btn_factory.CreateButton(sf::Vector2f(250.f, static_cast<float>(window_.getSize().y)  - 50.f), "Green");
            //btnGreen->OnReleasedLeft = []() {npc_adding_type = api::ai::NpcType::kGreen; };

	  }
	}

	void Loop() {
	  Setup();


		//Start the game loop
		while (window_.isOpen())
		{
		        //Reset the clock each frame
		        const float deltaTime = clock_.restart().asSeconds();

			//Process events
			while (const std::optional event = window_.pollEvent())
			{
				//Close window: exit
				if (event->is<sf::Event::Closed>()) {
					window_.close();
				}

			  bool buttonsWasClicked = false;
			  btnBlue->HandleEvent(event, buttonsWasClicked);
			  btnRed->HandleEvent(event, buttonsWasClicked);
			  btnGreen->HandleEvent(event, buttonsWasClicked);

                          //building_manager_.HandleEvent(event, buttonsWasClicked);
			}

		        npc_manager_.Update(deltaTime);

			window_.clear();

			tilemap_ptr_->Draw(window_);
		        resources_.Draw(window_);
		        npc_manager_.Draw(window_);
		        building_manager_.Draw(window_);

		        btnBlue->Draw(window_);
		        btnRed->Draw(window_);
		        btnGreen->Draw(window_);

			window_.display();
		}
	}
//1 - Make button to place house
//2 - House automatically spawns one NPC

}
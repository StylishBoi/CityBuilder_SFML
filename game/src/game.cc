#include "game.h"

#include "resources/resources_manager.h"
#include "SFML/Graphics.hpp"
#include "ai/npc_manager.h"
#include "graphics/building_manager.h"
#include "graphics/tilemap.h"
#include "ui/button.h"
#include "ui/button_factory.h"
#include "ui/clickable.h"

#ifdef TRACY_ENABLE
#include <tracy/Tracy.hpp>
#endif
namespace game{
	namespace{

	//Inline makes it so that it is compiled on the spot
	sf::Clock clock_;
	sf::RenderWindow window_;

	auto tilemap_ptr_= std::make_unique<TileMap>();
	api::ai::NpcManager npc_manager_;

	ResourceManager resource_manager_;
	BuildingManager building_manager_;

	// UI Elements
        api::ui::ButtonFactory btn_factory;

	std::unique_ptr<api::ui::Button> btnBlue;
	std::unique_ptr<api::ui::Button> btnRed;
	std::unique_ptr<api::ui::Button> btnGreen;
        std::unique_ptr<api::ui::Button> btnExit;

        //Makes so base click has no NPC
	api::ai::NpcType npc_adding_type = api::ai::NpcType::kNone;



	void ChopEvent(int index, float quantity) {
	  std::cout << "chop event : " << index << "," << quantity << "\n";
	  if (quantity <= 0){
	    tilemap_ptr_->SetTile(index, TileMap::Tile::kFlowers);
	  }
	}

	  void Setup() {
	    window_.create(sf::VideoMode({kWindowWidth,kWindowHeight}), "SFML window");

	    tilemap_ptr_->Setup();
	    building_manager_.Setup(tilemap_ptr_.get());

	    tilemap_ptr_->OnReleasedLeft = []() {
	      std::cout << "Clicked tilemap" << "\n";
	      npc_manager_.Add(npc_adding_type,
                             tilemap_ptr_.get(),
                             TileMap::TilePos(sf::Mouse::getPosition(window_)),
                             resource_manager_);
	      npc_adding_type = api::ai::NpcType::kNone;
	    };

	    btnBlue = btn_factory.CreateButton(sf::Vector2f(50.f, static_cast<float>(window_.getSize().y) - 50.f), "Lumberjack");
            btnBlue->OnReleasedLeft = []() { npc_adding_type = api::ai::NpcType::kBlueLumberjack; };

	    btnRed = btn_factory.CreateButton(sf::Vector2f(150.f, static_cast<float>(window_.getSize().y)  - 50.f), "Miner");
            btnRed->OnReleasedLeft = []() { npc_adding_type = api::ai::NpcType::kRedMiner; };

	    btnGreen = btn_factory.CreateButton(sf::Vector2f(250.f, static_cast<float>(window_.getSize().y)  - 50.f), "Gatherer");
            btnGreen->OnReleasedLeft = []() {npc_adding_type = api::ai::NpcType::kGreenGatherer; };

            btnExit = btn_factory.CreateButton(sf::Vector2f(350.f, static_cast<float>(window_.getSize().y)  - 50.f), "Exit");
            btnExit->OnReleasedLeft = []() { window_.close(); };

	    resource_manager_.LoadResources(
                Resource::ResourceType::kWood,
                tilemap_ptr_->GetCollectibles(TileMap::Tile::kWood), ChopEvent);

	    resource_manager_.LoadResources(
                    Resource::ResourceType::kFood,
                    tilemap_ptr_->GetCollectibles(TileMap::Tile::kFood), ChopEvent);

	    resource_manager_.LoadResources(
                    Resource::ResourceType::kRock,
                    tilemap_ptr_->GetCollectibles(TileMap::Tile::kRock), ChopEvent);

	  }
	}

	void Loop() {
	  Setup();


		//Start the game loop
		while (window_.isOpen())
		{
                  #ifdef TRACY_ENABLE
                  ZoneNamedN(game_loop_event, "Game loop", true);
                  #endif
		        //Reset the clock each frame
		        const float deltaTime = clock_.restart().asSeconds();

			//Process events
			while (const std::optional event = window_.pollEvent())
			{
                          #ifdef TRACY_ENABLE
                          ZoneNamedN(event_handling_event, "Event handling", true);
                          #endif
				//Close window: exit
				if (event->is<sf::Event::Closed>()) {
					window_.close();
				}

			  bool buttonsWasClicked = false;
			  btnBlue->HandleEvent(event, buttonsWasClicked);
			  btnRed->HandleEvent(event, buttonsWasClicked);
			  btnGreen->HandleEvent(event, buttonsWasClicked);
                          btnExit->HandleEvent(event, buttonsWasClicked);


			  tilemap_ptr_->HandleEvent(event, buttonsWasClicked);
                          //building_manager_.HandleEvent(event, buttonsWasClicked);
			}

		        npc_manager_.Update(deltaTime);

			window_.clear();

			tilemap_ptr_->Draw(window_);
		        npc_manager_.Draw(window_);
		        building_manager_.Draw(window_);

		        btnBlue->Draw(window_);
		        btnRed->Draw(window_);
		        btnGreen->Draw(window_);
                        btnExit->Draw(window_);

			window_.display();

                        #ifdef TRACY_ENABLE
                        FrameMark;
                        #endif
		}
	}
//1 - Make button to place house
//2 - House automatically spawns one NPC

}
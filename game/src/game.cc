#include "game.h"

#include "ai/npc_manager.h"
#include "gameplay/resources_manager.h"
#include "graphics/building_manager.h"
#include "graphics/tilemap.h"
#include "ui/button.h"
#include "ui/button_factory.h"
#include "ui/clickable.h"
#include "ui/economy_display.h"
#include "ui/hover.h"

#ifdef TRACY_ENABLE
#include <tracy/Tracy.hpp>
#endif
namespace game {
namespace {

  //Inline makes it so that it is compiled on the spot
  sf::Clock clock_;
  sf::RenderWindow window_;

  auto tilemap_ptr_= std::make_unique<TileMap>();
  api::ai::NpcManager npc_manager_;

  ResourceManager resource_manager_;
  BuildingManager building_manager_;
  EconomyManager economy_manager_;

  // UI Elements
  api::ui::ButtonFactory btn_factory_;

  //std::unique_ptr<api::ui::EconomyDisplay> economy_display_;

  Hover hover_;

  std::unique_ptr<api::ui::Button> btn_blue_;
  std::unique_ptr<api::ui::Button> btn_red_;
  std::unique_ptr<api::ui::Button> btn_green_;
  std::unique_ptr<api::ui::Button> btn_exit_;

  //Makes so base click has no NPC
  api::ai::NpcType npc_adding_type = api::ai::NpcType::kNone;



  void ChopEvent(int index, float quantity) {
    std::cout << "Chop event : " << index << " : " << quantity << "\n";
    if (quantity <= 0){
      economy_manager_.IncreaseWoodEconomyBy(10);
      tilemap_ptr_->SetTile(index, TileMap::Tile::kFlowers);
    }
  }
  void MineEvent(int index, float quantity) {
    std::cout << "Mine event : " << index << " : " << quantity << "\n";
    if (quantity <= 0){
      economy_manager_.IncreaseStoneEconomyBy(10);
      tilemap_ptr_->SetTile(index, TileMap::Tile::kFlowers);
    }
  }

  void HarvestEvent(int index, float quantity) {
    std::cout << "Harvest event : " << index << " : " << quantity << "\n";
    if (quantity <= 0){
      economy_manager_.IncreaseFoodEconomyBy(10);
      tilemap_ptr_->SetTile(index, TileMap::Tile::kFlowers);
    }
  }
  void RespawnEvent(int index, Resource::ResourceType resource_type) {
    switch(resource_type){
      case Resource::ResourceType::kWood:
        tilemap_ptr_->SetTile(index, TileMap::Tile::kWood);
        break;
      case Resource::ResourceType::kFood:
        tilemap_ptr_->SetTile(index, TileMap::Tile::kFood);
        break;
      case Resource::ResourceType::kRock:
        tilemap_ptr_->SetTile(index, TileMap::Tile::kRock);
        break;
    }
  }

  void Setup() {
    window_.create(sf::VideoMode({kWindowWidth,kWindowHeight}), "SFML window");

    tilemap_ptr_->Setup();
    building_manager_.Setup(tilemap_ptr_.get());



    resource_manager_.LoadResources(
        Resource::ResourceType::kWood,
        tilemap_ptr_->GetCollectibles(TileMap::Tile::kWood), ChopEvent, RespawnEvent);

    resource_manager_.LoadResources(
        Resource::ResourceType::kFood,
        tilemap_ptr_->GetCollectibles(TileMap::Tile::kFood), HarvestEvent, RespawnEvent);

    resource_manager_.LoadResources(
        Resource::ResourceType::kRock,
        tilemap_ptr_->GetCollectibles(TileMap::Tile::kRock), MineEvent, RespawnEvent);

    tilemap_ptr_->OnReleasedLeft = []() {
      sf::Vector2f clickPos = TileMap::TilePos(sf::Mouse::getPosition(window_));

      auto walkables = tilemap_ptr_->GetWalkables();
      if (std::find(walkables.begin(), walkables.end(), clickPos) != walkables.end()) {
        //Verify if there is a building at the position
        if (!building_manager_.HasBuildingAt(clickPos)){
            if(building_manager_.BuildingStonePrice(npc_adding_type)<=economy_manager_.GetStoneEconomy() &&
              building_manager_.BuildingWoodPrice(npc_adding_type)<=economy_manager_.GetWoodEconomy()){
              npc_manager_.Add(
                  npc_adding_type, tilemap_ptr_.get(),
                  TileMap::TilePos(sf::Mouse::getPosition(window_)),
                  resource_manager_);
              building_manager_.Add(TileMap::TilePos(sf::Mouse::getPosition(window_)), npc_adding_type);
              economy_manager_.ReduceWoodEconomyBy(building_manager_.BuildingWoodPrice(npc_adding_type));
              economy_manager_.ReduceStoneEconomyBy(building_manager_.BuildingStonePrice(npc_adding_type));
            }
          }
        }
      npc_adding_type = api::ai::NpcType::kNone;
    };

    btn_blue_ = btn_factory_.CreateButton(sf::Vector2f(50.f, static_cast<float>(window_.getSize().y) - 50.f), "Lumberjack");
    btn_blue_->OnReleasedLeft = []() { npc_adding_type = api::ai::NpcType::kBlueLumberjack; };

    btn_red_ = btn_factory_.CreateButton(sf::Vector2f(150.f, static_cast<float>(window_.getSize().y)  - 50.f), "Miner");
    btn_red_->OnReleasedLeft = []() { npc_adding_type = api::ai::NpcType::kRedMiner; };

    btn_green_ = btn_factory_.CreateButton(sf::Vector2f(250.f, static_cast<float>(window_.getSize().y)  - 50.f), "Gatherer");
    btn_green_->OnReleasedLeft = []() {npc_adding_type = api::ai::NpcType::kGreenGatherer; };

    btn_exit_ = btn_factory_.CreateButton(sf::Vector2f(350.f, static_cast<float>(window_.getSize().y)  - 50.f), "Exit");
    btn_exit_->OnReleasedLeft = []() { window_.close(); };
  }
}

void Loop() {
  Setup();


  //Start the game loop
  while (window_.isOpen()) {
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

      bool buttons_was_clicked_ = false;
      btn_blue_->HandleEvent(event, buttons_was_clicked_);
      btn_red_->HandleEvent(event, buttons_was_clicked_);
      btn_green_->HandleEvent(event, buttons_was_clicked_);
      btn_exit_->HandleEvent(event, buttons_was_clicked_);

      tilemap_ptr_->HandleEvent(event, buttons_was_clicked_);
    }

    npc_manager_.Update(deltaTime);
    resource_manager_.UpdateResources(deltaTime);
    hover_.Update(TileMap::TilePos(sf::Mouse::getPosition(window_)));

    window_.clear();

    tilemap_ptr_->Draw(window_);
    resource_manager_.Draw(window_);
    building_manager_.Draw(window_);
    npc_manager_.Draw(window_);

    //economy_display_->Draw(window_);

    if(npc_adding_type!=api::ai::NpcType::kNone){
      hover_.Draw(window_);
    }

    btn_blue_->Draw(window_);
    btn_red_->Draw(window_);
    btn_green_->Draw(window_);
    btn_exit_->Draw(window_);

    window_.display();

#ifdef TRACY_ENABLE
    FrameMark;
#endif
  }
}
}

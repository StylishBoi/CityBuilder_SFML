#include "graphics/building_manager.h"

void BuildingManager::Setup(const TileMap* tileMap) {
  textures.LoadAssets(files);

  tileMap_ = tileMap;
}

void BuildingManager::Add(sf::Vector2f position, api::ai::NpcType npcType) {
  auto building_type = Building::kNone;

  switch(npcType){
    case api::ai::NpcType::kBlueLumberjack:
      building_type = Building::kLumberHouse;
      break;
    case api::ai::NpcType::kRedMiner:
      building_type = Building::kMinerHouse;
      break;
    case api::ai::NpcType::kGreenGatherer:
      building_type = Building::kGathererHouse;
      break;
    default:
      return;
  }
  buildingPositions_.emplace_back(building_type,position);
}


void BuildingManager::Draw(sf::RenderWindow &window){

  sf::Sprite sprite(textures.GetAsset(Building::kLumberHouse));

  for (auto [building, position] : buildingPositions_) {
    sprite.setPosition(position);
    sprite.setTexture(textures.GetAsset(building));
    window.draw(sprite);
  }
}

bool BuildingManager::HasBuildingAt(const sf::Vector2f &position) const {

  for (auto [building, pos] : buildingPositions_) {

    if (pos.x == position.x && pos.y == position.y) {
      return true;
    }
  }
  return false;
}
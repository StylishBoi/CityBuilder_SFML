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

int BuildingManager::BuildingWoodPrice(api::ai::NpcType npcType) {
  switch (npcType) {
    case api::ai::NpcType::kBlueLumberjack:
      return 20;
    case api::ai::NpcType::kRedMiner:
      return 10;
    case api::ai::NpcType::kGreenGatherer:
      return 20;
    default:
      return 0;
  }
}
int BuildingManager::BuildingStonePrice(api::ai::NpcType npcType) {
  switch (npcType) {
    case api::ai::NpcType::kBlueLumberjack:
      return 10;
    case api::ai::NpcType::kRedMiner:
      return 20;
    case api::ai::NpcType::kGreenGatherer:
      return 20;
    default:
      return 0;
  }
}
void BuildingManager::RemoveBuildingAt(const sf::Vector2f &position) {
  int index=0;
  for (auto [building, building_position] : buildingPositions_) {
    if(position.x == building_position.x && position.y == building_position.y){
      buildingPositions_.erase(buildingPositions_.begin()+index);
    }
    index++;
  }
}

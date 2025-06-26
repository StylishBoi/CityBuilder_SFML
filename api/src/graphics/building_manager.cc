#include "graphics/building_manager.h"

void BuildingManager::Setup(const TileMap* tileMap) {
  textures.LoadAssets(files);

  tileMap_ = tileMap;

  buildingPositions_.emplace_back(Building::kHouse, sf::Vector2f(320, 240));
}

void BuildingManager::Add(sf::Vector2f position) {
  buildingPositions_.emplace_back(Building::kHouse,position);
}


void BuildingManager::Draw(sf::RenderWindow &window){

  sf::Sprite sprite(textures.GetAsset(Building::kHouse));

  for (auto [building, position] : buildingPositions_) {
    sprite.setPosition(position);
    sprite.setTexture(textures.GetAsset(building));
    window.draw(sprite);
  }
}
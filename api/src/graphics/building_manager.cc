#include "graphics/building_manager.h"

void BuildingManager::Setup(const TileMap* tileMap) {
  textures.LoadAssets(files);

  tileMap_ = tileMap;

  buildingPositions_.emplace_back(Building::kLumberHouse, sf::Vector2f(320, 240));
}

void BuildingManager::Add(sf::Vector2f position) {
  buildingPositions_.emplace_back(Building::kLumberHouse,position);
}


void BuildingManager::Draw(sf::RenderWindow &window){

  sf::Sprite sprite(textures.GetAsset(Building::kLumberHouse));

  for (auto [building, position] : buildingPositions_) {
    sprite.setPosition(position);
    sprite.setTexture(textures.GetAsset(building));
    window.draw(sprite);
  }
}
#include "graphics/building_manager.h"

#include <iostream>

void BuildingManager::Setup(const TileMap* tileMap) {
  textures.LoadAssets(files);

  tileMap_ = tileMap;

  buildingPositions_.emplace_back(Building::kHouse, sf::Vector2f(320, 240));
}

void BuildingManager::Draw(sf::RenderWindow &window){

  sf::Sprite sprite(textures.GetAsset(Building::kHouse));

  for (auto building : buildingPositions_) {
    sprite.setPosition(building.second);
    sprite.setTexture(textures.GetAsset(building.first));
    window.draw(sprite);
  }
}
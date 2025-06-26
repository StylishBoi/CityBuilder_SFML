#include <iostream>
#include <random>

#include "graphics/resources_manager.h"

void Resources::Setup(const TileMap* tileMap) {
  textures.LoadAssets(files);

  tileMap_ = tileMap;
  const auto walkableTiles = tileMap_->GetWalkables();

  std::random_device random_device;
  std::mt19937 engine{random_device()};

  for (int numberOfResources=5; numberOfResources>0; numberOfResources--) {
    std::uniform_int_distribution<int> dist(0, walkableTiles.size() - 1);
    sf::Vector2f random_element = walkableTiles[dist(engine)];
    resourcePositions_.emplace_back(Resource::kWood, sf::Vector2f(random_element));
  }
}

void Resources::Draw(sf::RenderWindow &window){

  sf::Sprite sprite(textures.GetAsset(Resource::kWood));

  for (auto element : resourcePositions_) {
    sprite.setPosition(element.second);
    sprite.setTexture(textures.GetAsset(element.first));
    window.draw(sprite);
  }
}
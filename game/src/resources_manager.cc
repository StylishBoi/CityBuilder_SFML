#include "../include/resources_manager.h"

#include <random>

void ResourceManager::Setup(const TileMap* tileMap) {
  textures.LoadAssets(files);

  tileMap_ = tileMap;
  const auto walkableTiles = tileMap_->GetWalkables();

  std::random_device random_device;
  std::mt19937 engine{random_device()};

  for (int numberOfResources=10; numberOfResources>0; numberOfResources--) {
    std::uniform_int_distribution<int> dist(0, static_cast<int>(walkableTiles.size()) - 1);
    sf::Vector2f random_element = walkableTiles[dist(engine)];

    std::uniform_int_distribution<int> res(0, static_cast<size_t>(Resource::kLength) - 1);
    auto random_resource = static_cast<Resource>(res(engine) );
    resourcePositions_.emplace_back(random_resource, sf::Vector2f(random_element));
  }
}

void ResourceManager::Draw(sf::RenderWindow &window){

  sf::Sprite sprite(textures.GetAsset(Resource::kWood));

  for (auto [resource, position] : resourcePositions_) {
    sprite.setPosition(position);
    sprite.setTexture(textures.GetAsset(resource));
    window.draw(sprite);
  }
}
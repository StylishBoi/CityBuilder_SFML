#include "resources/resources_manager.h"

#include <random>
#include <iostream>

void ResourceManager::LoadResources(Resource::ResourceType type,
                                    std::vector<int> indexes,
                                    std::function<void(int, float)> OnChopEvent)
{
  for (auto& index : indexes) {
    resources_.emplace_back();
    resources_.back().SetType(type);
    resources_.back().SetIndex(index);
    resources_.back().SetQuantity(10);
    resources_.back().OnChopRessource_ = OnChopEvent;
  }
}

const std::vector<Resource> ResourceManager::GetResources(
    Resource::ResourceType type) const {
  std::vector<Resource> resources_of_type = {};

  for (const auto& resource : resources_) {
    if (resource.GetType() == type) {
      resources_of_type.emplace_back(resource);
    }
  }
  return resources_of_type;
}

void ResourceManager::Draw(sf::RenderWindow &window) {
  sf::Sprite sprite(textures.GetAsset(Tile::kGrass));
  for (auto& resource : resources_) {
    sprite.setTexture(textures.GetAsset(static_cast<TileMap::Tile>(resource.GetType())));
    sprite.setPosition(ScreenPosition(resource.GetTileIndex()));
    window.draw(sprite);
  }
};
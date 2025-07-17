#include "gameplay/resources_manager.h"

#include <random>
#include <iostream>

void ResourceManager::LoadResources(Resource::ResourceType type,
                                    std::vector<int> indexes,
                                    std::function<void(int, float)> on_chop_event)
{
  std::cout << "Loading gameplay of type " << static_cast<int>(type)
            << " with " << indexes.size() << " indexes\n";

  for (auto& index : indexes) {
    resources_.emplace_back(std::make_unique<Resource>());
    resources_.back()->SetType(type);
    resources_.back()->SetIndex(index);
    resources_.back()->SetQuantity(10);
    resources_.back()->SetWorkStatus(false);
    resources_.back()->on_chop_resource_ = on_chop_event;

    std::cout << "This resource has been added : " << resources_.size() << "\n";
  }
  std::cout << "Total resources after loading: " << resources_.size() << "\n";

}

std::vector<Resource*> ResourceManager::GetResources(Resource::ResourceType type)
    const {

  auto resources_of_type = std::vector<Resource*>();

  for (auto& resource : resources_) {
    if (resource->GetType() == type) {
      resources_of_type.push_back(resource.get());
    }
  }
  return resources_of_type;
}

void ResourceManager::Draw(sf::RenderWindow& window) {
  sf::Sprite sprite(textures.GetAsset(Tile::kGrass));
  for (auto& resource : resources_) {
    sprite.setTexture(textures.GetAsset(static_cast<TileMap::Tile>(resource->GetType())));
    sprite.setPosition(ScreenPosition(resource->GetTileIndex()));
    window.draw(sprite);
  }
};
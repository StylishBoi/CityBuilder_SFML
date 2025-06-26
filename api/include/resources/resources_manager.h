#ifndef RESOURCES_H
#define RESOURCES_H

#include "assets/asset_manager.h"
#include "graphics/tilemap.h"
#include "resource.h"

class ResourceManager : public TileMap {

  std::vector<Resource> resources_;

  // Tilemap
public:
  void LoadResources(Resource::ResourceType type, std::vector<int> indexes, std::function<void(int, float)> OnChopEvent);

  [[nodiscard]] const std::vector<Resource> GetResources(Resource::ResourceType type) const;
};

inline void ResourceManager::LoadResources(
        Resource::ResourceType type, std::vector<int> indexes,
        std::function<void(int, float)> OnChopEvent) {
  for (auto& index : indexes) {
    resources_.emplace_back();
    resources_.back().SetType(type);
    resources_.back().SetIndex(index);
    resources_.back().SetQuantity(10);
    resources_.back().OnChopRessource_ = OnChopEvent;
  }
}

inline const std::vector<Resource> ResourceManager::GetResources(
        Resource::ResourceType type) const {
  std::vector<Resource> ressources_of_type = {};

  for (const auto& ressource : resources_) {
    if (ressource.GetType() == type) {
      ressources_of_type.emplace_back(ressource);
    }
  }
  return ressources_of_type;
}

#endif //RESOURCES_H

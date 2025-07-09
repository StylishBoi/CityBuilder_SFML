#ifndef RESOURCES_H
#define RESOURCES_H

#include "assets/asset_manager.h"
#include "graphics/tilemap.h"
#include "resource.h"
#include <SFML/Graphics.hpp>

class ResourceManager : public TileMap {

  std::vector<Resource> resources_;

  // Tilemap
public:
  void LoadResources(Resource::ResourceType type, std::vector<int> indexes, std::function<void(int, float)> OnChopEvent);
  [[nodiscard]] const std::vector<Resource> GetResources(Resource::ResourceType type) const;
  void Draw(sf::RenderWindow &window);
};

#endif //RESOURCES_H

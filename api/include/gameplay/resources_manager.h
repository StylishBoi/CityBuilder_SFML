#ifndef RESOURCES_H
#define RESOURCES_H

#include "assets/asset_manager.h"
#include "graphics/tilemap.h"
#include "resource.h"
#include <SFML/Graphics.hpp>

class ResourceManager : public TileMap {

  std::vector<Resource> resources_;
  std::vector<Resource> wood_resources_;
  std::vector<Resource> stone_resources_;
  std::vector<Resource> food_resources_;

  // Tilemap
public:
  void LoadResources(Resource::ResourceType type, std::vector<int> indexes, std::function<void(int, float)> on_chop_event);
  [[nodiscard]] std::vector<Resource> GetResources(Resource::ResourceType type) const;
  void Draw(sf::RenderWindow& window);
};

#endif //RESOURCES_H

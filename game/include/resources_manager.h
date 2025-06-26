#ifndef RESOURCES_H
#define RESOURCES_H

#include "graphics/tilemap.h"
#include "assets/asset_manager.h"

class ResourceManager : public TileMap {
  // Texture
  enum class Resource {
    kWood,
    kFood,
    kRock,
    kLength
  };
  std::string_view files[static_cast<size_t>(Resource::kLength)]{"wood.png", "food.png", "rock.png"};
  core::experimental::AssetManager<sf::Texture, Resource, "_assets/sprites"> textures;

  // Tilemap
  const TileMap* tileMap_ = nullptr;

public:
  //Position
  std::vector<std::pair<Resource, sf::Vector2f>> resourcePositions_;

  void Setup(const TileMap* tileMap);
  void Draw(sf::RenderWindow &window);
};
#endif //RESOURCES_H

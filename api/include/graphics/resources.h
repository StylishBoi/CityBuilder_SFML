#ifndef RESOURCES_H
#define RESOURCES_H

#include "graphics/tilemap.h"
#include "assets/asset_manager.h"

class Resources : public TileMap {
  // Texture
  enum class Resource {
    kWood,
    kFood,
    kLength
  };
  std::string_view files[static_cast<size_t>(Resource::kLength)]{"wood.png", "food.png"};
  core::experimental::AssetManager<sf::Texture, Resource, "_assets/sprites"> textures;

  // Tilemap
  const TileMap* tileMap_;

  //Position
  std::vector<std::pair<Resource, sf::Vector2f>> position_;

public:
  //Position commands
  /*void SetPosition(sf::Vector2f position, int idx){position_[idx] = position;}
  [[nodiscard]] const sf::Vector2f& GetPosition(int idx) const{return position_[idx];}*/

  void Setup(const TileMap* tileMap);
  void Draw(sf::RenderWindow &window);
};
#endif //RESOURCES_H

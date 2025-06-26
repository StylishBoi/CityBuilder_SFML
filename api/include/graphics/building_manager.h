#ifndef BUILDING_MANAGER_H
#define BUILDING_MANAGER_H

#include "graphics/tilemap.h"
#include "assets/asset_manager.h"

class BuildingManager : public TileMap {

  enum class Building {
    kHouse,
    kRestaurant,
    kLength
  };

  std::string_view files[static_cast<size_t>(Building::kLength)]{"building.png", "restaurant.png"};
  core::experimental::AssetManager<sf::Texture, Building, "_assets/sprites"> textures;

  // Tilemap
  const TileMap* tileMap_ = nullptr;

public:
  //Position
  std::vector<std::pair<Building, sf::Vector2f>> buildingPositions_;

  void Setup(const TileMap* tileMap);
  void Add(sf::Vector2f position);
  void Draw(sf::RenderWindow &window);
};
#endif //BUILDING_MANAGER_H

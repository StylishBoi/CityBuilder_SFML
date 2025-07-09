#ifndef BUILDING_MANAGER_H
#define BUILDING_MANAGER_H

#include <SFML/Graphics.hpp>

#include "ai/npc_manager.h"
#include "assets/asset_manager.h"
#include "graphics/tilemap.h"

class BuildingManager : public TileMap {

  enum class Building {
    kLumberHouse,
    kMinerHouse,
    kGathererHouse,
    kLength
  };

  std::string_view files[static_cast<size_t>(Building::kLength)]{"lumber_house.png", "miner_house.png", "gatherer_house.png"};
  core::experimental::AssetManager<sf::Texture, Building, "_assets/sprites"> textures;

  // Tilemap
  const TileMap* tileMap_ = nullptr;

public:
  //Position
  std::vector<std::pair<Building, sf::Vector2f>> buildingPositions_;

  void Setup(const TileMap* tileMap);
  void Add(sf::Vector2f position, api::ai::NpcType npcType);
  void Draw(sf::RenderWindow &window);
};
#endif //BUILDING_MANAGER_H

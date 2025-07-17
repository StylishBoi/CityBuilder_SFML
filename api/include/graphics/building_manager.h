#ifndef BUILDING_MANAGER_H
#define BUILDING_MANAGER_H

#include <SFML/Graphics.hpp>

#include "ai/npc_manager.h"
#include "assets/asset_manager.h"
#include "graphics/tilemap.h"

class BuildingManager : public TileMap {

  enum class Building {
    kNone,
    kLumberHouse,
    kMinerHouse,
    kGathererHouse,
    kLength
  };

  std::string_view files[static_cast<size_t>(Building::kLength)]{"empty.png","lumber_house.png", "miner_house.png", "gatherer_house.png"};
  core::experimental::AssetManager<sf::Texture, Building, "_assets/sprites"> textures;

  // Tilemap
  const TileMap* tileMap_ = nullptr;

public:
  //Position
  std::vector<std::pair<Building, sf::Vector2f>> buildingPositions_;

  void Setup(const TileMap* tileMap);
  void Add(sf::Vector2f position, api::ai::NpcType npcType);
  void Draw(sf::RenderWindow &window);
  bool HasBuildingAt(const sf::Vector2f& position) const;

  //Building prices
  static int BuildingWoodPrice(api::ai::NpcType npcType);
  static int BuildingStonePrice(api::ai::NpcType npcType);

};
#endif //BUILDING_MANAGER_H

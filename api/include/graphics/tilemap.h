#ifndef API_GRAPHICS_TILEMAP_H
#define API_GRAPHICS_TILEMAP_H

#include "assets/asset_manager.h"
#include "ui/clickable.h"
#include <SFML/Graphics.hpp>

// Window variables
constexpr static int kWindowWidth = 640;
constexpr static int kWindowHeight= 640;
const static int kTileSize=16;

using core::experimental::AssetManager;

class TileMap : public api::ui::Clickable{
public:
  enum class Tile {
    kGrass,
    kWater,
    kFlowers,
    kSand,
    kRock,
    kNpc,
    kWood,
    kFood,
    kLength
  };

  std::string_view files[static_cast<size_t>(Tile::kLength)]{"grass.png", "water.png", "flowers.png", "sand.png", "rock_with_bg.png","npc.png", "wood_with_bg.png", "food_with_bg.png"};

private:
  std::array<Tile, (kWindowWidth/kTileSize) * (kWindowHeight/kTileSize)> tiles_={};

  std::vector<sf::Vector2f> walkables_;

protected:
 static int Index(sf::Vector2f screenPosition);
 AssetManager<sf::Texture, Tile, "_assets/sprites"> textures;

public:
  explicit TileMap();
  void Setup();
  virtual void Draw(sf::RenderWindow &window);
  void SetTile(int, Tile);

  static sf::Vector2f ScreenPosition(int index);
  static sf::Vector2f TilePos(sf::Vector2i);

  std::vector<sf::Vector2f> GetWalkables() { return walkables_; };
  std::vector<int> GetCollectibles(Tile);
};
#endif

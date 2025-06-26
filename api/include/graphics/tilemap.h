#ifndef API_GRAPHICS_TILEMAP_H
#define API_GRAPHICS_TILEMAP_H

#include "assets/asset_manager.h"
#include <SFML/Graphics.hpp>

// Window variables
constexpr static int kWindowWidth = 640;
constexpr static int kWindowHeight= 640;
const static int kTileSize=16;

using core::experimental::AssetManager;

class TileMap{
public:
  enum class Tile {
    kGrass,
    kWater,
    kFlowers,
    kSand,
    kRock,
    kNpc,
    kLength
  };

  std::string_view files[static_cast<size_t>(Tile::kLength)]{"grass.png", "water.png", "flowers.png", "sand.png", "rock.png","npc.png"};

private:
  std::array<Tile, (kWindowWidth/kTileSize) * (kWindowHeight/kTileSize)> tiles_={};
  AssetManager<sf::Texture, Tile, "_assets/sprites"> textures;

  std::vector<sf::Vector2f> walkables_;

protected:
  static sf::Vector2f ScreenPosition(int index);
  static int Index(sf::Vector2f screenPosition);

public:
  explicit TileMap();
  void Setup();
  void Draw(sf::RenderWindow &window);

  static sf::Vector2f TilePos(sf::Vector2i);

  std::vector<sf::Vector2f> GetWalkables() const{ return walkables_; };
};
#endif

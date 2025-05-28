#ifndef API_GRAPHICS_TILEMAP_H
#define API_GRAPHICS_TILEMAP_H

#include "SFML/Graphics.hpp"
#include "assets/asset_manager.h"

// Window variables
constexpr int kWindowWidth = 640;
constexpr int kWindowHeight=480;
constexpr int kTileSize=16;

class TileMap{
  enum class Tile {
    GRASS,
    WATER,
    FLOWERS,
    SAND
  };

private:
  std::array<Tile, kWindowWidth/kTileSize * (kWindowHeight/kTileSize)> tiles_={};
  AssetManager<sf::Texture> textures;

  static sf::Vector2f ScreenPosition(int index);
  static int Index(sf::Vector2f screenPosition);

public:
  explicit TileMap();
  void Setup();
  void Draw(sf::RenderWindow &window);
};
#endif

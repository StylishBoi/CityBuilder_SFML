#ifndef API_GRAPHICS_TILEMAP_H
#define API_GRAPHICS_TILEMAP_H

#include "SFML/Graphics.hpp"

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
  std::array<Tile, (kWindowWidth/kTileSize) * (kWindowHeight/kTileSize)> tiles_={};

  sf::Texture sand_texture_;
  sf::Texture grass_texture_;
  sf::Texture water_texture_;
  sf::Texture flower_texture_;

  static sf::Vector2f ScreenPosition(int index);
  static int Index(sf::Vector2f screenPosition);

public:
  void Setup();
  void Draw(sf::RenderWindow &window) const;
};
#endif

#include "graphics/tilemap.h"

#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

void TileMap::Draw(sf::RenderWindow &window) const{
  int tileIndex=0;

  sf::Sprite sprite(water_texture_);

  for (auto tile: tiles_) {

  //Decide the sprite of the tile
    switch (tile) {
      case Tile::WATER:
        sprite.setTexture(water_texture_);
        break;
      case Tile::GRASS:
        sprite.setTexture(grass_texture_);
        break;
      case Tile::FLOWERS:
        sprite.setTexture(flower_texture_);
        break;
      case Tile::SAND:
        sprite.setTexture(sand_texture_);
        break;
      default:
        sprite.setTexture(water_texture_);
        break;

    }
    sprite.setPosition(ScreenPosition(tileIndex));
    window.draw(sprite);
  }
  tileIndex++;
}

sf::Vector2f TileMap::ScreenPosition(const int index) {
  float x=ceil((index%(kWindowWidth/kTileSize))*kTileSize);
  float y=ceil((index/(kWindowHeight/kTileSize))*kTileSize);

  return{x,y};
}

int TileMap::Index(const sf::Vector2f screenPosition) {
  return static_cast<int>(ceil(screenPosition.y/kTileSize)*kWindowWidth) +
    static_cast<int>(ceil(screenPosition.x/kTileSize));
}

void TileMap::Setup(){
  grass_texture_.loadFromFile("../_assets/sprites/grass.png");
  water_texture_.loadFromFile("../_assets/sprites/water.png");
  flower_texture_.loadFromFile("../_assets/sprites/flowers.png");
  sand_texture_.loadFromFile("../_assets/sprites/sand.png");

  tiles_.fill(Tile::WATER);
}
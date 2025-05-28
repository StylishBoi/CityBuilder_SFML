#include "graphics/tilemap.h"

#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

TileMap::TileMap() : textures("../_assets/sprites/"){
}

void TileMap::Setup(){

  textures.LoadAssets();
  tiles_.fill(Tile::GRASS);
}

void TileMap::Draw(sf::RenderWindow &window){
  int tileIndex=0;

  sf::Sprite sprite(textures.GetAsset(AssetManager<sf::Texture>::TextureIndex::kDefault));

  for (auto tile: tiles_) {

  //Decide the sprite of the tile
    switch (tile) {
      case Tile::WATER:
        sprite.setTexture(textures.GetAsset(AssetManager<sf::Texture>::TextureIndex::kWater));
        break;
      case Tile::GRASS:
        sprite.setTexture(textures.GetAsset(AssetManager<sf::Texture>::TextureIndex::kGrass));
        break;
      case Tile::FLOWERS:
        sprite.setTexture(textures.GetAsset(AssetManager<sf::Texture>::TextureIndex::kFlowers));
        break;
      case Tile::SAND:
        sprite.setTexture(textures.GetAsset(AssetManager<sf::Texture>::TextureIndex::kSand));
        break;
      default:
        sprite.setTexture(textures.GetAsset(AssetManager<sf::Texture>::TextureIndex::kWater));
        break;

    }
    sprite.setPosition(ScreenPosition(tileIndex));
    window.draw(sprite);

    tileIndex++;
  }
}

sf::Vector2f TileMap::ScreenPosition(const int index) {
  float x=ceil((index%(kWindowWidth/kTileSize))*kTileSize);
  float y=ceil((index/(kWindowWidth/kTileSize))*kTileSize);

  return{x,y};
}

int TileMap::Index(const sf::Vector2f screenPosition) {
  return static_cast<int>(ceil(screenPosition.y/kTileSize)*kWindowWidth) +
         static_cast<int>(ceil(screenPosition.x/kTileSize));
}
#include "graphics/tilemap.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "graphics/directions.h"
#include "graphics/map_generation.h"

TileMap::TileMap(){}

MapGeneration map_generation;
Directions directions;

void TileMap::Setup(){
  directions.Setup();
  textures.LoadAssets(files);
  tiles_.fill(Tile::kWater);

  auto grassSpots=map_generation.Drunkard();
  for (auto grass : grassSpots) {
    tiles_[grass]=Tile::kGrass;
  }

  auto newPositions=map_generation.MapThickening();
  for (auto newPosition : newPositions) {
    tiles_[newPosition]=Tile::kGrass;
  }

  auto sandPositions=map_generation.SandUpdate();
  for (auto sandPosition : sandPositions) {
    tiles_[sandPosition]=Tile::kSand;
  }
}

void TileMap::Draw(sf::RenderWindow &window){
  int tileIndex=0;

  sf::Sprite sprite(textures.GetAsset(Tile::kGrass));

  for (auto element: tiles_) {

    sprite.setPosition(ScreenPosition(tileIndex));

    if (element==Tile::kNpc || element==Tile::kFood || element==Tile::kRock) {
      sprite.setTexture(textures.GetAsset(Tile::kGrass));
      window.draw(sprite);
      sprite.setTexture(textures.GetAsset(element));
      window.draw(sprite);
    }
    else {
      sprite.setTexture(textures.GetAsset(element));
      window.draw(sprite);
    }

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
#include "graphics/tilemap.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "graphics/directions.h"
#include "graphics/map_generation.h"

TileMap::TileMap()= default;

MapGeneration map_generation;
Directions directions;

void TileMap::Setup(){
  Directions::Setup();
  textures.LoadAssets(files);
  tiles_.fill(Tile::kWater);

  //Sets up the grass island
  auto grassSpots=map_generation.Drunkard();
  for (auto grass : grassSpots) {
    tiles_[grass]=Tile::kGrass;
  }

  //Increase the size of the island
  auto newPositions=map_generation.MapThickening();
  for (auto newPosition : newPositions) {
    tiles_[newPosition]=Tile::kGrass;
  }

  //Fill up potential holes on the island
  auto holePositions=map_generation.HoleFilling();
  for (auto holePosition : holePositions) {
    tiles_[holePosition]=Tile::kFlowers;
  }
  //Adds sand to the island
  auto sandPositions=map_generation.SandUpdate();
  for (auto sandPosition : sandPositions) {
    tiles_[sandPosition]=Tile::kSand;
  }

  for (int tileIndex = 0; tileIndex < tiles_.size(); ++tileIndex) {
    if (tiles_[tileIndex]==Tile::kGrass || tiles_[tileIndex]==Tile::kFlowers || tiles_[tileIndex]==Tile::kSand) {
      sf::Vector2f pos = ScreenPosition(tileIndex);
      walkables_.push_back(pos);
      std::cout<<pos.x<<", "<<pos.y<<std::endl;
    }
  }
}

void TileMap::Draw(sf::RenderWindow &window){
  int tileIndex=0;

  sf::Sprite sprite(textures.GetAsset(Tile::kGrass));

  for (auto element: tiles_) {

    sprite.setPosition(ScreenPosition(tileIndex));
    sprite.setTexture(textures.GetAsset(element));
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

sf::Vector2f TileMap::TilePos(sf::Vector2i pos) {

  return {static_cast<float>(ceil(pos.x / kTileSize) * kTileSize),
          static_cast<float>(ceil(pos.y / kTileSize) * kTileSize)};

}
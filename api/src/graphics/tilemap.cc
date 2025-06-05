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

  auto grassSpots=map_generation.MapGeneration::Drunkard();

  for (auto grass : grassSpots) {
    tiles_[((grass.x%+grass.y)%40)*kTileSize]=Tile::kGrass;
  }
  tiles_[0]=Tile::kGrass;
  tiles_[39]=Tile::kGrass;
  tiles_[1549]=Tile::kGrass;
  tiles_[1599]=Tile::kGrass;
  std::cout<<tiles_.size()<<std::endl;
}

void TileMap::Draw(sf::RenderWindow &window){
  int tileIndex=0;

  sf::Sprite sprite(textures.GetAsset(Tile::kGrass));

  for (auto element: tiles_) {

    sprite.setTexture(textures.GetAsset(element));
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
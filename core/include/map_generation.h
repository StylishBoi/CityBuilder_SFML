#ifndef MAP_GENERATION_H
#define MAP_GENERATION_H
#include "../../api/include/graphics/tilemap.h"

class MapGeneration
{
private:
  //PCG Generation
  int walkIterMax=30;
  int walkDistanceMin=2;
  int walkDistanceMax=4;
  int walkBounds=kTileSize*3;

  //Set the grid tile size
  constexpr int numberOfWidthTiles = static_cast<int>(kWindowWidth)/kTileSize;
  constexpr int numberOfHeightTiles = static_cast<int>(kWindowHeight)/kTileSize;

public:
  std::array<TileMap::Tile, kWindowWidth/kTileSize * (kWindowHeight/kTileSize)> Drunkard();

private:

};
#endif //MAP_GENERATION_H

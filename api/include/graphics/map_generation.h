#ifndef MAP_GENERATION_H
#define MAP_GENERATION_H
#include "D:\Module 4\NewCityBuilder\api\include\graphics\tilemap.h"

class MapGeneration
{
private:
  //PCG Generation
  int walkIterMax=30;
  int walkDistanceMin=4;
  int walkDistanceMax=7;
  int walkBounds=kTileSize*3;
  std::vector<sf::Vector2i> usedTiles;

  //Set the grid tile size
  int numberOfWidthTiles = static_cast<int>(kWindowWidth/kTileSize);
  int numberOfHeightTiles = static_cast<int>(kWindowHeight/kTileSize);

public:
  std::array<int, 150> Drunkard();
  std::vector<int> MapThickening();
  std::vector<int> HoleFilling();
  std::vector<int> SandUpdate();

private:

};
#endif //MAP_GENERATION_H

#ifndef MAP_GENERATION_H
#define MAP_GENERATION_H
#include "D:\Module 4\NewCityBuilder\api\include\graphics\tilemap.h"

class MapGeneration
{
private:
  //PCG Generation
  int walkIterMax=50;
  int walkDistanceMin=4;
  int walkDistanceMax=8;
  int walkBounds=kTileSize*3;

  //Set the grid tile size
  int numberOfWidthTiles = static_cast<int>(kWindowWidth/kTileSize);
  int numberOfHeightTiles = static_cast<int>(kWindowHeight/kTileSize);

public:
  std::vector<sf::Vector2i> Drunkard();

private:

};
#endif //MAP_GENERATION_H

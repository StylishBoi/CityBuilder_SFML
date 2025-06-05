#include "map_generation.h"
#include "directions.h"

#include <random>

std::array<TileMap::Tile, kWindowWidth/kTileSize * (kWindowHeight/kTileSize)> MapGeneration::Drunkard() {
  //Drunkard generation variables

  std::array<TileMap::Tile, kWindowWidth/kTileSize * (kWindowHeight/kTileSize)>grassPositions={};
  int walkAmounts=0;
  int walkDistance;
  sf::Vector2f newGrassSpot;
  std::vector<sf::Vector2f> generationPositions;

  sf::Vector2f startPosition=sf::Vector2f((numberOfWidthTiles/2)*kTileSize, (numberOfHeightTiles/2)*kTileSize);

  generationPositions.emplace_back(startPosition);

  //Drunkard generation loop
  while (walkAmounts<walkIterMax) {
    sf::Vector2f nextDirection = Directions::fourWayDirections[std::rand() % Directions::fourWayDirections.size()];
    walkDistance = std::rand() % (walkDistanceMax - walkDistanceMin) + walkDistanceMin;

    for (int walk = 0; walk < walkDistance; walk++) {
      newGrassSpot=generationPositions.back()+sf::Vector2f(nextDirection);

      if (newGrassSpot.x>(kWindowWidth-walkBounds) || newGrassSpot.x<walkBounds) {
        break;
      }
      if (newGrassSpot.y>(kWindowHeight-walkBounds) || newGrassSpot.y<walkBounds) {
        break;
      }
      grassPositions[(newGrassSpot.x/kTileSize)+(newGrassSpot.y/kTileSize)] = TileMap::Tile::GRASS;
    }
    generationPositions.clear();
    walkAmounts++;
  }

  return grassPositions;
}


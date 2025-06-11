#include "graphics/map_generation.h"
#include "graphics/tilemap.h"
#include "graphics/directions.h"

#include <random>
#include <vector>


std::array<int, 150> MapGeneration::Drunkard() {
  //Drunkard generation variables

  //Setup randomness
  srand(time(0));

  std::array<int, 150>grassPositions={};
  int currentIter=0;
  int distanceToWalk;
  int tilesConvertedToGrass=1;

  std::vector<sf::Vector2i> generationPositions;

  std::cout<<numberOfHeightTiles<<std::endl;
  std::cout<<numberOfWidthTiles<<std::endl;

  //Sets up the start
  sf::Vector2i newGrassSpot={320, 240};

  //Drunkard generation loop
  while (currentIter<walkIterMax) {
    //Decides next direction
    sf::Vector2i nextDirection = Directions::fourWayDirections[std::rand() % Directions::fourWayDirections.size()];
    //Decides the distance to walk
    distanceToWalk = std::rand() % (walkDistanceMax - walkDistanceMin) + walkDistanceMin;

    //----------------Walk amount of given steps----------------------
    for (int walk = 0; walk < distanceToWalk; walk++) {
      newGrassSpot=newGrassSpot+nextDirection;
      std::cout<<newGrassSpot.x<<" "<<newGrassSpot.y<<std::endl;

      //----------------BOUNDS LIMITS----------------------
      if (newGrassSpot.x>(kWindowWidth-walkBounds) || newGrassSpot.x<walkBounds) {
        break;
      }
      if (newGrassSpot.y>(kWindowHeight-walkBounds) || newGrassSpot.y<walkBounds) {
        break;
      }

      //----------------Register that loop of steps----------------------
      usedTiles.push_back(newGrassSpot);
      generationPositions.push_back(newGrassSpot);
    }
    //----------------Register all the steps of that loop----------------------
    for (auto step : generationPositions) {
      grassPositions[tilesConvertedToGrass]=(step.x/kTileSize)+((step.y/kTileSize)*40);
      std::cout<<step.x<<" "<<step.y<<std::endl;
      tilesConvertedToGrass++;
      if (tilesConvertedToGrass >= 150) {
        return grassPositions;
      }
    }
    //----------------Reset that loop number of steps----------------------
    newGrassSpot=generationPositions.back();
    generationPositions.clear();
    //Increase the amount of iter
    currentIter++;
  }
}

std::vector<int> MapGeneration::MapThickening() {
  std::vector<sf::Vector2i> newPositions;
  std::vector<int> returnPositions;
  for (auto usedTile : usedTiles) {
    for (auto direction : Directions::fourWayDirections) {
      newPositions.push_back(usedTile+direction);
    }
  }
  for (auto newPosition : newPositions) {
    returnPositions.push_back((newPosition.x/kTileSize)+((newPosition.y/kTileSize)*40));
    usedTiles.push_back(newPosition);
  }
  return returnPositions;
}

std::vector<int> MapGeneration::SandUpdate() {
  std::vector<int> returnPositions;
  for (auto usedTile : usedTiles) {
    for (auto direction : Directions::eightWayDirections) {
      if (std::find(usedTiles.begin(), usedTiles.end(), usedTile+direction) == usedTiles.end()) {
        returnPositions.push_back((usedTile.x/kTileSize)+((usedTile.y/kTileSize)*40));
      }
    }
  }
  return returnPositions;
}

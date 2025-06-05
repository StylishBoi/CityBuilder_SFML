#include "graphics/map_generation.h"
#include "graphics/tilemap.h"
#include "graphics/directions.h"

#include <random>
#include <vector>


std::vector<sf::Vector2i> MapGeneration::Drunkard() {
  //Drunkard generation variables

  //Setup randomness
  srand(time(0));

  std::vector<sf::Vector2i>grassPositions={};
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
      generationPositions.push_back(newGrassSpot);
    }
    //----------------Register all the steps of that loop----------------------
    for (auto step : generationPositions) {
      grassPositions.push_back(step);
      std::cout<<step.x<<" "<<step.y<<std::endl;
      tilesConvertedToGrass++;
      if (tilesConvertedToGrass >= 50) {
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


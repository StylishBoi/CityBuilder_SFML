#include "graphics/map_generation.h"
#include "graphics/tilemap.h"
#include "graphics/directions.h"

#include <random>
#include <vector>


std::array<int, 150> MapGeneration::Drunkard() {
  //Drunkard generation variables

  //Setup randomness
  std::random_device rd;
  std::mt19937 gen(rd());


  std::array<int, 150>grassPositions={};
  int currentIter=0;
  int tilesConvertedToGrass=0;

  std::vector<sf::Vector2i> generationPositions;

  std::cout<<numberOfHeightTiles<<std::endl;
  std::cout<<numberOfWidthTiles<<std::endl;

  //Sets up the start
  sf::Vector2i newGrassSpot={320, 240};

  //Drunkard generation loop
  while (currentIter<walkIterMax) {
    //Decides next direction
    std::uniform_int_distribution<> dirDist(0, Directions::fourWayDirections.size() - 1);
    sf::Vector2i nextDirection = Directions::fourWayDirections[dirDist(gen)];

    //Decides the distance to walk
    std::uniform_int_distribution<> walkDist(walkDistanceMin, walkDistanceMax - 1);
    int distanceToWalk = walkDist(gen);

    generationPositions.clear();

    //----------------Walk amount of given steps----------------------
    for (int walk = 0; walk < distanceToWalk; walk++) {
      newGrassSpot=newGrassSpot+nextDirection;
      std::cout<< newGrassSpot.x << " and " << newGrassSpot.y << std::endl;

      //----------------BOUNDS LIMITS----------------------
      if (newGrassSpot.x > (kWindowWidth - walkBounds) ||
          newGrassSpot.x < walkBounds ||
          newGrassSpot.y >(kWindowHeight-walkBounds)
        || newGrassSpot.y<walkBounds) {
        std::cout<<"Out of bounds attempt"<<std::endl;
        newGrassSpot={320, 240};
      }

      //----------------Register that loop of steps----------------------
      usedTiles.push_back(newGrassSpot);
      generationPositions.push_back(newGrassSpot);
    }
    //----------------Register all the steps of that loop----------------------
    for (auto step : generationPositions) {
      if (tilesConvertedToGrass >= 150) {
        break;
      }
      grassPositions[tilesConvertedToGrass++]=(step.x/kTileSize)+((step.y/kTileSize)*40);
    }
    //----------------Reset that loop number of steps----------------------
    if (!generationPositions.empty()) {
      newGrassSpot=generationPositions.back();
    }

    //Increase the amount of iter
    currentIter++;
  }
  return grassPositions;
}

std::vector<int> MapGeneration::MapThickening() {
  std::vector<sf::Vector2i> newPositions;
  std::vector<int> returnPositions;
  for (auto usedTile : usedTiles) {
    for (auto direction : Directions::fourWayDirections) {

      sf::Vector2i newPos = usedTile + direction;
      sf::Vector2i newPos2 = usedTile + (direction * 2);

      // Add bounds checking
      if (newPos.x >= walkBounds && newPos.x < (kWindowWidth-walkBounds) &&
          newPos.y >= walkBounds && newPos.y < (kWindowHeight-walkBounds)) {
          newPositions.push_back(newPos);
          }

      if (newPos2.x >= walkBounds && newPos2.x < (kWindowWidth-walkBounds) &&
          newPos2.y >= walkBounds && newPos2.y < (kWindowHeight-walkBounds)) {
          newPositions.push_back(newPos2);
          }

    }
  }
  //Converts coordinates into tile position
  for (auto newPosition : newPositions) {
    returnPositions.push_back((newPosition.x/kTileSize)+((newPosition.y/kTileSize)*40));
    usedTiles.push_back(newPosition);
  }
  return returnPositions;
}

std::vector<int> MapGeneration::HoleFilling() {
    std::vector<sf::Vector2i> newPositions;
    std::vector<int> returnPositions;

    // Create a set of positions to check
    std::vector<sf::Vector2i> tilesToCheck;

    // Find all positions adjacent to grass tiles
    for (const auto& grassTile : usedTiles) {
        for (const auto& direction : Directions::fourWayDirections) {
            sf::Vector2i adjacentTile = grassTile + direction;

            // Check bounds
            if (adjacentTile.x >= walkBounds &&
                adjacentTile.x < (kWindowWidth - walkBounds) &&
                adjacentTile.y >= walkBounds &&
                adjacentTile.y < (kWindowHeight - walkBounds)) {

                // Only add if it's not already a grass tile
                if (std::find(usedTiles.begin(), usedTiles.end(), adjacentTile) == usedTiles.end() &&
                    std::find(tilesToCheck.begin(), tilesToCheck.end(), adjacentTile) == tilesToCheck.end()) {
                    tilesToCheck.push_back(adjacentTile);
                }
            }
        }
    }

    // Check each potential position
    for (const auto& tileToCheck : tilesToCheck) {
        int grassNeighbors = 0;

        // Count grass neighbors
        for (const auto& direction : Directions::fourWayDirections) {
            sf::Vector2i neighborTile = tileToCheck + direction;
            if (std::find(usedTiles.begin(), usedTiles.end(), neighborTile) != usedTiles.end()) {
                grassNeighbors++;
            }
        }

        // If enough neighbors are grass, add this tile
        if (grassNeighbors >= 3) {
            newPositions.push_back(tileToCheck);
        }
    }

    // Convert to tile positions and update usedTiles
    for (const auto& newPosition : newPositions) {
        int tilePos = (newPosition.x / kTileSize) + ((newPosition.y / kTileSize) * 40);
        returnPositions.push_back(tilePos);
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

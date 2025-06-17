#include "graphics/map_generation.h"
#include "graphics/tilemap.h"
#include "graphics/directions.h"

#include <unordered_set>
#include <random>
#include <vector>

std::array<int, 150> MapGeneration::Drunkard() {
    std::array<int, 150> grassPositions;
    grassPositions.fill(-1);  // Initialize all elements to -1

    int currentIter = 0;
    int tilesConvertedToGrass = 0;

    // Move random generator initialization outside the loop
    std::random_device rd;
    std::mt19937 gen(rd());

    sf::Vector2i newGrassSpot{320, 240};

    // Add first position
    grassPositions[0] = (320/kTileSize) + ((240/kTileSize)*40);
    tilesConvertedToGrass = 1;
    usedTiles.push_back(newGrassSpot);

    try {
        while (currentIter < walkIterMax && tilesConvertedToGrass < 150) {
            std::uniform_int_distribution<> dirDist(0, Directions::fourWayDirections.size() - 1);
            auto dirIndex = dirDist(gen);

            // Add bounds check for direction index
            if (dirIndex < 0 || dirIndex >= Directions::fourWayDirections.size()) {
                std::cout << "Invalid direction index: " << dirIndex << std::endl;
                continue;
            }

            sf::Vector2i nextDirection = Directions::fourWayDirections[dirIndex];
            std::uniform_int_distribution<> walkDist(walkDistanceMin, walkDistanceMax - 1);
            int distanceToWalk = walkDist(gen);

            for (int walk = 0; walk < distanceToWalk && tilesConvertedToGrass < 150; walk++) {
                newGrassSpot += nextDirection;

                if (newGrassSpot.x > (kWindowWidth - walkBounds) ||
                    newGrassSpot.x < walkBounds ||
                    newGrassSpot.y > (kWindowHeight - walkBounds) ||
                    newGrassSpot.y < walkBounds) {
                    newGrassSpot = {320, 240};
                    continue;
                }

                // Calculate tile index
                int tileIndex = (newGrassSpot.x/kTileSize) + ((newGrassSpot.y/kTileSize)*40);

                // Validate tile index
                if (tileIndex < 0 || tileIndex >= 1600) {  // 40x40 grid = 1600 max tiles
                    std::cout << "Invalid tile index calculated: " << tileIndex << std::endl;
                    continue;
                }

                if (tilesConvertedToGrass < 150) {
                    grassPositions[tilesConvertedToGrass++] = tileIndex;
                    usedTiles.push_back(newGrassSpot);
                }
            }

            currentIter++;
        }
    }
    catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
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
  std::unordered_set<int> addedPositions;  // To prevent duplicates

  for (const auto& usedTile : usedTiles) {
    for (const auto& direction : Directions::eightWayDirections) {
      sf::Vector2i neighborTile = usedTile + direction;

      // Check bounds
      if (neighborTile.x >= walkBounds &&
          neighborTile.x < (kWindowWidth - walkBounds) &&
          neighborTile.y >= walkBounds &&
          neighborTile.y < (kWindowHeight - walkBounds)) {

        // Check if this neighbor is not a grass tile
        if (std::find(usedTiles.begin(), usedTiles.end(), neighborTile) == usedTiles.end()) {
          // Calculate tile index
          int tileIndex = (usedTile.x/kTileSize) + ((usedTile.y/kTileSize)*40);

          // Validate tile index
          if (tileIndex >= 0 && tileIndex < 1600 && // 40x40 grid = 1600 max tiles
              addedPositions.find(tileIndex) == addedPositions.end()) {

            returnPositions.push_back(tileIndex);
            addedPositions.insert(tileIndex);
              }
        }
          }
    }
  }
  return returnPositions;
}

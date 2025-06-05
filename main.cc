#include "D:/Module 4/NewCityBuilder/game/include/game.h"

int main() {
  game::Loop();
}
/*
  //Setup randomnness
  srand(time(0));

  //PCG Variables
  int walkIterMax=30;
  int walkDistanceMin=2;
  int walkDistanceMax=4;
  int walkBounds=kTileSize*3;

  //Set the grid tile size
  constexpr int numberOfWidthTiles = static_cast<int>(kWindowWidth)/kTileSize;
  constexpr int numberOfHeightTiles = static_cast<int>(kWindowHeight)/kTileSize;

  sf::Vector2f startPosition=sf::Vector2f((numberOfWidthTiles/2)*kTileSize, (numberOfHeightTiles/2)*kTileSize);

  //Create the positions of the tilemap
  for (int x = 0; x < numberOfWidthTiles; x++) {
    for (int y = 0; y < numberOfHeightTiles; y++) {
      tilePositions.emplace_back(x*kTileSize, y*kTileSize);
    }
  }

  //Drunkard generation variables
  int walkAmounts=0;
  int walkDistance;
  sf::Vector2f newGrassSpot;

  grassPositions.emplace_back(startPosition);

//Drunkard generation loop
  while (walkAmounts<walkIterMax) {
    sf::Vector2f nextDirection = fourWayDirections[std::rand() % fourWayDirections.size()];
    walkDistance = std::rand() % (walkDistanceMax - walkDistanceMin) + walkDistanceMin;

    for (int walk = 0; walk < walkDistance; walk++) {
      newGrassSpot=grassPositions.back()+sf::Vector2f(nextDirection);

      if (newGrassSpot.x>(kWindowWidth-walkBounds) || newGrassSpot.x<walkBounds) {
        break;
      }
      if (newGrassSpot.y>(kWindowHeight-walkBounds) || newGrassSpot.y<walkBounds) {
        break;
      }
      grassPositions.emplace_back(newGrassSpot);
    }
    walkAmounts++;
  }

  //Create the ocean
  for(auto tilePosition : tilePositions){
    water_sprite_.setPosition(tilePosition);
    tileMap.emplace_back(water_sprite_);
  }

  //Increase grass size
  std::vector<sf::Vector2f> newGrassPositions;
  //1 - Make the grass slightly thicker by the ones surrounding him
  for (auto grassPosition : grassPositions) {
    for (auto direction : fourWayDirections) {
      newGrassPositions.emplace_back(grassPosition+direction);
    }
  }
  //2 - Add these new tiles to him
  for (auto newGrassPosition : newGrassPositions) {
    grassPositions.emplace_back(newGrassPosition);
  }

  //3 - Add the grass positions on the tilemap
  for (auto grassPosition : grassPositions) {
    grass_sprite_.setPosition(grassPosition);
    tileMap.emplace_back(grass_sprite_);
  }

  //Fill empty holes
  /*
  int fillUp=0;

  for (auto tilePosition : tilePositions) {
    //Check if the current tile is a grass tile
    if (std::find(grassPositions.begin(), grassPositions.end(), tilePosition) != grassPositions.end()) {
      //Nothing
    }
    //If not a grass tile, check the ones around him
    else {
      for (auto direction : fourWayDirections) {
        sf::Vector2f neighboorTile=tilePosition+direction;

        if (std::find(grassPositions.begin(), grassPositions.end(), neighboorTile) != grassPositions.end()) {
          fillUp++;
        }
      }
      //If enough tiles around him are grass, he becomes grass
      if (fillUp>=3) {
        flower_sprite_.setPosition(tilePosition);
        tileMap.emplace_back(flower_sprite_);
      }
      fillUp=0;
    }
  }

//Add sand tiles based if a grass tile is surrounded by empty tile
  for (auto grassPosition : grassPositions) {
    for (auto direction : fourWayDirections) {
      if (std::find(grassPositions.begin(), grassPositions.end(), grassPosition+direction) == grassPositions.end()) {
        sand_sprite_.setPosition(grassPosition);
        tileMap.emplace_back(sand_sprite_);
      }
    }
  }
}*/
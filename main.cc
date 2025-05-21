#include <iostream>
#include <random>

#include "SFML/Graphics.hpp"
#include "game.h"
#include "map_generation.h"

int main() {

  game::Loop();
/*
  //Setup randomnness
  srand(time(0));

  // Window variables
  constexpr int kWindowWidth = 640;
  constexpr int kWindowHeight=480;
  constexpr int kTileSize=16;

  //PCG Variables
  int walkIterMax=30;
  int walkDistanceMin=2;
  int walkDistanceMax=4;
  int walkBounds=kTileSize*3;

  //Set the grid tile size
  constexpr int numberOfWidthTiles = static_cast<int>(kWindowWidth)/kTileSize;
  constexpr int numberOfHeightTiles = static_cast<int>(kWindowHeight)/kTileSize;

  //Tilemap Variables
  std::vector<sf::Vector2f> tilePositions;
  std::vector<sf::Vector2f> grassPositions;
  std::vector<sf::Sprite> tileMap;
  sf::Vector2f startPosition=sf::Vector2f((numberOfWidthTiles/2)*kTileSize, (numberOfHeightTiles/2)*kTileSize);

  //Set up 4 way directions
  std::array<sf::Vector2f, 4> fourWayDirections;

  fourWayDirections[0] = sf::Vector2f(kTileSize, 0);
  fourWayDirections[1] = sf::Vector2f(-kTileSize, 0);
  fourWayDirections[2] = sf::Vector2f(0, kTileSize);
  fourWayDirections[3] = sf::Vector2f(0, -kTileSize);

  //Set up 8 way directions
  std::array<sf::Vector2f, 8> eightWayDirections;

  eightWayDirections[0] = sf::Vector2f(kTileSize, 0);
  eightWayDirections[1] = sf::Vector2f(-kTileSize, 0);
  eightWayDirections[2] = sf::Vector2f(0, kTileSize);
  eightWayDirections[3] = sf::Vector2f(0, -kTileSize);
  eightWayDirections[4] = sf::Vector2f(kTileSize, kTileSize);
  eightWayDirections[5] = sf::Vector2f(-kTileSize, -kTileSize);
  eightWayDirections[6] = sf::Vector2f(kTileSize, -kTileSize);
  eightWayDirections[7] = sf::Vector2f(-kTileSize, kTileSize);

  //Texture and sprite setup
  sf::Texture grass_texture_("../_assets/sprites/grass.png");
  sf::Sprite grass_sprite_(grass_texture_);

  sf::Texture water_texture_("../_assets/sprites/water.png");
  sf::Sprite water_sprite_(water_texture_);

  sf::Texture flower_texture_("../_assets/sprites/flowers.png");
  sf::Sprite flower_sprite_(flower_texture_);

  sf::Texture sand_texture_("../_assets/sprites/sand.png");
  sf::Sprite sand_sprite_(sand_texture_);

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

  //Display screen
  sf::RenderWindow window(sf::VideoMode({kWindowWidth, kWindowHeight}), "City Builder");

  while (window.isOpen()){
    while (std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }
    window.clear();

    //Draws the tilemap
    for (const auto& tile : tileMap) {
      window.draw(tile);
    }

    window.display();
  }

    return 0;
  */
}
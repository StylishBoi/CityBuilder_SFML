#include "../../include/graphics/directions.h"

#include <iostream>
#include <random>

#include "../../include/graphics/tilemap.h"
#include "SFML/Graphics.hpp"

void Directions::Setup(){

  //Set up 4 way directions
  fourWayDirections[0] = sf::Vector2i(kTileSize, 0);
  fourWayDirections[1] = sf::Vector2i(-kTileSize, 0);
  fourWayDirections[2] = sf::Vector2i(0, kTileSize);
  fourWayDirections[3] = sf::Vector2i(0, -kTileSize);

  //Set up 8 way directions
  eightWayDirections[0] = sf::Vector2i(kTileSize, 0);
  eightWayDirections[1] = sf::Vector2i(-kTileSize, 0);
  eightWayDirections[2] = sf::Vector2i(0, kTileSize);
  eightWayDirections[3] = sf::Vector2i(0, -kTileSize);
  eightWayDirections[4] = sf::Vector2i(kTileSize, kTileSize);
  eightWayDirections[5] = sf::Vector2i(-kTileSize, -kTileSize);
  eightWayDirections[6] = sf::Vector2i(kTileSize, -kTileSize);
  eightWayDirections[7] = sf::Vector2i(-kTileSize, kTileSize);
}

#ifndef DIRECTIONS_H
#define DIRECTIONS_H

#include "SFML/Graphics.hpp"

class Directions{

private:
  constexpr int kTileSize=16;

public:
  std::array<sf::Vector2f, 4> fourWayDirections;

  std::array<sf::Vector2f, 8> eightWayDirections;

  void Setup();
};

#endif //DIRECTIONS_H

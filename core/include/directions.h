#ifndef DIRECTIONS_H
#define DIRECTIONS_H

#include "SFML/Graphics.hpp"

class Directions{

public:
  static std::array<sf::Vector2f, 4> fourWayDirections;

  static std::array<sf::Vector2f, 8> eightWayDirections;

  void Setup();
};

#endif //DIRECTIONS_H

#ifndef DIRECTIONS_H
#define DIRECTIONS_H

#include <SFML/Graphics.hpp>
#include <iostream>

class Directions{

public:
  static inline std::array<sf::Vector2i, 4> fourWayDirections;

  static inline std::array<sf::Vector2i, 8> eightWayDirections;

  static void Setup();
};

#endif //DIRECTIONS_H

#ifndef CITYBUILDER_HOVER_H
#define CITYBUILDER_HOVER_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "clickable.h"

class Hover{

 private:
  sf::Texture texture_;
  sf::Vector2f hover_position_;

 public:
  Hover();
  void Update(sf::Vector2f mousePos);
  void Draw(sf::RenderWindow& window) const;
};


#endif  // CITYBUILDER_HOVER_H

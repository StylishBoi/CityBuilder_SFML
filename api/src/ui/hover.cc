#include "ui/hover.h"

Hover::Hover() {
  if(!texture_.loadFromFile("_assets/sprites/hover_sprite.png")){
  }
  }

void Hover::Update(sf::Vector2f mousePos) {
  hover_position_=mousePos;
}

void Hover::Draw(sf::RenderWindow& window) const {
  sf::Sprite hover_sprite_(texture_);
  hover_sprite_.setPosition(hover_position_);

  window.draw(hover_sprite_);
}
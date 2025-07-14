#include "ui/button.h"

#include <SFML/Graphics/Texture.hpp>
#include <iostream>

namespace api::ui {

Button::Button(const sf::Vector2f pos, std::string_view label,
               const sf::Texture& texture,
               const sf::Texture& hover_texture,
               const sf::Font& font)
    : Clickable(), sprite_(texture), hover_sprite_(hover_texture), label_(font) {
  sf::Vector2i int_size = {static_cast<int>(sprite_.getTexture().getSize().x),
                           static_cast<int>(sprite_.getTexture().getSize().y)};
  sf::Vector2i int_pos = {static_cast<int>(pos.x), static_cast<int>(pos.y)};

  std::cout << "Texture size : " << int_size.x << ":" << int_size.y << "\n";

  sprite_.setPosition(pos);
  // sprite_.setOrigin(sprite_.getLocalBounds().getCenter());
  hover_sprite_.setPosition(pos);
  // hover_sprite_.setOrigin(hover_sprite_.getLocalBounds().getCenter());

  label_.setCharacterSize(20);
  label_.setString(std::string(label));
  sf::FloatRect textRect = label_.getLocalBounds();
  label_.setOrigin(label_.getLocalBounds().getCenter());
  label_.setPosition({pos.x + sprite_.getTexture().getSize().x / 2.f,
                      pos.y + sprite_.getTexture().getSize().y / 2.f});

  Button::SetZone(sf::IntRect(int_pos, int_size));

  OnHoverEnter = [this]() {
    sprite_.setColor(sf::Color(0, 0, 0, 0));
    hover_sprite_.setColor(sf::Color(255, 255, 255, 255));
    label_.setFillColor(sf::Color::Black);
  };
  OnHoverExit = [this]() {
    sprite_.setColor(sf::Color(255, 255, 255, 255));
    hover_sprite_.setColor(sf::Color(0, 0, 0, 0));
    label_.setFillColor(sf::Color::White);
  };

  sprite_.setColor(sf::Color(255, 255, 255, 255));
  hover_sprite_.setColor(sf::Color(0, 0, 0, 0));
}

void Button::Draw(sf::RenderWindow& window) const {
  window.draw(sprite_);
  window.draw(hover_sprite_);
  window.draw(label_);
}
}  // namespace api::ui
#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "clickable.h"

namespace api::ui {
  class Button : public Clickable{
    sf::Sprite sprite_;
    sf::Sprite hover_sprite_;
    sf::Text label_;

  public:
    Button(sf::Vector2f pos, std::string_view label, const sf::Texture& texture, const sf::Texture& hover_texture, const sf::Font& font);
    void Draw(sf::RenderWindow& window) const;
  };

}

#endif //BUTTON_H

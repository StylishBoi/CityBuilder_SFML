#ifndef ECONOMY_DISPLAY_H
#define ECONOMY_DISPLAY_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

#include "assets/asset_manager.h"
#include "gameplay/economy_manager.h"

class EconomyDisplay {
 private:
  static constexpr float kTextSize = 16.0f;

  sf::Sprite wood_icon_;
  sf::Text wood_text_;

 public:
  void Draw(sf::RenderWindow& window) const;
};
#endif  // ECONOMY_DISPLAY_H
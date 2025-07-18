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

  enum class economyIcon {
    kNone,
    kWood,
    kStone,
    kFood,
    kBackground,
    kLength
  };

  std::string_view files[static_cast<size_t>(economyIcon::kLength)]{
      "empty.png",
      "wood_icon.png",
      "rock_icon.png",
      "food_icon.png",
      "HighQualitySquareBox.png"};
  core::experimental::AssetManager<sf::Texture, economyIcon, "_assets/sprites"> textures;

  sf::Font economy_font;

  int wood_total_;
  int stone_total_;
  int food_total_;

 public:
  void Setup();
  void Draw(sf::RenderWindow& window);
  void Update(int wood, int stone, int food);
};
#endif  // ECONOMY_DISPLAY_H
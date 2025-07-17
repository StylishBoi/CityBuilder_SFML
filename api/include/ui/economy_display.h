#ifndef ECONOMY_DISPLAY_H
#define ECONOMY_DISPLAY_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

#include "assets/asset_manager.h"
#include "gameplay/economy_manager.h"

namespace api::ui {
class EconomyDisplay : public sf::Drawable {
 private:

  enum class EconomySprite { kEmpty, kWood, kStone, kFood, kLength };

  const std::array<std::string_view, static_cast<size_t>(EconomySprite::kLength)> files_ =
      {"empty.png", "wood.png", "stone.png", "food.png"};

  sf::Font font_;
  core::experimental::AssetManager<sf::Texture, EconomySprite, "_assets/sprites"> textures_;

  sf::Text wood_economy_text_;
  sf::Text stone_economy_text_;
  sf::Text food_economy_text_;

  sf::Sprite wood_shape_;
  sf::Sprite stone_shape_;
  sf::Sprite food_shape_;
  sf::Sprite background_shape_;

  EconomyManager& economy_manager_;

  size_t wood_economy_amount_;
  size_t stone_economy_amount_;
  size_t food_economy_amount_;

 public:
  void Setup();
  void SetupUiEconomyText();
  void SetupUiEconomyImage();

  void Draw(sf::RenderWindow& window) const;
};

}
#endif  // ECONOMY_DISPLAY_H
#include "ui/economy_display.h"

#ifdef TRACY_ENABLE
#include <tracy/Tracy.hpp>
#endif

#include "gameplay/economy_manager.h"
#include "assets/asset_manager.h"

//change text
namespace api::ui {
void EconomyDisplay::SetupUiEconomyText() {
#ifdef TRACY_ENABLE
  ZoneScoped;
#endif
  const auto text_pos = sf::Vector2f(0.0f, 0.0f);

  // Wood text setup
  wood_economy_text_.setFont(font_);
  wood_economy_text_.setCharacterSize(16);
  wood_economy_text_.setFillColor(sf::Color::Black);
  wood_economy_text_.setPosition(sf::Vector2f(
      text_pos.x + wood_shape_.getGlobalBounds().size.x, text_pos.y));

  // Stone text setup
  stone_economy_text_.setFont(font_);
  stone_economy_text_.setCharacterSize(16);
  stone_economy_text_.setFillColor(sf::Color::Black);
  stone_economy_text_.setPosition(
      sf::Vector2f(text_pos.x + stone_shape_.getGlobalBounds().size.x,
                   text_pos.y + stone_shape_.getGlobalBounds().size.y));

  // Set text as economy
  wood_economy_amount_ = economy_manager_.GetWoodEconomy();
  wood_economy_text_.setString(std::to_string(wood_economy_amount_));
  stone_economy_amount_ = economy_manager_.GetStoneEconomy();
  stone_economy_text_.setString(std::to_string(stone_economy_amount_));
  food_economy_amount_ = economy_manager_.GetFoodEconomy();
  food_economy_text_.setString(std::to_string(food_economy_amount_));
}

void EconomyDisplay::SetupUiEconomyImage() {
  const auto wood_shape_position = sf::Vector2f(0.0f, 0.0f);
  const auto color = sf::Color::White;

  // Wood image setup
  wood_shape_.setPosition(wood_shape_position);
  wood_shape_.setColor(color);
  wood_shape_.setTexture(textures_.GetAsset(EconomySprite::kWood));

  // Stone image setup
  const auto stone_shape_position = sf::Vector2f(
      wood_shape_position.x,
      wood_shape_position.y + wood_shape_.getGlobalBounds().size.y);
  stone_shape_.setPosition(stone_shape_position);
  stone_shape_.setColor(color);
  stone_shape_.setTexture(textures_.GetAsset(EconomySprite::kStone));

  // Background image setup
  background_shape_.setPosition(wood_shape_position);
  background_shape_.setColor(color);
  background_shape_.setTexture(textures_.GetAsset(EconomySprite::kEmpty));
}

// draw
void EconomyDisplay::Draw(sf::RenderWindow& window) const {
  window.draw(background_shape_);
  window.draw(wood_economy_text_);
  window.draw(stone_economy_text_);
  window.draw(wood_shape_);
  window.draw(stone_shape_);
}

// constructor
void EconomyDisplay::Setup(){
  SetupUiEconomyImage();
  SetupUiEconomyText();
}
}
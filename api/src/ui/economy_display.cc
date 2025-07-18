#include "ui/economy_display.h"

void EconomyDisplay::Setup() {
  textures.LoadAssets(files);

  if(economy_font.openFromFile("_assets/fonts/Bebas-Regular.ttf")){
  }
}

void EconomyDisplay::Update(int wood, int stone, int food) {
  wood_total_ = wood;
  stone_total_ = stone;
  food_total_ = food;
}

void EconomyDisplay::Draw(sf::RenderWindow& window) {
  sf::Sprite economy_background(textures.GetAsset(economyIcon::kBackground));
  economy_background.setPosition(sf::Vector2f(0, 0));
  economy_background.setScale(sf::Vector2f(0.175, 0.19));
  window.draw(economy_background);

  sf::Sprite wood_icon(textures.GetAsset(economyIcon::kWood));
  wood_icon.setPosition(sf::Vector2f (25, 25));
  window.draw(wood_icon);

  // Draw stone icon and count
  sf::Sprite stone_icon(textures.GetAsset(economyIcon::kStone));
  stone_icon.setPosition(sf::Vector2f (25, 50));
  window.draw(stone_icon);

  // Draw food icon and count
  sf::Sprite food_icon(textures.GetAsset(economyIcon::kFood));
  food_icon.setPosition(sf::Vector2f (25, 75));
  window.draw(food_icon);

  sf::Text wood_text(economy_font, std::to_string(wood_total_)+" W", kTextSize);
  wood_text.setFillColor(sf::Color::Black);
  wood_text.setPosition(sf::Vector2f(50, 25));
  window.draw(wood_text);

  sf::Text stone_text(economy_font, std::to_string(stone_total_)+" S", kTextSize);
  stone_text.setFillColor(sf::Color::Black);
  stone_text.setPosition(sf::Vector2f(50, 50));
  window.draw(stone_text);

  sf::Text food_text(economy_font, std::to_string(food_total_)+" F", kTextSize);
  food_text.setFillColor(sf::Color::Black);
  food_text.setPosition(sf::Vector2f(50, 75));
  window.draw(food_text);

  sf::Text price(economy_font, "20W | 10S", kTextSize);
  price.setFillColor(sf::Color::Black);

  price.setPosition(sf::Vector2f(70, 615));
  window.draw(price);

  price.setString("10W | 20S");
  price.setPosition(sf::Vector2f(170, 615));
  window.draw(price);

    price.setString("20W | 20S");
  price.setPosition(sf::Vector2f(270, 615));
  window.draw(price);

}

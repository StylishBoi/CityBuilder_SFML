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

  sf::Sprite economy_icon(textures.GetAsset(economyIcon::kWood));
  economy_icon.setPosition(sf::Vector2f (25, 25));
  window.draw(economy_icon);

  // Draw stone icon and count
  economy_icon.setTexture(textures.GetAsset(economyIcon::kStone));
  economy_icon.setPosition(sf::Vector2f (25, 50));
  window.draw(economy_icon);

  // Draw food icon and count
  economy_icon.setTexture(textures.GetAsset(economyIcon::kFood));
  economy_icon.setPosition(sf::Vector2f (25, 75));
  window.draw(economy_icon);

  sf::Text economy_text(economy_font, std::to_string(wood_total_)+" W", kTextSize);
  economy_text.setFillColor(sf::Color::Black);
  economy_text.setPosition(sf::Vector2f(50, 25));
  window.draw(economy_text);

  economy_text.setString(std::to_string(stone_total_)+" S");
  economy_text.setPosition(sf::Vector2f(50, 50));
  window.draw(economy_text);

  economy_text.setString(std::to_string(food_total_)+" F");
  economy_text.setPosition(sf::Vector2f(50, 75));
  window.draw(economy_text);

  sf::Text price_text(economy_font, "20W | 10S", kTextSize);
  price_text.setFillColor(sf::Color::Black);

  price_text.setPosition(sf::Vector2f(70, 615));
  window.draw(price_text);

  price_text.setString("10W | 20S");
  price_text.setPosition(sf::Vector2f(170, 615));
  window.draw(price_text);

  price_text.setString("20W | 20S");
  price_text.setPosition(sf::Vector2f(270, 615));
  window.draw(price_text);

}

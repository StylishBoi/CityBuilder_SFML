#include "graphics/resources.h"

#include <iostream>

void Resources::Setup(const TileMap* tileMap) {
  textures.LoadAssets(files);

  tileMap_ = tileMap;
  position_.emplace_back(Resource::kWood, sf::Vector2f(160.f, 160.f));
  position_.emplace_back(Resource::kWood, sf::Vector2f(176.f, 160.f));
  position_.emplace_back(Resource::kWood, sf::Vector2f(160.f, 176.f));
  position_.emplace_back(Resource::kWood, sf::Vector2f(176.f, 176.f));
  std::cout<<"RESOURCES SETUP"<<std::endl;
}

void Resources::Draw(sf::RenderWindow &window){

  sf::Sprite sprite(textures.GetAsset(Resource::kWood));

  for (auto element : position_) {
    sprite.setPosition(element.second);
    sprite.setTexture(textures.GetAsset(element.first));
    window.draw(sprite);
  }
}
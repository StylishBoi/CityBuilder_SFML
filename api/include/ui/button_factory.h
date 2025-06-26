#ifndef BUTTON_FACTORY_H
#define BUTTON_FACTORY_H

#include <SFML/Graphics/Font.hpp>
#include <array>
#include <iostream>
#include <string_view>

#include "assets/asset_manager.h"
#include "button.h"

namespace api::ui {
class ButtonFactory {
  enum class Sprite { kEmpty, kBgBtn, kHoverBtn, kLength };

  std::array<std::string_view, static_cast<size_t>(Sprite::kLength)> files_ =
          {"empty.png", "button.png", "button_hover.png"};

  sf::Font font;
  core::experimental::AssetManager<sf::Texture, Sprite, "_assets/sprites"> textures_;

public:
  ButtonFactory(){
    textures_.LoadAssets(files_);
    if (!font.openFromFile("_assets/fonts/Bebas-Regular.TTF")) {
      std::cout << "Failed to load font" << std::endl;
    }
  }

  std::unique_ptr<Button> CreateButton(sf::Vector2f pos, std::string_view label){
    return std::move(
        std::make_unique<api::ui::Button>(
            pos, label,
            textures_.GetAsset(Sprite::kBgBtn), textures_.GetAsset(Sprite::kHoverBtn),
            font)
    );
  }
};
}

#endif //BUTTON_FACTORY_H

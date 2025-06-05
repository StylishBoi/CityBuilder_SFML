#include "ai/npc.h"

#include <iostream>

Status Npc::Move() {
  std::cout << "I'm moving 2" << std::endl;
  return Status::kRunning;
}

void Npc::Setup() {
  textures.LoadAssets(files);

  auto selector =std::make_unique<Selector>();

  selector->AddChild(std::make_unique<Action>([this]() {
    if (hungry_) {
      std::cout << "I'm hungry!" << std::endl;
      return Status::kSuccess;
    }
    return Status::kFailure;
  }));

  selector->AddChild(std::make_unique<Action>([this]() {
    if (resourceAvailable_) {
      std::cout << "Available!" << std::endl;
      return Status::kSuccess;
    }
    return Status::kFailure;
  }));

  selector->AddChild(std::make_unique<Action>([this]() {
    std::cout << "I'm sleeping!" << std::endl;
    return Status::kSuccess;
  }));

  root_=std::make_unique<Action>([] {
    std::cout<<"I'm moving"<<std::endl;
    return Status::kSuccess;
  });

  root_=std::move(selector);
}

void Npc::Update() {
  root_->Tick();
}

void Npc::Draw(sf::RenderWindow &window) {
  sf::Sprite sprite(textures.GetAsset(Animation::kBlue));
  window.draw(sprite);
}

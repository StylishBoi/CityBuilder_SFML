#include "ai/npc.h"

#include <iostream>

#include "ai/bt_sequence.h"
#include "ai/bt_selector.h"
#include "ai/bt_action.h"

using namespace api::ai;

Status Npc::Move() {
  //If destination not reachable, return failure
  if (!target_reachable_) {
    std::cout << "Not reachable : " << target_reachable_ << std::endl;
    return Status::kFailure;
  }
  else{
    if (target_distance_>=0.15f) {
      std::cout << "I'm moving : "<< target_distance_ << std::endl;
      target_distance_-=kMovingSpeed;
      return Status::kRunning;
    }
    else {
      return Status::kSuccess;
    }
  }
}

Status Npc::Eat() {
    //No failure until we have food storage system
    hunger_-=kHungerRate;
    if (hunger_>0) {
      return Status::kRunning;
    }
    else {
    return Status::kSuccess;
    }
}

void Npc::SetupBehaviourTree() {

  auto feedSequence = std::make_unique<Sequence>();
  feedSequence->AddChild(std::make_unique<Action>([this]() {
    if (hunger_>=100) {
      std::cout << "I'm hungry!" << std::endl;
      return Status::kSuccess;
    }
    std::cout << "I'm not hungry!" << std::endl;
    return Status::kFailure;
  }));
  feedSequence->AddChild(std::make_unique<Action>(std::bind(&Npc::Move, this)));
  feedSequence->AddChild(std::make_unique<Action>(std::bind(&Npc::Move, this)));


  auto selector =std::make_unique<Selector>();

  selector->AddChild(std::move(feedSequence));
  selector->AddChild(std::make_unique<Action>([this]() {
    if (resourceAvailable_) {
      std::cout << "Resource available!" << std::endl;
      return Status::kSuccess;
    }
    return Status::kFailure;
  }));

  selector->AddChild(std::make_unique<Action>([this]() {
    hunger_+=kHungerRate*5;
    std::cout << "I'm sleeping!" << std::endl;
    return Status::kSuccess;
  }));

  root_=std::move(selector);
}

void Npc::Setup() {
  textures.LoadAssets(files);

  SetupBehaviourTree();

  motor_.SetPosition(sf::Vector2f(100.f, 100.f));
}


void Npc::Update(float dt) {
  std::cout<<"Hunger : "<<hunger_<<std::endl;
  motor_.Update(dt);
  root_->Tick();
}

void Npc::Draw(sf::RenderWindow &window) {
  sf::Sprite sprite(textures.GetAsset(Animation::kBlue));

  sprite.setPosition(motor_.GetPosition());

  window.draw(sprite);
}

#include "ai/npc.h"

#include <iostream>
#include <random>

#include "ai/bt_sequence.h"
#include "ai/bt_selector.h"
#include "ai/bt_action.h"
#include "motion/AStar.h"

using namespace api::ai;

Status Npc::Move(){
    // If the destination isn't reached, returns failure
    if (!target_reachable_) {
        std::cout << "Not reachable" << target_reachable_ << std::endl;
        return Status::kFailure;
    } else {
        std::cout << "I'm moving (distance = " << target_distance_ << ")" << std::endl;
        if (target_distance_ >= 0.15f) {
            // still arriving, return running
            target_distance_ -= kMovingSpeed;
            return Status::kRunning;
        } else {
            // If destination reached, return success
            return Status::kSuccess;
        }
    }
}

Status Npc::Eat(){
    // No failure, until we have food storage system
    hunger_ -= kHungerRate;
    if (hunger_ > 0) {
        return Status::kRunning;
    } else {
        return Status::kSuccess;
    }
}

void Npc::SetupBehaviourTree(){
    auto feedSequence = std::make_unique<Sequence>();
    feedSequence->AddChild(std::make_unique<Action>([this]() {
        if (hunger_ >= 100) {
            std::cout << "I'm hungry, wanna eat........" << std::endl;
            return Status::kSuccess;
        } else {
            std::cout << "I'm not hungry, thanks........" << std::endl;
            return Status::kFailure;
        }
    }));
    feedSequence->AddChild(std::make_unique<Action>(std::bind(&Npc::Move, this)));
    feedSequence->AddChild(std::make_unique<Action>(std::bind(&Npc::Eat, this)));

    auto selector = std::make_unique<Selector>();
    // Attach the sequence to the selector
    selector->AddChild(std::move(feedSequence));
    // Work sequence
    selector->AddChild(std::make_unique<Action>([this]() {
        hunger_ += kHungerRate * 5;
        if (resourceAvailable_) {
            std::cout << "Resource Available, working....." << std::endl;
            return Status::kSuccess;
        }
        return Status::kFailure;
    }));
    // Idle sequence
    selector->AddChild(std::make_unique<Action>([this]() {
        hunger_ += kHungerRate * 5;
        std::cout << "I'm sleeping" << std::endl;
        return Status::kSuccess;
    }));

    root_ = std::move(selector);

}

void Npc::Setup(const TileMap* tileMap, const Resources* resources){
  //Load assets for the drawing phase
    textures.LoadAssets(files);

    SetupBehaviourTree();

  //Sets up the motor
    motor_.SetPosition({320, 240});
    motor_.SetSpeed(kMovingSpeed);

  //Intakes the tilemap as a local poitner
    tileMap_ = tileMap;
    resources_ = resources;

  //Setup randomness
    static std::mt19937 gen{std::random_device{}()};
    static std::uniform_int_distribution<size_t> dist(0, tileMap_->GetWalkables().size() - 1);

  //Setup path
    sf::Vector2f end = tileMap_->GetWalkables().at(dist(gen));

    Path path = Astar::GetPath(64, motor_.GetPosition(), end, tileMap_->GetWalkables());
    SetPath(path);

}

void Npc::Update(float dt){

    // If the path is valid, the player will move
    if (path_.IsValid()){
        motor_.Update(dt);
        //If the path isn't done yet, the player will find the next point to go to
        if (!path_.IsDone() && motor_.RemainingDistance() <= 0.001f) {
            motor_.SetDestination(path_.GetNextPoint());
        }
    }
    else {
      if (resources_->resourcePositions_.empty()) {
        std::cout << "Resource Available, moving....." << std::endl;
          std::vector<sf::Vector2f> hallo;
        for (auto element : resources_->resourcePositions_) {
          hallo.push_back(element.second);
        }
        path_.Fill(hallo);
        motor_.SetDestination(resources_->resourcePositions_[0].second);
      }
    }
}

//Draws the npc on the tilemap
void Npc::Draw(sf::RenderWindow &window){
    sf::Sprite sprite(textures.GetAsset(Animation::kBlue));
    sprite.setPosition(motor_.GetPosition());
    window.draw(sprite);
}

//Sets a new path for the npc
void Npc::SetPath(const Path& path){
    path_ = path;
    motor_.SetDestination(path_.StartPoint());
}
#include "ai/npc_behaviour_tree.h"

#include <functional>
#include <iostream>
#include <random>
#include <utility>

#include "ai/bt_action.h"
#include "ai/bt_selector.h"
#include "ai/bt_sequence.h"
#include "motion/AStar.h"
#include "motion/path.h"

using namespace core::ai::behaviour_tree;
using namespace api::motion;

namespace api::ai {

  void NpcBehaviourTree::SetDestination(const sf::Vector2f& destination) const {

    // Try to find a path to the destination using A* pathfinding
    Path path = Astar::GetPath(16, npc_motor_->GetPosition(), destination,
                                                       this->tilemap_->GetWalkables());
    if (path.IsValid()) {
      // Fill the NPC's path with the found waypoints
      this->path_->Fill(path.Points());
      // Set the first waypoint as the immediate destination
      this->npc_motor_->SetDestination(path.StartPoint());
    }
    std::cout<<"That shit did not work";
  }

  Status NpcBehaviourTree::CheckHunger() const {
    std::cout << "Current action : Checking hunger"<<"\n";
    std::cout << "Am I hungry ? " << std::to_string(hunger_);

    if (hunger_ >= 100) {
      std::cout << " : Yes, I need to find food\n";

      if (!tilemap_) {
        std::cout << "No tilemap\n";
        return Status::kFailure;
      }
      if (!path_) {
        std::cout << "No path\n";
        return Status::kFailure;
      }
      if (!npc_motor_) {
        std::cout << "No motor\n";
        return Status::kFailure;
      }

      return Status::kSuccess;

    } else {
      std::cout << " : No, I can wait\n";
      return Status::kFailure;
    }
      SetDestination(home_position_);
  }



  Status NpcBehaviourTree::Move() const {
    std::cout << "Current action : Moving"<<"\n";
    // if destination not reachable, return failure
    if (!path_->IsValid()) {
      std::cout << "Not reachable " << path_->IsValid() << "\n";
      std::cout << path_->StartPoint().x << ":" << path_->StartPoint().y << "\n";
      return Status::kFailure;
    } else {
      std::cout << "I'm moving" << "\n";
      if (!path_->IsDone()) {
        // still arriving, return running
        return Status::kRunning;
      } else {
        // if destination reached, return success
        return Status::kSuccess;
      }
    }
  }

  Status NpcBehaviourTree::Eat() {
    // No failure, until we have food storage system
    std::cout << "Current action : Eating"<<"\n";
    hunger_ -= kHungerRate * tick_dt;
    if (hunger_ > 0) {
      return Status::kRunning;
    } else {
      return Status::kSuccess;
    }
  }

  Status NpcBehaviourTree::PickResource() {
    std::cout << "Current action : Picking resource"<<"\n";

      if (resources_.empty()) {
        std::cout << "No resources available\n";
        return Status::kFailure;
      }

      std::mt19937 gen{std::random_device{}()};
      std::uniform_int_distribution<size_t> dist(0, resources_.size() - 1);

      if (resources_[dist(gen)].GetQty() > 0) {
        current_resource_ = resources_[dist(gen)];
        SetDestination(TileMap::ScreenPosition(current_resource_.GetTileIndex()));

        if (path_->IsValid())
          return Status::kSuccess;

      }

      return Status::kFailure;


    }

  Status NpcBehaviourTree::GetResource() {
    std::cout << "Current action : Getting resource"<<"\n";
      if (current_resource_.GetQty() <= 0) {
        return Status::kSuccess;
      }

      current_resource_.Exploit(kExploitRate * tick_dt);
      hunger_ += kHungerRate * tick_dt;
      return Status::kRunning;
    }

  Status NpcBehaviourTree::Idle() {
    hunger_ += kHungerRate * tick_dt;
    std::cout << "I'm sleeping" << "\n";
    return Status::kSuccess;
  }

  void NpcBehaviourTree::SetupBehaviourTree(Motor* npc_motor, Path* path,
                                            TileMap* tilemap, sf::Vector2f home_position,
                                            std::vector<Resource> resources) {
    std::cout << "Setup Behaviour Tree\n";

    hunger_ = 0;

    npc_motor_ = npc_motor;
    path_ = path;
    tilemap_ = tilemap;
    home_position_ = home_position;
    resources_ = std::move(resources);

    auto feedSequence = std::make_unique<Sequence>();
    feedSequence->AddChild(std::make_unique<Action>([this]() { return CheckHunger(); }));
    feedSequence->AddChild(std::make_unique<Action>([this]() { return Move(); }));
    feedSequence->AddChild(std::make_unique<Action>([this]() { return Eat(); }));

    auto workSequence = std::make_unique<Sequence>();
    workSequence->AddChild(std::make_unique<Action>([this]() { return PickResource(); }));
    workSequence->AddChild(std::make_unique<Action>([this]() { return Move(); }));
    workSequence->AddChild(std::make_unique<Action>([this]() { return GetResource(); }));

    auto selector = std::make_unique<Selector>();
    // Attach the sequence to the selector
    selector->AddChild(std::move(feedSequence));
    selector->AddChild(std::move(workSequence));
    selector->AddChild(std::make_unique<Action>([this]() { return Idle(); }));

    bt_root_ = std::move(selector);
  }

  void NpcBehaviourTree::Update(float dt) {
    tick_dt = dt;
    bt_root_->Tick();
  }
}  // namespace api::ai
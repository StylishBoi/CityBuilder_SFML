#ifndef NPC_BEHAVIOUR_TREE_H
#define NPC_BEHAVIOUR_TREE_H

#include <memory>

#include "../resources/resources_manager.h"
#include "ai/bt_node.h"
#include "graphics/tilemap.h"
#include "motion/motor.h"
#include "motion/path.h"

namespace api::ai {
  class NpcBehaviourTree {
    // Behaviour tree
    std::unique_ptr<core::ai::behaviour_tree::Node> bt_root_;

    TileMap *tilemap_ = nullptr;

    motion::Motor *npc_motor_ = nullptr;
    motion::Path *path_ = nullptr;


    void SetDestination(const sf::Vector2f& destination) const;
    // Actions
    [[nodiscard]] core::ai::behaviour_tree::Status CheckHunger() const;
    [[nodiscard]] core::ai::behaviour_tree::Status Move() const;
    [[nodiscard]] core::ai::behaviour_tree::Status Eat();
    [[nodiscard]] core::ai::behaviour_tree::Status PickResource();
    [[nodiscard]] core::ai::behaviour_tree::Status GetResource();
    [[nodiscard]] core::ai::behaviour_tree::Status Idle();

    // Behaviour Constants
    static constexpr float kHungerRate = 2.f;
    static constexpr float kExploitRate = 1.f;

    // Behaviours
    float hunger_ = 0.0f;
    bool resourceAvailable_ = true;
    float tick_dt=0;

    sf::Vector2f home_position_;
    std::vector<Resource> resources_;
    Resource current_resource_;

  public:

    void SetupBehaviourTree(
        motion::Motor* npc_motor,
        motion::Path* path,
        TileMap* tilemap,
        sf::Vector2f home_position,
        std::vector<Resource> resources);
    void Update(float dt);

  };
}

#endif //NPC_BEHAVIOUR_TREE_H
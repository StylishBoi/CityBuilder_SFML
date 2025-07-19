#ifndef AI_NPC_BEHAVIOUR_TREE_H_
#define AI_NPC_BEHAVIOUR_TREE_H_

#include <memory>

#include "../gameplay/resources_manager.h"
#include "ai/bt_node.h"
#include "graphics/tilemap.h"
#include "motion/motor.h"
#include "motion/path.h"

namespace api::ai {
class NpcBehaviourTree {

  // Behaviour tree
  std::unique_ptr<core::ai::behaviour_tree::Node> bt_root_;
  // Behaviours
  float hunger_ = 0.0f;
  float tick_dt_ =0;
  float starvation_rate_=0;


  //Movement
  TileMap *tilemap_ = nullptr;
  motion::Motor *npc_motor_ = nullptr;
  motion::Path *path_ = nullptr;
  void SetDestination(const sf::Vector2f& destination) const;

  // Actions
  [[nodiscard]] core::ai::behaviour_tree::Status CheckHunger();
  [[nodiscard]] core::ai::behaviour_tree::Status Move() const;
  [[nodiscard]] core::ai::behaviour_tree::Status Eat();
  [[nodiscard]] core::ai::behaviour_tree::Status PickResource();
  [[nodiscard]] core::ai::behaviour_tree::Status GetResource();
  [[nodiscard]] core::ai::behaviour_tree::Status Idle();


  std::function<void(sf::Vector2f)> death_event = nullptr;

  // Behaviour Constants
  static constexpr float kHungerRate = 5.f;
  static constexpr float kExploitRate = 1.f;

  // Informations
  sf::Vector2f home_position_;
  std::vector<Resource*> resources_;
  EconomyManager* economy_manager_;
  Resource* current_resource_ = nullptr;

 public:

  void SetupBehaviourTree(
      motion::Motor* npc_motor,
      motion::Path* path,
      TileMap* tilemap,
      sf::Vector2f home_position,
      std::vector<Resource*> resources,
      EconomyManager* economyManager,
      std::function<void(sf::Vector2f)> deathEvent);
  void Update(float delta_time);

};
}

#endif  // AI_NPC_BEHAVIOUR_TREE_H_
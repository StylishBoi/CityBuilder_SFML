#ifndef NPC_H
#define NPC_H

#include <SFML/Graphics.hpp>

#include "npc_behaviour_tree.h"
#include "graphics/tilemap.h"
#include "motion/motor.h"
#include "motion/path.h"

namespace api::ai {
class Npc {

  sf::Texture texture_;

  // Decision
  std::unique_ptr<NpcBehaviourTree> bt_tree_ = std::make_unique<NpcBehaviourTree>();

  // Movement
  static constexpr float kMovingSpeed = 200.0f;
  std::unique_ptr<motion::Motor> motor_ = std::make_unique<motion::Motor>();
  std::unique_ptr<motion::Path> path_ = std::make_unique<motion::Path>();

  sf::Vector2f home_position_;

  // name
  std::string name_;

 public:
  void Setup(std::string_view name, std::string_view filename,
             TileMap* tilemap, sf::Vector2f& spawn_position,
             std::vector<Resource*> resources, EconomyManager* economyManager,
             std::function<void(sf::Vector2f)> deathEvent);
  void Update(float dt);
  void Draw(sf::RenderWindow &window) const;
  void SetPosition(const sf::Vector2f& position) {
    motor_->SetPosition(position);
  }
  sf::Vector2f GetHomePosition() const{
      return home_position_;
  }

};
}

#endif //NPC_H
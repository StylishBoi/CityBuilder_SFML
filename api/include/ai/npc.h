#ifndef NPC_H
#define NPC_H

#include <SFML/Graphics.hpp>

#include "ai/bt_node.h"
#include "assets/asset_manager.h"
#include "motion/motor.h"
#include "motion/path.h"

using namespace core::ai::behaviour_tree;
using namespace api::motion;

namespace api::ai {
  class Npc {
    enum class Animation {
      kEmpty,
      kBlue,
      kLength
    };

    std::string_view files[static_cast<size_t>(Animation::kLength)]{"empty.png", "npc_blue.png"};
    core::experimental::AssetManager<sf::Texture, Animation, "_assets/sprites"> textures;

    std::unique_ptr<Node> root_;

    static constexpr float kHungerRate=0.1f;
    static constexpr float kMovingSpeed=0.5f;

    Motor motor_;
    Path path_;

  public:
    void Setup();
    void Update(float dt);
    void Draw(sf::RenderWindow &window);

    //Actions
    Status Move();
    Status Eat();

    void SetupBehaviourTree();

    //Behaviours
    float hunger_=0;
    bool resourceAvailable_=true;

    bool target_reachable_=true;
    float target_distance_=20;

    void SetPath(const Path& path);
  };
}
#endif //NPC_H

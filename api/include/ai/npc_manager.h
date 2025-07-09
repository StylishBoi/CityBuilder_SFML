#ifndef NPC_MANAGER_H
#define NPC_MANAGER_H

#include "ai/npc.h"

namespace api::ai {

  enum class NpcType {
    kNone,
    kBlueLumberjack,
    kRedMiner,
    kGreenGatherer
};

  class NpcManager {
    std::vector<Npc> npcs_;

  public:
    void Add(NpcType type, TileMap* tilemap, sf::Vector2f start_position, ResourceManager& resources_manager);
    void Update(float dt);
    void Draw(sf::RenderWindow &window);

  };
}
#endif //NPC_MANAGER_H

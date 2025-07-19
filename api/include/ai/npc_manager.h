#ifndef AI_NPC_MANAGER_H_
#define AI_NPC_MANAGER_H_

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
    void Add(NpcType type,
            TileMap* tilemap,
            sf::Vector2f start_position,
            ResourceManager& resources_manager,
            EconomyManager* economyManager,
            std::function<void(sf::Vector2f)> deathEvent);
    void Update(float dt);
    void Draw(sf::RenderWindow& window);
    void RemoveNPC(sf::Vector2f npc_position);

  };
}
#endif  // AI_NPC_MANAGER_H_

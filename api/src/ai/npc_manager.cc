#include "ai/npc_manager.h"

#include "ai/npc_factory.h"

#ifdef TRACY_ENABLE
#include <tracy/Tracy.hpp>
#endif

namespace api::ai {

void NpcManager::Add(NpcType type,
                     TileMap* tilemap,
                     sf::Vector2f start_position,
                     ResourceManager& resources_manager,
                     EconomyManager* economyManager,
                     std::function<void(sf::Vector2f)> deathEvent) {
  CreateNpc(npcs_, type, tilemap, start_position, resources_manager, economyManager, deathEvent);;
}

void NpcManager::Update(float dt) {
  std::vector<Npc> npcs_copy;
  npcs_copy.reserve(npcs_.size());

  for (auto& npc : npcs_) {
    if (!npc.IsMarkedForDeath()) {
      npc.Update(dt);
      npcs_copy.push_back(std::move(npc));
    }
  }
  npcs_ = std::move(npcs_copy);

}

void NpcManager::Draw(sf::RenderWindow& window) {
  for (auto& npc : npcs_) {
    npc.Draw(window);
  }
}
void NpcManager::RemoveNPC(sf::Vector2f npc_position) {
  for (auto& npc : npcs_) {
    if (npc.GetHomePosition() == npc_position) {
      npc.MarkForDeath();
    }
  }
}
}
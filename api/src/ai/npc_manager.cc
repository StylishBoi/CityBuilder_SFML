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
#ifdef TRACY_ENABLE
  ZoneScoped;
#endif
  for (auto& npc : npcs_) {
    npc.Update(dt);
  }
}

void NpcManager::Draw(sf::RenderWindow& window) {
  for (auto& npc : npcs_) {
    npc.Draw(window);
  }
}
void NpcManager::RemoveNPC(sf::Vector2f npc_position) {
  auto removeIter = std::remove_if(npcs_.begin(), npcs_.end(),
                                   [&npc_position](const Npc& npc) {
                                     return npc.GetHomePosition() == npc_position;
                                   });
  npcs_.erase(removeIter, npcs_.end());
}

}
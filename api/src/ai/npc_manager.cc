#include "ai/npc_manager.h"

#include "ai/npc_factory.h"

#ifdef TRACY_ENABLE
#include <tracy/Tracy.hpp>
#endif

namespace api::ai {

void NpcManager::Add(NpcType type, TileMap* tilemap, sf::Vector2f start_position, ResourceManager& resources_manager, EconomyManager* economyManager) {
  CreateNpc(npcs_, type, tilemap, start_position, resources_manager, economyManager);
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
void NpcManager::RemoveNPC(Npc removedNpc) {
  for (auto& npc : npcs_) {
  }
}

}
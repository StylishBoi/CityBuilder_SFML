#include "ai/npc_manager.h"

#include "ai/npc_factory.h"

namespace api::ai {

void NpcManager::Add(NpcType type, TileMap* tilemap, ResourceManager* resources) {
  CreateNpc(npcs_, type, tilemap, resources);
}

void NpcManager::Update(float dt) {
  for (auto& npc : npcs_) {
    npc.Update(dt);
  }
}

void NpcManager::Draw(sf::RenderWindow& window) const {
  for (auto& npc : npcs_) {
    npc.Draw(window);
  }
}

}
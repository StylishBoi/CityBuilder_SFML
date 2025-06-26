#include "ai/npc_manager.h"

#include "ai/npc_factory.h"

namespace api::ai {

void NpcManager::Add(NpcType type, TileMap* tilemap, sf::Vector2f start_position, ResourceManager& resources_manager) {
  CreateNpc(npcs_, type, tilemap, start_position, resources_manager);
}

void NpcManager::Update(float dt) {
  for (auto& npc : npcs_) {
    npc.Update(dt);
  }
}

void NpcManager::Draw(sf::RenderWindow& window) {
  for (auto& npc : npcs_) {
    npc.Draw(window);
  }
}

}
#ifndef NPC_FACTORY_H
#define NPC_FACTORY_H
#include "npc_manager.h"

namespace api::ai {
  inline void CreateNpc(std::vector<Npc> &npcs, const NpcType type, TileMap* tilemap,  sf::Vector2f& start_position, ResourceManager& resources_manager){


    switch (type) {
      case NpcType::kBlueLumberjack:
        npcs.emplace_back();
        npcs.back().Setup("BLUE", "npc_blue.png", tilemap, start_position, resources_manager.GetResources(Resource::ResourceType::kWood));
        break;
      case NpcType::kRedMiner:
        npcs.emplace_back();
        npcs.back().Setup("RED", "npc_red.png", tilemap, start_position, resources_manager.GetResources(Resource::ResourceType::kWood));
        break;
      case NpcType::kGreenGatherer:
        npcs.emplace_back();
        npcs.back().Setup("GREEN","npc_green.png", tilemap, start_position, resources_manager.GetResources(Resource::ResourceType::kWood));
        break;
      default:
        break;
    }
    if (type == NpcType::kBlueLumberjack || type == NpcType::kRedMiner || type == NpcType::kGreenGatherer) {
      npcs.back().SetPosition(start_position);
    }
  }
}


#endif
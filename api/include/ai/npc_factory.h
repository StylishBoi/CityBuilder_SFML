#ifndef NPC_FACTORY_H
#define NPC_FACTORY_H
#include "npc_manager.h"

namespace api::ai {
  inline void CreateNpc(std::vector<Npc> &npcs, const NpcType type, TileMap* tilemap, Resources* resources){


    switch (type) {
      case NpcType::kBlue:
        npcs.emplace_back();
        npcs.back().Setup("BLUE", "npc_blue.png", tilemap, resources);
        break;
      case NpcType::kRed:
        npcs.emplace_back();
        npcs.back().Setup("RED", "npc_red.png", tilemap, resources);
        break;
      case NpcType::kGreen:
        npcs.emplace_back();
        npcs.back().Setup("GREEN","npc_green.png", tilemap, resources);
        break;
      default:
        break;
    }
  }
}


#endif
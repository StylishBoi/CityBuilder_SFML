#ifndef NPC_FACTORY_H
#define NPC_FACTORY_H
#include "npc_manager.h"

namespace api::ai {
  inline void CreateNpc(std::vector<Npc> &npcs, const NpcType type, TileMap* tilemap){


    switch (type) {
      case NpcType::kBlue:
        npcs.emplace_back();
        npcs.back().Setup("BLUE", "npc_blue.png", tilemap);
        break;
      case NpcType::kRed:
        npcs.emplace_back();
        npcs.back().Setup("RED", "npc_red.png", tilemap);
        break;
      case NpcType::kGreen:
        npcs.emplace_back();
        npcs.back().Setup("GREEN","npc_green.png", tilemap);
        break;
      default:
        break;
    }
  }
}


#endif
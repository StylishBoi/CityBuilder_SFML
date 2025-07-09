#ifndef ASTAR_H
#define ASTAR_H
#include <SFML/System/Vector2.hpp>
#include <__msvc_filebuf.hpp>
#include <filesystem>
#include <span>

#include "motion/path.h"

namespace api::motion {
  namespace Astar {

    Path GetPath(const int gridStep, sf::Vector2f start, sf::Vector2f end,
               std::vector<sf::Vector2f> walkableTiles);

  }
}


#endif //ASTAR_H
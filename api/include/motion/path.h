#ifndef PATH_H
#define PATH_H
#include <SFML/System/Vector2.hpp>
#include <array>
#include <vector>

namespace api::motion {
  class Path {
    int idxPoint_=0;
    std::vector<sf::Vector2f> pathPoints_;

  public:
    bool IsDone();
    sf::Vector2f GetNextPoint();
    void Fill(std::vector<sf::Vector2f>& pathPoints);
  };
}

#endif //PATH_H

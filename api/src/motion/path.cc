#include "motion/path.h"

using namespace api::motion;

bool Path::IsDone() {
  return idxPoint_==pathPoints_.size();
}

sf::Vector2f Path::GetNextPoint() {
  if (!IsDone()) {
    ++idxPoint_;
  }
  return pathPoints_[idxPoint_];
}

void Path::Fill(std::vector<sf::Vector2f>& pathPoints) {
  pathPoints_=pathPoints;
}


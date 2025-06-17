#include "motion/path.h"

using namespace api::motion;

//Verify if we reached the end of the path
bool Path::IsDone() const {
  // Check if the path is empty or if we're at the end
  return pathPoints_.empty() || idxPoint_ >= pathPoints_.size() - 1;
}


//Verify that the path isn't empty
bool Path::IsValid() const{
  return !pathPoints_.empty();
}

//Gets the next point on the path
sf::Vector2f Path::GetNextPoint() {
  // Return default position if path is empty
  if (pathPoints_.empty()) {
    return {0, 0};
  }

  // Make sure idxPoint_ doesn't exceed vector bounds
  if (idxPoint_ + 1 < pathPoints_.size()) {
    ++idxPoint_;
  }

  // Return current point (bounds already checked by now)
  return pathPoints_[idxPoint_];
}


void Path::Fill(std::vector<sf::Vector2f>& pathPoints) {
  // Reset index when filling new path
  idxPoint_ = 0;

  // Only fill if we have points
  if (!pathPoints.empty()) {
    pathPoints_ = std::move(pathPoints);  // Use move to avoid copy
  } else {
    pathPoints_.clear();  // Clear if empty path provided
  }
}


sf::Vector2f Path::StartPoint() const {
  //If the path isn't empty, return the first point of the path
  if (IsValid()) {
    return pathPoints_[0];
  }
  //If the path is empty, returns it to a base coordinate
  return {0,0};
}



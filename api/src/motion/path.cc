#include "motion/path.h"

#include <iostream>

using namespace api::motion;

//Verify if we reached the end of the path
bool Path::IsDone() const{
  // Check if the path is empty or if we're at the end
  return idxPoint_ == path_points_.size() - 1;
}

//Verify that the path isn't empty
bool Path::IsValid() const{
  return !path_points_.empty();
}

//Gets the next point on the path
sf::Vector2f Path::GetNextPoint(){

  // Return default position if path is empty
  if (!IsValid()) {
    return {0, 0};
  }

  // Make sure idxPoint_ doesn't exceed vector bounds
  if (!IsDone()) {
    ++idxPoint_;
  }

  // Return current point (bounds already checked by now)
  return path_points_[idxPoint_];
}

void Path::Fill(std::vector<sf::Vector2f>& path_points){
  // Only fill if we have points
  if (!path_points.empty())
    path_points_ = path_points;
}

sf::Vector2f Path::StartPoint() const{
  //If the path isn't empty, return the first point of the path
  if (IsValid()) {
    return path_points_[0];
  }
  //If the path is empty, returns it to a base coordinate
  return {0, 0,};
}

#include "motion/path.h"

using namespace api::motion;

//Verify if we reached the end of the path
bool Path::IsDone() const{
  return idxPoint_==pathPoints_.size()-1;
}

//Verify that the path isn't empty
bool Path::IsValid() const{
  return !pathPoints_.empty();
}

//Gets the next point on the path
sf::Vector2f Path::GetNextPoint() {
  //If the path is empty, it returns a basic coordinate
  if (!IsValid()) {
    return {0,0};
  }

  //If the path isn't done, get the next point of the path
  if (!IsDone()) {
    ++idxPoint_;
  }
  //Returns the next path point
  return pathPoints_[idxPoint_];
}

void Path::Fill(std::vector<sf::Vector2f>& pathPoints) {
  //Fills up the path if it isn't empty
  if (!pathPoints.empty()) {
    pathPoints_=pathPoints;
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



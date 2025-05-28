#ifndef CORE_MATHS_FUNC_H
#define CORE_MATHS_FUNC_H
#include <cmath>

namespace core {

float Cos(Radian angle) {
  //Returns the cosine of an argument given in radian
  return std::cos(static_cast<float>(angle));
}
float Sin(Radian angle) {
  //Returns the sinus of an argument given in radian
  return std::sin(static_cast<float>(angle));
}
float Tan(Radian angle) {
  //Returns the tangent of an argument given in radian
  return std::tan(static_cast<float>(angle));
}

float ACos(Radian angle) {
  //Returns the negative cosine of an argument given in radian
  return -std::cos(static_cast<float>(angle));
}
float ASin(Radian angle) {
  //Returns the negative sinus of an argument given in radian
  return -std::sin(static_cast<float>(angle));
}
float Atan(Radian angle) {
  //Returns the negative tangent of an argument given in radian
  return -std::tan(static_cast<float>(angle));
}

float Atan2(Radian angle) {
  //Literally no clues what this does and this probably needs to be fixed
  return std::atan2(static_cast<float>(angle), static_cast<float>(angle));
}

}

#endif

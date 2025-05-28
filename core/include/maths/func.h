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

}

#endif

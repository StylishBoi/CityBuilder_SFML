#ifndef CORE_MATHS_ANGLE_H
#define CORE_MATHS_ANGLE_H

#include "maths/const.h"

namespace core::maths {
//States/Initializes the class beforehand so it can be used within radian without causing an error
class Degree;
class Radian {
public:
  //Needs to be explicit and state that it is float
  constexpr explicit Radian(float value): radian_value_(value){}
  //No need to be explicit if the value is already a degree
  constexpr Radian(const Degree& angle);

  //Converts the radian into a float value
  explicit constexpr operator float() const { return radian_value_; }

private:
  //The value of the radian of the object
  float radian_value_;
};

class Degree {
public:
  //Needs to be explicit and state that it is float
  constexpr explicit Degree(float value): degree_value_(value){}
  //No need to be explicit if the value is already a radian
  constexpr Degree(const Radian& angle): degree_value_(static_cast<float>(angle)/Pi*180.0f) {}

  //Converts the degree into a float value
  explicit constexpr operator float() const { return degree_value_; }

private:
  //The value of the degree of the object
  float degree_value_;
};


constexpr Radian::Radian(const Degree& angle)
    : radian_value_(static_cast<float>(angle) / 180.0f * Pi) {}
}

#endif
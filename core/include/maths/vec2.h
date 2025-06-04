#ifndef VEC2_H
#define VEC2_H
#include <cmath>
#include <type_traits>

namespace core::maths {

//Allows to intake any arguments no matter the type
template <typename VectorT, typename T>
//Concept is a set of requirements
//Requires defines the constraint
//In this case, the values of VectorT must be the same as the type T
concept is_vector2 = requires(VectorT v){
  {v.x} -> std::same_as<T&>;
  {v.y} -> std::same_as<T&>;
};

template <typename VectorT, typename T>
//In this case, the values of VectorT can be converted into type T
concept is_convertible_to_vector2 = requires(VectorT v){
  {v.x}->std::convertible_to<T>;
  {v.y}->std::convertible_to<T>;
};

//Verify if the type T is a number
template <typename T>
  requires std::is_arithmetic_v<T>

class Vec2 {

  public:
  //X and Y coordinates which values can be any type that is a number
  T x{}, y{};
  //Use (empty) which is given by the compiler
  constexpr Vec2()=default;
  //Sets the x and y values of the Vec2
  constexpr Vec2(T x, T y): x{x}, y{y} {}


  //Verify if it fits the Vec2 requirements before changing the values of Vec2
  template <typename VectorT>
    requires is_vector2<VectorT, T>
  //The use of explicit is to avoid converting types
  constexpr explicit Vec2(VectorT v): x{v.x}, y{v.y} {}

  //Verify if it can be converted to Vec2
  template <typename VectorT>
    requires is_convertible_to_vector2<VectorT, T> && !is_vector2<VectorT, T>
  //The use of explicit is to avoid converting types
  constexpr explicit Vec2(VectorT v):
  //Converts x and y to the given type
    x(static_cast<T>(v.x)), y(static_cast<T>(v.y)) {}

  //Adds up two Vec2 together
  //Will be called via the use of the operator
  //constexpr makes it possible to evaluate the value at compile time
  //nodiscard will serve as a way to mark a function which result should not be ignored
  [[nodiscard]] constexpr Vec2 operator+(Vec2 other) const {
    return {x + other.x, y + other.y};
  }

  //Subtracts up two Vec2 together
  //Will be called via the use of the operator
  //constexpr makes it possible to evaluate the value at compile time
  //nodiscard will serve as a way to mark a function which result should not be ignored
  [[nodiscard]] constexpr Vec2 operator-(Vec2 other) const {
    return {x - other.x, y - other.y};
  }

  //Multiply the two Vec2 together
  //constexpr makes it possible to evaluate the value at compile time
  [[nodiscard]] static constexpr float Dot(const Vec2 v1,const Vec2 v2)
  {
    return v1.x * v2.x + v1.y * v2.y;
  }

  //The requirement is to verify if the number is a float type as you cant find the sqrt for an int
  //constexpr makes it possible to evaluate the value at compile time
  [[nodiscard]] static constexpr T Length()
    requires std::is_floating_point_v<T>
  {
    return std::sqrt(x * x + y * y);
  }
};
}

#endif //VEC2_H

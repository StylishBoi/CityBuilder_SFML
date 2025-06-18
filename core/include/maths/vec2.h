#ifndef VEC2_H
#define VEC2_H
#include <cmath>
#include <type_traits>

namespace core::maths {

//Allows to intake any arguments no matter the type
template <typename VectorT, typename T>
//Concept is a set of requirements
//Requires defines the constraint
//In this case, the values of VectorT must be the same as the type T otherwise the two vecs can't work together
concept is_vector2 = requires(VectorT v){
  {v.x} -> std::same_as<T&>;
  {v.y} -> std::same_as<T&>;
};

template <typename VectorT, typename T>
//In this case, the values of VectorT can be converted into type T
//Converts the other vector into something workable for VectorT
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
  [[nodiscard]] constexpr Vec2 operator+(Vec2 other) const {
    return {x + other.x, y + other.y};
  }

  //Subtracts up two Vec2 together
  [[nodiscard]] constexpr Vec2 operator-(Vec2 other) const {
    return {x - other.x, y - other.y};
  }

  //Multiply the two Vec2 together
  //constexpr makes it possible to evaluate the value at compile time
  [[nodiscard]] constexpr T Dot(const Vec2 v1,const Vec2 v2)
  {
    return v1.x * v2.x + v1.y * v2.y;
  }

  //Multiply only one Vec2f based on one given value from the other vec2f
  //Will be called via the use of the operator
  [[nodiscard]] constexpr Vec2 operator*(const T t) const
  {
    return { x * t,y * t };
  }

  //Same thing as above but takes in the other vec2f
  //Friend means it will take elements from another class
  [[nodiscard]] friend constexpr Vec2 operator*(const T t, const Vec2 vec) {
    return { t * vec.x, t * vec.y };
  }

  //Divide a vec2f based on one given value from the other vec2f
  [[nodiscard]] constexpr Vec2 operator/(const T t) const
  {
    return { x / t,y / t };
  }

  //Returns the vec2f with a value made negative
  //nodiscard will serve as a way to mark a function which result should not be ignored
  [[nodiscard]] constexpr Vec2 Perpendicular() const
  {
    return { -y, x };
  }

  //Returns the vec2f with a value made negative
  //nodiscard will serve as a way to mark a function which result should not be ignored
  [[nodiscard]] constexpr Vec2 Perpendicular2() const
  {
    return { y, -x };
  }

  //Calculate the result of a starting point and the distance crossed (brings out arrival point)
  [[nodiscard]] constexpr T Lerp(const Vec2 v1, const T t)
  {
    return v1.x * (1 - t) + v1.y * t;
  }

  //nodiscard will serve as a way to mark a function which result should not be ignored
  //Calculates the size of a vector by doing a square operation
  [[nodiscard]] T MagnitudeSqu() const
  {
    return  x * x + y * y;
  }

  //nodiscard will serve as a way to mark a function which result should not be ignored
  //Calculates the size of a vector by calling a different function that handles it
  [[nodiscard]] T Magnitude() const
  {
    //Calls the function which calculates the size of the vector up above
    return std::sqrt(MagnitudeSqu());
  }

  //nodiscard will serve as a way to mark a function which result should not be ignored
  [[nodiscard]] Vec2 Normalize() const
  {
    //Calls the magnitude function and puts it in a local function
    const auto man = Magnitude();
    //If the local variable equates to 0, it will return a Vec2F zero
    if (man == 0.0f)
    {
      return Vec2(0, 0);
    }
    //Return the vec2f using the division function and dividing by the magnitude
    return *this / man;
  }

  [[nodiscard]] Vec2 Rotate(const float angle)
  {
    const float c = std::cos(angle);
    const float s = std::sin(angle);
    const float new_x = c * x - s * y;
    const float new_y = s * x + c * y;
    x = new_x;
    y = new_y;

    return {x, y};
  }

  [[nodiscard]] T MiddleAngle(const Vec2 other) const
  {
    auto dot = (x*other.x) + (y*other.y);      // Dot product between [x1, y1] and [x2, y2]
    auto det = (x*other.y) - (y*other.x) ;     // Determinant
    auto result_angle = atan2(det, dot);  // atan2(y, x) or atan2(sin, cos)

    return result_angle;
  }

  //The requirement is to verify if the number is a float type as you cant find the sqrt for an int
  //constexpr makes it possible to evaluate the value at compile time
  [[nodiscard]] static constexpr T Length()
    requires std::is_floating_point_v<T>
  {
    return std::sqrt(x * x + y * y);
  }
};
using Vec2F=Vec2<float>;
using Vec2D=Vec2<double>;
using Vec2I=Vec2<int32_t>;
using Vec2U=Vec2<uint32_t>;
}


#endif //VEC2_H

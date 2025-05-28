#ifndef CORE_MATHS_VEC2F_H
#define CORE_MATHS_VEC2F_H

#include <complex>
#include <iostream>

namespace core::maths
{
//Creates the Vec2f but the commands only work when the Vec2f is intiliazed
//Constexpr means the code can be ran at compile time
    struct Vec2f
    {
        float x = 0, y = 0;

      //Adds up two Vec2f together
      //Will be called via the use of the operator
        constexpr Vec2f operator+(const Vec2f other) const
        {
            return { x + other.x, y + other.y };
        }

      //Adds two Vec2f together
      //Will be called via the use of the operator
      constexpr Vec2f operator+=(const Vec2f other) const
        {
          return { x+other.x, y+other.y};
      }

      // Subtracts two Vec2f together
      //Will be called via the use of the operator
        constexpr Vec2f operator-(const Vec2f other) const
        {
            return { x - other.x, y - other.y };
        }

      //Makes the Vec2f negative if it has no parameter
        constexpr Vec2f operator-() const
        {
            return { -x, -y };
        }

      //Multiply the two Vec2f together
        static constexpr float Dot(const Vec2f v1,const Vec2f v2)
        {
            return v1.x * v2.x + v1.y * v2.y;
        }

      //Multiply only one Vec2f based on one given value from the other vec2f
      //Will be called via the use of the operator
        constexpr Vec2f operator*(const float t) const
        {
            return { x * t,y * t };
        }

        /*constexpr Vec2f operator*(float nb, const Vec2f other) noexcept {
          return other * nb;
        }*/

      //Same thing as above but takes in the other vec2f
      //Friend means it will take elements from another class
        friend constexpr Vec2f operator*(const float t, const Vec2f& vec) {
            return { t * vec.x, t * vec.y };
        }

        //Divide a vec2f based on one given value from the other vec2f
        [[nodiscard]] constexpr Vec2f operator/(const float t) const
        {
            return { x / t,y / t };
        }

        //Returns the vec2f with a value made negative
        //nodiscard will serve as a way to mark a function which result should not be ignored
        [[nodiscard]] constexpr Vec2f Perpendicular() const
        {
            return { -y, x };
        }

        //Returns the vec2f with a value made negative
        //nodiscard will serve as a way to mark a function which result should not be ignored
        [[nodiscard]] constexpr Vec2f Perpendicular2() const
        {
            return { y, -x };
        }

      //Calculate the result of a starting point and the distance crossed (brings out arrival point)
        static constexpr float Lerp(const Vec2f v1, const float t)
        {
            return v1.x * (1 - t) + v1.y * t;
        }

        //nodiscard will serve as a way to mark a function which result should not be ignored
        //Calculates the size of a vector by doing a square operation
        [[nodiscard]] float MagnitudeSqu() const
        {
            return  x * x + y * y;
        }

        //nodiscard will serve as a way to mark a function which result should not be ignored
        //Calculates the size of a vector by calling a different function that handles it
        [[nodiscard]] float Magnitude() const
        {
          //Calls the function which calculates the size of the vector up above
            return std::sqrt(MagnitudeSqu());
        }

        //nodiscard will serve as a way to mark a function which result should not be ignored
        [[nodiscard]] Vec2f Normalize() const
        {
          //Calls the magnitude function and puts it in a local function
            const float man = Magnitude();
          //If the local variable equates to 0, it will return a Vec2F zero
            if (man == 0.0f)
            {
                return Vec2f(0, 0);
            }
          //Return the vec2f using the division function and dividing by the magnitude
            return *this / man;
        }
    }; // struct Vec2i
} // namespace core





#endif
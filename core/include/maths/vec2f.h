#ifndef VEC2F_H
#define VEC2F_H

#include <complex>
#include <iostream>

namespace core::maths
{
//Creates the Vec2f but the commands only work when the Vec2f is intiliazed
    struct Vec2f
    {
        float x = 0, y = 0;

      //Adds up two Vec2f together
        constexpr Vec2f operator+(const Vec2f other) const
        {
            return { x + other.x, y + other.y };
        }

      //Subtracts two Vec2f together
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

      //Multiply only one Vec2f based on one given value from the other
        constexpr Vec2f operator*(const float t) const
        {
            return { x * t,y * t };
        }

        friend constexpr Vec2f operator*(const float t, const Vec2f& vec) {
            return { t * vec.x, t * vec.y };
        }

        constexpr Vec2f operator/(const float t) const
        {
            return { x / t,y / t };
        }


        [[nodiscard]] constexpr Vec2f Perpendicular() const
        {
            return { -y, x };
        }

        [[nodiscard]] constexpr Vec2f Perpendicular2() const
        {
            return { y, -x };
        }

        static constexpr float Lerp(const Vec2f v1, const float t)
        {
            return v1.x * (1 - t) + v1.y * t;
        }

        [[nodiscard]] float MagnitudeSqu() const
        {
            return  x * x + y * y;
        }

        [[nodiscard]] float Magnitude() const
        {
            return std::sqrt(MagnitudeSqu());
        }

        [[nodiscard]] Vec2f Normalize() const
        {
            const float man = Magnitude();
            if (man == 0.0f)
            {
                return Vec2f(0, 0);
            }
            return *this / man;
        }

        void Rotate(const float angle)
        {
            const float c = std::cos(angle);
            const float s = std::sin(angle);
            const float new_x = c * x - s * y;
            const float new_y = s * x + c * y;
            x = new_x;
            y = new_y;
        }

        [[nodiscard]] float Rotate() const
        {
            return std::atan2(x, y);
        }
    }; // struct Vec2i
} // namespace core





#endif
#include "gtest/gtest.h"
#include "maths/vec2.h"
#include "maths/vec2f.h"
#include <SFML/System/Vector2.hpp>

TEST(Vec2, Empty) {
  core::maths::Vec2 v1{1.2f, 1.3f};
  sf::Vector2f v2 = sf::Vector2f(1.2f, 1.3f);
  core::maths::Vec2<float> v { v2 };
}
#include "gtest/gtest.h"
#include "maths/vec2.h"
#include "maths/vec2f.h"
#include <SFML/System/Vector2.hpp>

TEST(Vec2, Conversion) {
  core::maths::Vec2 v1{1.2f, 1.3f};
  sf::Vector2f v2 = sf::Vector2f(1.2f, 1.3f);
  core::maths::Vec2<float> v { v2 };
  EXPECT_FLOAT_EQ(v1.x,v2.x);
}

TEST(Vec2, Add) {
  core::maths::Vec2 v1{1.2f, 1.3f};
  core::maths::Vec2 v2{1.2f, 1.3f};

  auto result = v1 + v2;

  EXPECT_FLOAT_EQ(result.x, v1.x + v2.x);
  EXPECT_FLOAT_EQ(result.y, v1.y + v2.y);
}
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
  core::maths::Vec2 v2{1.0f, 2.1f};

  auto result = v1 + v2;

  EXPECT_FLOAT_EQ(result.x, v1.x + v2.x);
  EXPECT_FLOAT_EQ(result.y, v1.y + v2.y);
}

TEST(Vec2, Sub) {
  core::maths::Vec2 v1{1.2f, 1.3f};
  core::maths::Vec2 v2{1.2f, 1.3f};

  auto result = v1 - v2;

  EXPECT_FLOAT_EQ(result.x, v1.x - v2.x);
  EXPECT_FLOAT_EQ(result.y, v1.y - v2.y);
}

/*TEST(Vec2, Dot)
{
  core::maths::Vec2 v1{1.2f, 1.3f};
  core::maths::Vec2 v2{1.2f, 1.3f};

  //Multiples both Vec2f togethers via the function in the header
  const auto result = core::maths::Vec2<>::Dot(v1, v2);

  //Verify if the float values are approximately equal
  EXPECT_FLOAT_EQ(result, v1.x * v2.x + v1.y * v2.y);
}*/

TEST(Vec2, Multi)
{
  core::maths::Vec2 v1{1, 2};
  core::maths::Vec2 v2{3, -4};

  //Multiply a Vec2 based on only one value from the other Vec2
  const auto result = v1 * v2.x;
  const auto result2 = v1.x * v2;

  //Verify if the float values are approximately equal
  EXPECT_FLOAT_EQ(result.x, v1.x * v2.x);
  EXPECT_FLOAT_EQ(result.y, v1.y * v2.x);
  EXPECT_FLOAT_EQ(result2.x, v1.x * v2.x);
  EXPECT_FLOAT_EQ(result2.y, v1.x * v2.y);

}

TEST(Vec2, Div)
{
  core::maths::Vec2 v1{1.2f, 1.3f};
  core::maths::Vec2 v2{1.2f, 1.3f};

  //Function which will divide the two vec2f based on the value of one of the axes of one of the vec2f
  auto testDivByComponent = [&](float divisor, const auto& vecA, const auto& vecB)
  {
    //Function found in header which divides the vec2f with a divider
    const auto resA = vecA / divisor;
    const auto resB = vecB / divisor;

    //Function checking if a value is infinite or is not real
    auto checkInfOrNan = [](const float origVal, const float resVal)
    {
      //Verify the value and says if it's true or not
      //If true, the code will continue running
      if(origVal != 0.0f)
        EXPECT_TRUE(std::isinf(resVal));
      else
        EXPECT_TRUE(std::isnan(resVal));
    };

    //If the divisor is not 0, it will check the division
    if(divisor != 0.0f)
    {
      //Verify if the float values are approximately equal
      EXPECT_FLOAT_EQ(resA.x, vecA.x / divisor);
      EXPECT_FLOAT_EQ(resA.y, vecA.y / divisor);
      EXPECT_FLOAT_EQ(resB.x, vecB.x / divisor);
      EXPECT_FLOAT_EQ(resB.y, vecB.y / divisor);
    }
    //If is 0, it will check for potential errors via a function
    else
    {
      checkInfOrNan(vecA.x, resA.x);
      checkInfOrNan(vecA.y, resA.y);
      checkInfOrNan(vecB.x, resB.x);
      checkInfOrNan(vecB.y, resB.y);
    }
  };

  //Goes through a function to test the divisions
  testDivByComponent(v2.x, v1, v2);
  testDivByComponent(v2.y, v1, v2);
  testDivByComponent(v1.x, v2, v1);
  testDivByComponent(v1.y, v2, v1);
}

/*TEST(Vec2, Perpendicular)
{
  core::maths::Vec2 v1{1.2f, 1.3f};
  core::maths::Vec2 v2{1.2f, 1.3f};

  //Create the perpendicular line by making a point negative
  const auto p1 = v1.Perpendicular();
  const auto p2 = v2.Perpendicular();
  //Verify if the float values are approximately equal
  EXPECT_FLOAT_EQ(core::maths::Vec2::Dot(v1, p1), 0);
  EXPECT_FLOAT_EQ(core::maths::Vec2::Dot(v2, p2), 0);

  //Create the perpendicular line by making a point negative
  const auto r1 = v1.Perpendicular2();
  const auto r2 = v2.Perpendicular2();
  //Verify if the float values are approximately equal
  EXPECT_FLOAT_EQ(core::maths::Vec2::Dot(v1, r1), 0);
  EXPECT_FLOAT_EQ(core::maths::Vec2::Dot(v2, r2), 0);
}*/

/*TEST(Vec2, Lerp)
{
  core::maths::Vec2 v1{1.2f, 1.3f};
  core::maths::Vec2 v2{1.2f, 1.3f};

  //Determines the arrival coordinate
  const auto result1 = core::maths::Vec2::Lerp(v1, v2.x);
  const auto result2 = core::maths::Vec2::Lerp(v1, v2.y);
  const auto result3 = core::maths::Vec2::Lerp(v2, v1.x);
  const auto result4 = core::maths::Vec2::Lerp(v2, v1.y);
  //Verify if the float values are approximately equal
  EXPECT_FLOAT_EQ(result1, v1.x * (1 - v2.x) + v1.y * v2.x);
  EXPECT_FLOAT_EQ(result2, v1.x * (1 - v2.y) + v1.y * v2.y);
  EXPECT_FLOAT_EQ(result3, v2.x * (1 - v1.x) + v2.y * v1.x);
  EXPECT_FLOAT_EQ(result4, v2.x * (1 - v1.y) + v2.y * v1.y);
}*/

TEST(Vec2, Magnitude)
{
  core::maths::Vec2 v1{1.2f, 1.3f};
  core::maths::Vec2 v2{1.2f, 1.3f};

  //Calculates the size/distance of a vector
  const auto resultv1 = v1.Magnitude();
  const auto resultv2 = v2.Magnitude();
  //Verify if the float values are approximately equal
  EXPECT_FLOAT_EQ(resultv1, v1.Magnitude());
  EXPECT_FLOAT_EQ(resultv2, v2.Magnitude());
}

TEST(Vec2, SquMagnitude)
{
  core::maths::Vec2 v1{1.2f, 1.3f};
  core::maths::Vec2 v2{1.2f, 1.3f};

  //Calculates the size/distance of a vector
  const auto resultv1 = v1.MagnitudeSqu();
  const auto resultv2 = v2.MagnitudeSqu();
  //Verify if the float values are approximately equal
  EXPECT_FLOAT_EQ(resultv1, v1.MagnitudeSqu());
  EXPECT_FLOAT_EQ(resultv2, v2.MagnitudeSqu());
}

TEST(Vec2, Normalize)
{
  core::maths::Vec2 v1{1.2f, 1.3f};
  core::maths::Vec2 v2{1.2f, 1.3f};

  //Takes the result of the normalize function which finds
  auto resultv1 = v1.Normalize();
  auto resultv2 = v2.Normalize();
  //Honestly no idea what we're trying to achieve here
  if(v1.MagnitudeSqu() == 0)
  {
    EXPECT_FLOAT_EQ(resultv1.MagnitudeSqu(), 0);
  }
  else
  {
    EXPECT_FLOAT_EQ(resultv1.MagnitudeSqu(), 1);
  }
  if(v2.MagnitudeSqu() == 0)
  {
    EXPECT_FLOAT_EQ(resultv2.MagnitudeSqu(), 0);
  }
  else
  {
    EXPECT_FLOAT_EQ(resultv2.MagnitudeSqu(), 1);
  }
}

TEST(Vec2, Rotate)
{
  core::maths::Vec2 v1{1.2f, 1.3f};
  core::maths::Vec2 v2{1.2f, 1.3f};

  const core::maths::Vec2f expected_v1 = {
    v1.x * std::cos(0.5f) - v1.y * std::sin(0.5f),
    v1.x * std::sin(0.5f) + v1.y * std::cos(0.5f)
};

  const core::maths::Vec2f expected_v2 = {
    v2.x * std::cos(0.5f) - v2.y * std::sin(0.5f),
    v2.x * std::sin(0.5f) + v2.y * std::cos(0.5f)
};

  v1.Rotate(0.5f);
  v2.Rotate(0.5f);

  //Verify if the float values are approximately equal
  EXPECT_FLOAT_EQ(v1.x, expected_v1.x);
  EXPECT_FLOAT_EQ(v1.y, expected_v1.y);

  //Verify if the float values are approximately equal
  EXPECT_FLOAT_EQ(v2.x, expected_v2.x);
  EXPECT_FLOAT_EQ(v2.y, expected_v2.y);
}

TEST(Vec2, MiddleAngle)
{
  core::maths::Vec2 v1{1.2f, 1.3f};
  core::maths::Vec2 v2{1.2f, 1.3f};

  //Find the middle angle for both vectors using a function
  const auto angle1 = v1.MiddleAngle(v2);
  const auto angle2 = v2.MiddleAngle(v1);

  const float expected_angle1={
    atan2(((v1.x*v2.y) - (v1.y*v2.x)), ((v1.x*v2.x) + (v1.y*v2.y)))
  };
  const float expected_angle2={
    atan2(((v2.x*v1.y) - (v2.y*v1.x)), ((v2.x*v1.x) + (v2.y*v1.y)))
  };

  //Verify if the float values are approximately equal
  EXPECT_FLOAT_EQ(angle1, expected_angle1);
  EXPECT_FLOAT_EQ(angle2, expected_angle2);
}
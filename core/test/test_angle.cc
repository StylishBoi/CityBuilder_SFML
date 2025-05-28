#include "gtest/gtest.h"
#include "maths/angle.h"
#include "maths/func.h"

struct AngleOperationFixture : public ::testing::TestWithParam<float>
{
};

TEST_P(AngleOperationFixture, ConversionIntoRadian) {

  //Defines v1 and v2 with the parameter insert command
  //The parameter values can be found at the bottom of the code
  const auto test_value = GetParam();

  //Makes the float value into a degree
  const core::Degree test_degree{test_value};

  //Converts the degree into a radian
  const core::Radian float_radian_result{test_degree};

  // Transform the radian result into float to test the result
  const auto result = (static_cast<float>(float_radian_result));


  //Verify if the degree conversion into radian worked
  EXPECT_FLOAT_EQ(result, test_value*(core::Pi/180.0f));
}

TEST_P(AngleOperationFixture, ConversionIntoDegree) {

  //Defines v1 and v2 with the parameter insert command
  //The parameter values can be found at the bottom of the code
  const auto test_value = GetParam();

  //Makes the float value into a radian
  const core::Radian test_radian{test_value};

  //Converts the radian into a degree
  const core::Degree float_degree_result{test_radian};

  // Transform the degree result into float to test the result
  const auto result = (static_cast<float>(float_degree_result));

  //Verify if the radian conversion into degree worked
  EXPECT_FLOAT_EQ(result, test_value*(180.0f/core::Pi));
}

TEST_P(AngleOperationFixture, ACos) {

  //Defines v1 and v2 with the parameter insert command
  //The parameter values can be found at the bottom of the code
  const auto test_value = GetParam();

  //Makes the float value into a radian
  const core::Radian test_radian{test_value};

  //Converts the radian into a float value
  const auto result = ACos(test_radian);

  //Verify if acos worked
  EXPECT_FLOAT_EQ(result, -std::cos(static_cast<float>(test_value)));
}

TEST_P(AngleOperationFixture, ASin) {

  //Defines v1 and v2 with the parameter insert command
  //The parameter values can be found at the bottom of the code
  const auto test_value = GetParam();

  //Makes the float value into a radian
  const core::Radian test_radian{test_value};

  //Converts the radian into a float value
  const auto result = ASin(test_radian);

  //Verify if asin worked
  EXPECT_FLOAT_EQ(result, -std::sin(static_cast<float>(test_value)));
}

TEST_P(AngleOperationFixture, Atan) {

  //Defines v1 and v2 with the parameter insert command
  //The parameter values can be found at the bottom of the code
  const auto test_value = GetParam();

  //Makes the float value into a radian
  const core::Radian test_radian{test_value};

  //Converts the radian into a float value
  const auto result = Atan(test_radian);

  //Verify if atan worked
  EXPECT_FLOAT_EQ(result, -std::tan(static_cast<float>(test_value)));
}

INSTANTIATE_TEST_SUITE_P(AllNumbers,
                         AngleOperationFixture,
                         testing::Values(
                           45.0f,
                           -45.0f,
                           90.0f,
                           75.0f,
                           0.0f,
                           1028.0f
                         )
);
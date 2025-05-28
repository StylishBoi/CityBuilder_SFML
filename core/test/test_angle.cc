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

  //Converts the degree into a radian and converts to a float value
  //const auto float_radian_result = core::Cos(static_cast<core::Radian>(test_degree));
  //std::cout << float_result << " and " << std::cos((core::Pi/4.0f)*numberOfRadians) << std::endl;

  //Verify if the degree conversion into radian worked
  //Multiply by the number of radians to be expected
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
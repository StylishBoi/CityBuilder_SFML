#include <SFML/Window/ContextSettings.hpp>

#include "gtest/gtest.h"
#include "maths/angle.h"
#include "maths/func.h"

/*struct AngleOperationFixture : public ::testing::TestWithParam<float>
{
};*/

TEST(Vec2f, Conversion) {
  core::Degree test_degree_{45.0f};

  auto result = core::Cos(static_cast<core::Radian>(test_degree_));

  EXPECT_FLOAT_EQ(result, std::cos(core::Pi/4.0f));
}

/*INSTANTIATE_TEST_SUITE_P(AllNumbers,
                         AngleOperationFixture,
                         testing::Values(
                           2.0f,
                           -2.0f,
                           0.0f
                         )
);*/
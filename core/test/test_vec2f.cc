#include "maths/vec2f.h"

#include <gtest/gtest.h>
#include <iostream>

struct Vec2fOperationFixture : public ::testing::TestWithParam<std::pair<core::maths::Vec2f, core::maths::Vec2f>>
{
};

//TEST_P means it's a test using a value as a parameter.
//The parameter values can be found at the bottom of the code
TEST_P(Vec2fOperationFixture, Add)
{
  //Defines v1 and v2 with the parameter insert command
  //The parameter values can be found at the bottom of the code
	auto       [v1, v2] = GetParam();

  //Adds up the two 'Vec2f' via the operator+ found in the header
	const auto result = v1 + v2;

  //Verify if the float values are approximately equal
	EXPECT_FLOAT_EQ(result.x, v1.x + v2.x);
	EXPECT_FLOAT_EQ(result.y, v1.y + v2.y);
}

TEST_P(Vec2fOperationFixture, Sub)
{
  //Defines v1 and v2 with the parameter insert command
  //The parameter values can be found at the bottom of the code
	auto       [v1, v2] = GetParam();

  //Subtracts the two 'Vec2f' via the operator- found in the header
	const auto result = v1 - v2;

  //Verify if the float values are approximately equal
	EXPECT_FLOAT_EQ(result.x, v1.x - v2.x);
	EXPECT_FLOAT_EQ(result.y, v1.y - v2.y);

  //Makes the 'Vec2f' become negative via the header
	const auto neg1 = -v1;
	const auto neg2 = -v2;

  //Verify if the float values are approximately equal
	EXPECT_FLOAT_EQ(neg1.x, -v1.x);
	EXPECT_FLOAT_EQ(neg1.y, -v1.y);
	EXPECT_FLOAT_EQ(neg2.x, -v2.x);
	EXPECT_FLOAT_EQ(neg2.y, -v2.y);
}

TEST_P(Vec2fOperationFixture, Dot)
{
  //Defines v1 and v2 with the parameter insert command
  //The parameter values can be found at the bottom of the code
	auto       [v1, v2] = GetParam();

  //Multiples both Vec2f togethers via the function in the header
	const auto result = core::maths::Vec2f::Dot(v1, v2);

  //Verify if the float values are approximately equal
	EXPECT_FLOAT_EQ(result, v1.x * v2.x + v1.y * v2.y);
}

TEST_P(Vec2fOperationFixture, Multi)
{
  //Defines v1 and v2 with the parameter insert command
  //The parameter values can be found at the bottom of the code
	auto       [v1, v2] = GetParam();

  //Multiply a Vec2f based on only one value from the other Vec2f
	const auto result = v1 * v2.x;
	const auto result2 = v1.x * v2;

  //Verify if the float values are approximately equal
	EXPECT_FLOAT_EQ(result.x, v1.x * v2.x);
	EXPECT_FLOAT_EQ(result.y, v1.y * v2.x);
	EXPECT_FLOAT_EQ(result2.x, v1.x * v2.x);
	EXPECT_FLOAT_EQ(result2.y, v1.x * v2.y);

}

TEST_P(Vec2fOperationFixture, Div)
{
  //Defines v1 and v2 with the parameter insert command
  //The parameter values can be found at the bottom of the code
	auto [v1, v2] = GetParam();

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


TEST_P(Vec2fOperationFixture, Perpendicular)
{
  //Defines v1 and v2 with the parameter insert command
  //The parameter values can be found at the bottom of the code
	auto       [v1, v2] = GetParam();

  //Create the perpendicular line by making a point negative
	const auto p1 = v1.Perpendicular();
	const auto p2 = v2.Perpendicular();
  //Verify if the float values are approximately equal
	EXPECT_FLOAT_EQ(core::maths::Vec2f::Dot(v1, p1), 0);
	EXPECT_FLOAT_EQ(core::maths::Vec2f::Dot(v2, p2), 0);

  //Create the perpendicular line by making a point negative
	const auto r1 = v1.Perpendicular2();
	const auto r2 = v2.Perpendicular2();
  //Verify if the float values are approximately equal
	EXPECT_FLOAT_EQ(core::maths::Vec2f::Dot(v1, r1), 0);
	EXPECT_FLOAT_EQ(core::maths::Vec2f::Dot(v2, r2), 0);
}

TEST_P(Vec2fOperationFixture, Lerp)
{
  //Defines v1 and v2 with the parameter insert command
  //The parameter values can be found at the bottom of the code
	auto       [v1, v2] = GetParam();

  //Determines the arrival coordinate
	const auto result1 = core::maths::Vec2f::Lerp(v1, v2.x);
	const auto result2 = core::maths::Vec2f::Lerp(v1, v2.y);
	const auto result3 = core::maths::Vec2f::Lerp(v2, v1.x);
	const auto result4 = core::maths::Vec2f::Lerp(v2, v1.y);
  //Verify if the float values are approximately equal
	EXPECT_FLOAT_EQ(result1, v1.x * (1 - v2.x) + v1.y * v2.x);
	EXPECT_FLOAT_EQ(result2, v1.x * (1 - v2.y) + v1.y * v2.y);
	EXPECT_FLOAT_EQ(result3, v2.x * (1 - v1.x) + v2.y * v1.x);
	EXPECT_FLOAT_EQ(result4, v2.x * (1 - v1.y) + v2.y * v1.y);

}

TEST_P(Vec2fOperationFixture, Magnitude)
{
  //Defines v1 and v2 with the parameter insert command
  //The parameter values can be found at the bottom of the code
	auto       [v1, v2] = GetParam();

  //Calculates the size/distance of a vector
	const auto resultv1 = v1.Magnitude();
	const auto resultv2 = v2.Magnitude();
  //Verify if the float values are approximately equal
	EXPECT_FLOAT_EQ(resultv1, v1.Magnitude());
	EXPECT_FLOAT_EQ(resultv2, v2.Magnitude());
}

TEST_P(Vec2fOperationFixture, SquMagnitude)
{
  //Defines v1 and v2 with the parameter insert command
  //The parameter values can be found at the bottom of the code
	auto       [v1, v2] = GetParam();
  //Calculates the size/distance of a vector
	const auto resultv1 = v1.MagnitudeSqu();
	const auto resultv2 = v2.MagnitudeSqu();
  //Verify if the float values are approximately equal
	EXPECT_FLOAT_EQ(resultv1, v1.MagnitudeSqu());
	EXPECT_FLOAT_EQ(resultv2, v2.MagnitudeSqu());
}

TEST_P(Vec2fOperationFixture, Normalize)
{
  //Defines v1 and v2 with the parameter insert command
  //The parameter values can be found at the bottom of the code
	auto [v1, v2] = GetParam();

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

//The series of parameter values that will be used throughout the code for the lines using TEST_P
INSTANTIATE_TEST_SUITE_P(AllNumbers,
                         Vec2fOperationFixture,
                         testing::Values(
	                         std::pair{ core::maths::Vec2f{1.5f,3.2f}, core::maths::Vec2f{2.3f,-4.1f} },
	                         std::pair{ core::maths::Vec2f{-10.2f, 15.2f}, core::maths::Vec2f{-25.2f, -35.3f} },
	                         std::pair{ core::maths::Vec2f{0.0f, 0.0f}, core::maths::Vec2f{0.0f, 0.0f} },
	                         std::pair{ core::maths::Vec2f{0.0f, 1.0f}, core::maths::Vec2f{0.0f, 1.0f} },
	                         std::pair{ core::maths::Vec2f{1.0f, 0.0f}, core::maths::Vec2f{1.0f, 0.0f} },
	                         std::pair{ core::maths::Vec2f{}, core::maths::Vec2f{} },
	                         std::pair{ core::maths::Vec2f{1.2f, 2.1f}, core::maths::Vec2f{} },
	                         std::pair{ core::maths::Vec2f{}, core::maths::Vec2f{1.2f, 2.1f} }
                         )
);
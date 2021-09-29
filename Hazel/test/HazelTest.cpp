#include "hzpch.h"
#include <gtest/gtest.h>

TEST(testMath, myCubeTest)
{
	EXPECT_EQ(1000, 5 * 200);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

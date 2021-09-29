#include "hzpch.h"
#include <gtest/gtest.h>

TEST(HazelTest, dummyTest)
{
	EXPECT_TRUE(TRUE);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

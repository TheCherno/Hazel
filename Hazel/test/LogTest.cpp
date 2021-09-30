#include "hzpch.h"
#include <gtest/gtest.h>

#include "Hazel/Core/Log.h"

TEST(LogTest, InitTest)
{
	ASSERT_EQ(Hazel::Log::GetCoreLogger(), nullptr);
	ASSERT_EQ(Hazel::Log::GetClientLogger(), nullptr);

	Hazel::Log::Init();

	EXPECT_NE(Hazel::Log::GetCoreLogger(), nullptr);
	EXPECT_NE(Hazel::Log::GetClientLogger(), nullptr);
}

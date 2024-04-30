#include <gtest/gtest.h>

#include <librge/rge.h>

TEST(LibraryTests, TestFoo)
{
	auto got = foo();
	auto want = 4;
	EXPECT_EQ(want, got);
}
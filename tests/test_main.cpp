#include <gtest/gtest.h>

#include <librge/rge.h>

TEST(LibraryTests, TestEngine)
{

	EXPECT_EQ(0, rgeInit(320, 200, "test"));

	while (!rgeIsWindowClosing())
	{
		rgeBeginFrame();

		rgeClearRenderer(255, 0, 0, 255);

		rgeEndFrame();
	}

	rgeExit();
}
#include <gtest/gtest.h>

#include <librge/rge.h>

TEST(LibraryTests, TestEngine)
{

	int ret = rgeInit(NULL,
			"test_org",
			"test_app",
			".zip",
			"media",
			320,
			200,
			"test");

	GTEST_ASSERT_EQ(0, ret);

	while (!rgeIsWindowClosing())
	{
		rgeBeginFrame();

		rgeClearRenderer(255, 0, 0, 255);

		rgeEndFrame();
	}

	rgeExit();
}
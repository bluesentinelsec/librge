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
			"test_librge");

	GTEST_ASSERT_EQ(0, ret);

	void* backgroundTexture = rgeLoadMediaImage("images/background320x200.png");
	GTEST_ASSERT_TRUE(backgroundTexture != nullptr);

	while (!rgeIsWindowClosing())
	{
		rgeBeginFrame();

		rgeClearRenderer(255, 0, 0, 255);

		rgeDrawTexture(backgroundTexture, 0, 0);

		rgeEndFrame();
		rgeFlipBackbuffer(320, 200);
	}

	rgeFreeMediaImage(backgroundTexture);
	rgeExit();
}
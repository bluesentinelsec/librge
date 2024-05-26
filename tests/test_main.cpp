#include <gtest/gtest.h>

#include <librge/rge.h>

TEST(LibraryTests, TestEngine)
{

	int displayWidth = 320;
	int displayHeight = 200;

	int ret = rgeInit(NULL,
			"test_org",
			"test_app",
			".zip",
			"media",
			displayWidth,
			displayHeight,
			"test_librge");

	GTEST_ASSERT_EQ(0, ret);

	void* backgroundTexture = rgeLoadMediaImage("images/background320x200.png");
	GTEST_ASSERT_TRUE(backgroundTexture != nullptr);

	void* frameBuffer = rgeCreateFrameBuffer(displayWidth, displayHeight);

	while (!rgeIsWindowClosing())
	{
		// draw all sprites to a frame buffer so we can scale to the display size
		rgeSetFrameBuffer(frameBuffer);
		rgeClearRenderer(255, 255, 255, 255);
		rgeDrawTexture(backgroundTexture, 0, 0);
		rgeEndFrameBuffer();

		// flip the frame buffer, scaled to the display while maintaining aspect ratio
		rgeScaleFrameBuffer(displayWidth, displayHeight);
		rgeBeginFrame();
		rgeClearRenderer(0, 0, 0, 255);
		rgeFlipFrameBuffer(frameBuffer);
		rgeEndFrame();
		rgeFlipBackbuffer(320, 200);
	}

	rgeFreeFrameBuffer(frameBuffer);
	rgeFreeMediaImage(backgroundTexture);
	rgeExit();
}
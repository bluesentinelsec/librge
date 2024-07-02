#include <gtest/gtest.h>

#include <librge/rge.h>

TEST(LibraryTests, TestEngine)
{

    int displayWidth = 320;
    int displayHeight = 200;

    int ret = rgeInit(NULL, "test_org", "test_app", ".zip", "media", displayWidth, displayHeight, "test_librge");

    GTEST_ASSERT_EQ(0, ret);

    void *backgroundTexture = rgeLoadMediaImage("images/backgrounds/scroll_test.png");
    GTEST_ASSERT_TRUE(backgroundTexture != nullptr);

    void *frameBuffer = rgeCreateFrameBuffer(displayWidth, displayHeight);
    void *camera2D = rgeCreateCamera2D(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

    while (!rgeIsWindowClosing())
    {
        // draw all sprites to a frame buffer so we can scale to the display size
        rgeSetFrameBuffer(frameBuffer);
        rgeClearRenderer(255, 255, 255, 255);

        // draw to camera
        rgeBeginMode2D(camera2D);
        rgeDrawTexture(backgroundTexture, 0, 0);
        rgeMoveCamera(camera2D, 600.0f, 100.0f);
        rgeEndMode2D();
        rgeEndFrameBuffer();

        // flip the frame buffer, scaled to the display while maintaining aspect ratio
        rgeScaleFrameBuffer(displayWidth, displayHeight);
        rgeBeginFrame();
        rgeClearRenderer(0, 0, 0, 255);
        rgeFlipFrameBuffer(frameBuffer);
        rgeEndFrame();
    }

    rgeFreeCamera2D(camera2D);
    rgeFreeFrameBuffer(frameBuffer);
    rgeFreeMediaImage(backgroundTexture);
    rgeExit();
}

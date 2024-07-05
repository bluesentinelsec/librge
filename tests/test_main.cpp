#include "librge/keycodes.h"
#include "librge/logger.h"
#include <gtest/gtest.h>

#include <librge/rge.h>

TEST(LibraryTests, TestEngine)
{

    int displayWidth = 320;
    int displayHeight = 200;
    int fps = 60;

    int ret = rgeInit(NULL, "test_org", "test_app", ".zip", "media", displayWidth, displayHeight, "test_librge", fps);
    GTEST_ASSERT_EQ(0, ret);

    void *backgroundTexture = rgeLoadMediaImage("images/backgrounds/scroll_test.png");
    GTEST_ASSERT_TRUE(backgroundTexture != nullptr);

    void *playerTexture = rgeLoadMediaImage("images/actors/player.png");
    GTEST_ASSERT_TRUE(playerTexture != nullptr);
    float playerX = 320;
    float playerY = 200;

    void *frameBuffer = rgeCreateFrameBuffer(displayWidth, displayHeight);

    float offsetX = displayWidth / 2.0f;
    float offsetY = displayHeight / 2.0f;
    void *camera2D = rgeCreateCamera2D(playerX + 16, playerY + 16, offsetX, offsetY, 0.0f, 1.0f);

    while (!rgeIsWindowClosing())
    {

        if (rgeIsKeyDown(rgeKEY_RIGHT))
        {
            playerX += 1 * 5;
        }
        if (rgeIsKeyDown(rgeKEY_LEFT))
        {
            playerX -= 1 * 5;
        }
        if (rgeIsKeyDown(rgeKEY_UP))
        {
            playerY -= 1 * 5;
        }
        if (rgeIsKeyDown(rgeKEY_DOWN))
        {
            playerY += 1 * 5;
        }

        // camera follows the player position
        rgeMoveCamera(camera2D, playerX + 16, playerY + 16);

        // draw all sprites to a frame buffer so we can scale to the display size
        rgeSetFrameBuffer(frameBuffer);
        rgeClearRenderer(255, 255, 255, 255);

        // draw to camera (within frame buffer)
        rgeBeginMode2D(camera2D);
        rgeDrawTexture(backgroundTexture, 0, 0);
        rgeDrawTexture(playerTexture, playerX, playerY);
        rgeEndMode2D();
        rgeEndFrameBuffer();

        // flip the frame buffer, scaled to the display while maintaining aspect ratio
        rgeScaleFrameBuffer(displayWidth, displayHeight);
        rgeBeginFrame();
        rgeClearRenderer(0, 0, 0, 255);
        rgeFlipFrameBuffer(frameBuffer);
        rgeEndFrame();
    }

    bool collided = rgeIsCollisionRect(0.0f, 0.0f, 16.0f, 16.0f, 0.0f, 0.0f, 16.0f, 16.0f);
    GTEST_ASSERT_TRUE(collided);

    rgeFreeCamera2D(camera2D);
    rgeFreeFrameBuffer(frameBuffer);
    rgeFreeMediaImage(backgroundTexture);
    rgeExit();
}

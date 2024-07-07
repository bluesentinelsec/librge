#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "keycodes.h"
#include "logger.h"
#include "music.h"
#include "sound.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

    int rgeInit(const char *argv0, const char *organization, const char *appName, const char *archiveExt,
                const char *mediaPath, int width, int height, const char *title, int fps);

    void rgeExit();
    bool rgeIsWindowClosing();
    void rgeBeginFrame();
    void rgeEndFrame();
    void rgeClearRenderer(int r, int g, int b, int a);
    float rgeGetDeltaTime();

    int rgeGetMediaFileSize(const char *path);
    int rgeReadMediaFile(const char *path, char *buffer, int size);
    int rgeReadMediaFileWAV(const char *path, unsigned char *buffer, int size);
    void rgeUpdateMusicStream(void *music);

    void *rgeLoadMediaImage(const char *fileName);
    void rgeFreeMediaImage(void *texture);

    void rgeDrawTexture(void *texture, int x, int y);
    void *rgeCreateFrameBuffer(int w, int h);
    void rgeFreeFrameBuffer(void *frameBuffer);
    void rgeSetFrameBuffer(void *frameBuffer);
    void rgeEndFrameBuffer();
    void rgeFlipFrameBuffer(void *frameBuffer);
    void rgeScaleFrameBuffer(int originalWidth, int originalHeight);

    void *rgeCreateCamera2D(float targetX, float targetY, float offsetX, float offsetY, float rotation, float zoom);
    void rgeFreeCamera2D(void *camera2D);
    void rgeBeginMode2D(void *camera2D);
    void rgeEndMode2D();
    void rgeMoveCamera(void *camera2D, float x, float y);

    bool rgeIsKeyPressed(int key);
    bool rgeIsKeyDown(int key);

    bool rgeIsCollisionRect(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);

#ifdef __cplusplus
}
#endif

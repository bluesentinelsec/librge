#include <librge/rge.h>

#include <physfs.h>
#include <raylib.h>

// variables used for scaling the framebuffer to display size
float scaledWidth;
float scaledHeight;
float paddingX;
float paddingY;

static int initVirtualFS(const char *argv0, const char *organization, const char *appName, const char *archiveExt,
                         const char *mediaPath);

static void initGameWindow(const int width, const int height, const char *title, int fps);

int rgeInit(const char *argv0, const char *organization, const char *appName, const char *archiveExt,
            const char *mediaPath, int width, int height, const char *title, int fps)
{
    rgeLogInfo("initializing game engine");

    rgeLogDebug("initializing virtual filesystem");
    int ret = initVirtualFS(argv0, organization, appName, archiveExt, mediaPath);
    if (ret != 0)
    {
        return 1;
    }

    rgeLogDebug("initializing game window");
    initGameWindow(width, height, title, fps);

    return 0;
}

void rgeExit()
{
    rgeLogInfo("closing game engine");

    rgeLogDebug("closing game window");
    CloseWindow();

    rgeLogDebug("closing virtual filesystem");
    int ret = PHYSFS_deinit();
    if (ret == 0)
    {
        rgeLogError("unable to close virtual file system: %s\n", PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
    }
}

bool rgeIsWindowClosing()
{
    return WindowShouldClose();
}

void rgeBeginFrame()
{
    BeginDrawing();
}

void rgeEndFrame()
{
    EndDrawing();
    EndTextureMode();
}

void rgeClearRenderer(int r, int g, int b, int a)
{
    Color color = {.r = (unsigned char)r, .g = (unsigned char)g, .b = (unsigned char)b, .a = (unsigned char)a};
    ClearBackground(color);
}

static void initGameWindow(const int width, const int height, const char *title, int fps)
{
    // mute raylib logs
    SetTraceLogLevel(LOG_NONE);

    InitWindow(width, height, title);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(fps);

// disable close on ESC on release builds
#ifdef NDEBUG
    SetExitKey(0);
#endif
}

static int initVirtualFS(const char *argv0, const char *organization, const char *appName, const char *archiveExt,
                         const char *mediaPath)
{
    int ret = PHYSFS_init(argv0);
    if (ret == 0)
    {
        rgeLogError("unable to initialize virtual file system: %s\n", PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
        return 1;
    }

    ret = PHYSFS_setSaneConfig(organization, appName, archiveExt, 0, 0);
    if (ret == 0)
    {
        rgeLogError("unable to set virtual file system config: %s\n", PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
        return 1;
    }

    rgeLogDebug("mounting media directory or archive: '%s'\n", mediaPath);
    ret = PHYSFS_mount(mediaPath, "/", 0);
    if (ret == 0)
    {
        rgeLogError("unable to mount media directory '%s': %s\n", mediaPath,
                    PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
        return 1;
    }
    return 0;
}

void rgeDrawTexture(void *texture, int x, int y)
{
    auto raylibTex = (Texture2D *)texture;
    DrawTexture(*raylibTex, x, y, WHITE);
}

void *rgeCreateFrameBuffer(int w, int h)
{
    RenderTexture2D *frameBuffer = (RenderTexture2D *)malloc(sizeof(RenderTexture2D));
    *frameBuffer = LoadRenderTexture(w, h);

    return (void *)frameBuffer;
}

void rgeFreeFrameBuffer(void *frameBuffer)
{
    RenderTexture2D *fb = (RenderTexture2D *)frameBuffer;
    UnloadRenderTexture(*fb);
    free(fb);
}

void rgeSetFrameBuffer(void *frameBuffer)
{
    RenderTexture2D *fb = (RenderTexture2D *)frameBuffer;
    BeginTextureMode(*fb);
}

void rgeEndFrameBuffer()
{
    EndTextureMode();
}

void rgeFlipFrameBuffer(void *frameBuffer)
{
    RenderTexture2D *fb = (RenderTexture2D *)frameBuffer;
    Rectangle sourceRec = {0.0f, 0.0f, (float)fb->texture.width, -(float)fb->texture.height};
    Rectangle destRec = {paddingX, paddingY, scaledWidth, scaledHeight};
    Vector2 origin = {0.0f, 0.0f};
    DrawTexturePro(fb->texture, sourceRec, destRec, origin, 0.0f, WHITE);
}

void rgeScaleFrameBuffer(int originalWidth, int originalHeight)
{
    int targetWidth;
    int targetHeight;
    float scaleFactor;
    float scaleFactorWidth;
    float scaleFactorHeight;

    if (IsWindowFullscreen())
    {
        targetWidth = GetRenderWidth();
        targetHeight = GetRenderHeight();
    }
    else
    {
        targetWidth = GetScreenWidth();
        targetHeight = GetScreenHeight();
    }

    // Calculate scale factor to maintain aspect ratio
    scaleFactorWidth = (float)targetWidth / originalWidth;
    scaleFactorHeight = (float)targetHeight / originalHeight;
    scaleFactor = scaleFactorWidth < scaleFactorHeight ? scaleFactorWidth : scaleFactorHeight;

    // Calculate scaled dimensions
    scaledWidth = originalWidth * scaleFactor;
    scaledHeight = originalHeight * scaleFactor;

    // Calculate padding to center the scaled image
    paddingX = (targetWidth - scaledWidth) / 2;
    paddingY = (targetHeight - scaledHeight) / 2;
}

float rgeGetDeltaTime()
{
    return GetFrameTime();
}

#include <librge/rge.h>

#include <physfs.h>
#include <raylib.h>

static RenderTexture2D backbuffer;

static int initVirtualFS(const char* argv0,
		const char* organization,
		const char* appName,
		const char* archiveExt,
		const char* mediaPath);

static void initGameWindow(const int width, const int height, const char* title);

int rgeInit(const char* argv0,
		const char* organization,
		const char* appName,
		const char* archiveExt,
		const char* mediaPath,
		const int width,
		const int height,
		const char* title
)
{
	rgeLogInfo("initializing game engine");

	rgeLogDebug("initializing virtual filesystem");
	int ret = initVirtualFS(argv0, organization, appName, archiveExt, mediaPath);
	if (ret != 0)
	{
		return 1;
	}

	rgeLogDebug("initializing game window");
	initGameWindow(width, height, title);

	return 0;
}

void rgeExit()
{
	rgeLogInfo("closing game engine");

	rgeLogDebug("closing backbuffer texture");
	UnloadRenderTexture(backbuffer);

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
	BeginTextureMode(backbuffer);
	BeginDrawing();
}

void rgeEndFrame()
{
	EndDrawing();
	EndTextureMode();
}

void rgeClearRenderer(int r, int g, int b, int a)
{
	Color color = { .r = (unsigned char)r, .g = (unsigned char)g, .b = (unsigned char)b, .a = (unsigned char)a };
	ClearBackground(color);
}

static void initGameWindow(const int width, const int height, const char* title)
{
	// mute raylib logs
	SetTraceLogLevel(LOG_NONE);

	InitWindow(width, height, title);
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	backbuffer = LoadRenderTexture(width, height);

// disable close on ESC on release builds
#ifdef NDEBUG
	SetExitKey(0);
#endif
}

static int initVirtualFS(const char* argv0,
		const char* organization,
		const char* appName,
		const char* archiveExt,
		const char* mediaPath)
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

void rgeDrawTexture(void* texture, int x, int y)
{
	auto raylibTex = (Texture2D*)texture;
	DrawTexture(*raylibTex, x, y, WHITE);
}

void rgeFlipBackbuffer(int w, int h)
{
	BeginDrawing();
	ClearBackground(WHITE);

	DrawTexturePro(backbuffer.texture,
			(Rectangle){ 0.0f, 0.0f, static_cast<float>(w), static_cast<float>(h) },
			(Rectangle){ 0.0f, 0.0f, static_cast<float>(w), static_cast<float>(h) },
			(Vector2){ static_cast<float>(w), static_cast<float>(h) },
			180.0f,
			WHITE);

	EndDrawing();
}
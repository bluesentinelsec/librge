#include <librge/rge.h>

#include <physfs.h>
#include <raylib.h>

int rgeInit(const char* argv0,
		const char* organization,
		const char* appName,
		const char* archiveExt,
		int width,
		int height,
		const char* title
)
{
	rgeLogInfo("initializing game engine");

	rgeLogDebug("initializing virtual filesystem");
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

	// mute raylib logs
	SetTraceLogLevel(LOG_NONE);

	InitWindow(width, height, title);
	SetWindowState(FLAG_WINDOW_RESIZABLE);

// disable close on ESC on release builds
#ifdef NDEBUG
	SetExitKey(0);
#endif

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
}

void rgeClearRenderer(int r, int g, int b, int a)
{
	Color color = { .r = (unsigned char)r, .g = (unsigned char)g, .b = (unsigned char)b, .a = (unsigned char)a };
	ClearBackground(color);
}
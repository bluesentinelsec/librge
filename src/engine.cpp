#include <librge/rge.h>

#include <physfs.h>
#include <raylib.h>

int rgeInit(int width, int height, const char* title)
{
	rgeLogInfo("initializing game engine");

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
	CloseWindow();
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
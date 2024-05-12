#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "logger.h"

#include <stdbool.h>
#include <assert.h>

int
rgeInit(const char* argv0,
		const char* organization,
		const char* appName,
		const char* archiveExt,
		const char* mediaPath,
		const int width,
		const int height,
		const char* title
);

void rgeExit();
bool rgeIsWindowClosing();
void rgeBeginFrame();
void rgeEndFrame();
void rgeClearRenderer(int r, int g, int b, int a);

int rgeGetMediaFileSize(const char* path);
int rgeReadMediaFile(const char* path, char* buffer, int size);

void* rgeLoadMediaImage(const char* fileName);
void rgeFreeMediaImage(void *texture);

void rgeDrawTexture(void *texture, int x, int y);

#ifdef __cplusplus
}
#endif
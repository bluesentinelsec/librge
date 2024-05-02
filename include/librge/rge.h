#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include "logger.h"

#include <stdbool.h>

int rgeInit(int width, int height, const char* title);
void rgeExit();
bool rgeIsWindowClosing();
void rgeBeginFrame();
void rgeEndFrame();
void rgeClearRenderer(int r, int g, int b, int a);

#ifdef __cplusplus
}
#endif
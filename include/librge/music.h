#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include <librge/rge.h>

    void *rgeNewMusic(const char *path, const char *fileType);
    void rgeFreeMusic(void *music);
    void rgePlayMusic(void *music);

#ifdef __cplusplus
}
#endif

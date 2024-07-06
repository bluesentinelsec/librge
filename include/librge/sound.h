#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include <librge/rge.h>

    void *rgeNewSound(const char *path, const char *fileType);
    void rgeFreeSound(void *sound);
    void rgePlaySound(void *sound);

#ifdef __cplusplus
}
#endif

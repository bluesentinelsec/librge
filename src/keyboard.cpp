#include "raylib.h"
#include <librge/rge.h>

bool rgeIsKeyPressed(int key)
{
    return IsKeyPressed(key);
}

bool rgeIsKeyDown(int key)
{
    return IsKeyDown(key);
}

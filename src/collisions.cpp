#include "raylib.h"
#include <librge/rge.h>

bool rgeIsCollisionRect(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2)
{
    Rectangle r1 = {.x = x1, .y = y1, .width = w1, .height = h1};
    Rectangle r2 = {.x = x2, .y = y2, .width = w2, .height = h2};
    return CheckCollisionRecs(r1, r2);
}

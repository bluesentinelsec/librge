#include <librge/rge.h>

#include <physfs.h>
#include <raylib.h>

void *rgeCreateCamera2D(float targetX, float targetY, float offsetX, float offsetY, float rotation, float zoom)
{
    Camera2D *camera = new Camera2D{0};
    camera->target = {targetX, targetY};
    camera->offset = {offsetX, offsetY};
    camera->rotation = rotation;
    camera->zoom = zoom;
    return camera;
}

void rgeFreeCamera2D(void *camera2D)
{
    Camera2D *camera = static_cast<Camera2D *>(camera2D);
    delete camera;
}

void rgeBeginMode2D(void *camera2D)
{
    Camera2D *camera = static_cast<Camera2D *>(camera2D);
    BeginMode2D(*camera);
}

void rgeEndMode2D()
{
    EndMode2D();
}

void rgeMoveCamera(void *camera2D, float x, float y)
{
    Camera2D *camera = static_cast<Camera2D *>(camera2D);
    camera->target = {x, y};
}

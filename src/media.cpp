#include <librge/rge.h>

#include <raylib.h>

void *rgeLoadMediaImage(const char *fileName)
{
    assert(fileName != NULL && fileName[0] != '\0');

    int dataSize = rgeGetMediaFileSize(fileName);
    assert(dataSize > 0);

    char *fileData = (char *)malloc(sizeof(char) * dataSize);
    int ret = rgeReadMediaFile(fileName, fileData, dataSize);
    assert(ret == 0);

    const char *fileExtension = GetFileExtension(fileName);

    Image img = LoadImageFromMemory(fileExtension, (const unsigned char *)fileData, dataSize);
    assert(img.data != NULL);

    auto *tex = new Texture2D(LoadTextureFromImage(img));
    SetTextureFilter(*tex, TEXTURE_FILTER_POINT);

    UnloadImage(img);
    free(fileData);

    return (void *)tex;
}

void rgeFreeMediaImage(void *texture)
{
    assert(texture != NULL);
    auto *tex = (Texture2D *)texture;
    UnloadTexture(*tex);
    tex = NULL;
    texture = NULL;
}

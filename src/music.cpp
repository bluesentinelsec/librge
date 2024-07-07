#include <librge/music.h>
#include <raylib.h>

void *rgeNewMusic(const char *path, const char *fileType)
{
    int dataSize = rgeGetMediaFileSize(path);
    assert(dataSize > 0);

    auto fileData = new unsigned char[dataSize];
    int ret = rgeReadMediaFileWAV(path, fileData, dataSize);
    assert(ret == 0);

    Music *wav = new Music(LoadMusicStreamFromMemory(fileType, fileData, dataSize));

    return static_cast<void *>(wav);
}

void rgeFreeMusic(void *music)
{
    auto mus = static_cast<Music *>(music);
    UnloadMusicStream(*mus);
    delete (mus);
};

void rgePlayMusic(void *music)
{
    auto mus = static_cast<Music *>(music);
    PlayMusicStream(*mus);
};

void rgeUpdateMusicStream(void *music)
{
    auto mus = static_cast<Music *>(music);
    UpdateMusicStream(*mus);
}
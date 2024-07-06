#include <librge/sound.h>

#include <raylib.h>

class rgeSound
{
public:
	rgeSound(const char* path, const char* fileType);

	~rgeSound();

	void rgePlaySound();

private:
	unsigned char* fileData;
	Wave wav;
	Sound sound;
};

rgeSound::rgeSound(const char* path, const char* fileType)
{

	int dataSize = rgeGetMediaFileSize(path);
	assert(dataSize > 0);

	fileData = new unsigned char[dataSize];
	int ret = rgeReadMediaFileWAV(path, fileData, dataSize);
	assert(ret == 0);

	wav = LoadWaveFromMemory(fileType, fileData, dataSize);
	sound = LoadSoundFromWave(wav);

}

rgeSound::~rgeSound()
{
	UnloadSound(sound);
	UnloadWave(wav);
	free(fileData);
	fileData = nullptr;
}

void rgeSound::rgePlaySound()
{
	PlaySound(sound);
}

void* rgeNewSound(const char* path, const char* fileType)
{
	auto* sound = new rgeSound(path, fileType);
	return static_cast<void*>(sound);
}

void rgeFreeSound(void* sound)
{
	auto* aSound = static_cast<rgeSound*>(sound);
	delete aSound;
}

void rgePlaySound(void* sound)
{
	auto* aSound = static_cast<rgeSound*>(sound);
	aSound->rgePlaySound();
}

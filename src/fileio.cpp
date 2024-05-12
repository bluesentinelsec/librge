#include <librge/rge.h>

#include <physfs.h>

int rgeGetMediaFileSize(const char* path)
{
	assert(path != NULL);
	rgeLogDebug("getting size from file: '%s'\n", path);

	PHYSFS_File* file = PHYSFS_openRead(path);
	if (!file)
	{
		rgeLogError("unable to open file: '%s' - %s\n", path, PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
		return -1;
	}

	PHYSFS_sint64 fileSize = PHYSFS_fileLength(file);

	PHYSFS_close(file);

	return fileSize;

}

int rgeReadMediaFile(const char* path, char* buffer, int size)
{
	assert(path != NULL);
	assert(buffer != NULL);
	assert(size > 0);

	rgeLogDebug("reading file: '%s'\n", path);
	PHYSFS_File* file = PHYSFS_openRead(path);
	if (!file)
	{
		rgeLogError("unable to open file: '%s' - %s\n", path, PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
		return 1;
	}

	PHYSFS_sint64 bytesRead = PHYSFS_readBytes(file, buffer, size);
	if (bytesRead != size)
	{
		rgeLogError("failed to read file: '%s' - %s\n", path, PHYSFS_getErrorByCode(PHYSFS_getLastErrorCode()));
		PHYSFS_close(file);
		return 1;
	}

	PHYSFS_close(file);
	return 0;
}
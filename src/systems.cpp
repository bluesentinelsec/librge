#include <librge/rge.h>

#include <physfs.h>
#include <raylib.h>


int foo()
{
	TraceLog(LOG_INFO, "this is a test");
	PHYSFS_init(nullptr);
	int a = 2 + 2;
	return a;
}
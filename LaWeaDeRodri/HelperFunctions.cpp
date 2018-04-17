#include "HelperFunctions.h"

HANDLE hnd = NULL;
HANDLE getConsoleHandle()
{
	return hnd ? hnd : hnd = GetStdHandle(STD_OUTPUT_HANDLE);
}

size_t getAccessor(size_t x, size_t y, size_t arrSize)
{
	return (arrSize * x) + y;
}

int randomRange(int min, int max)
{
	if (!(max - min)) return 0;
	return (rand() % (max - min)) + min;
}
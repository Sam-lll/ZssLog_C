#include "stdafx.h"

int main()
{
	char *buf = "string";
	unsigned char *str = (unsigned char *)"test";
	ZssLog(str);
// 	while(1)
// 	{
		zssLogINFO("<%s  %d> %s(buf: %s)", __FILE__, __LINE__, __FUNCTION__, buf);
		zssLogDEBUG("<%s  %d> %s(buf: %s)", __FILE__, __LINE__, __FUNCTION__, buf);
		zssLogERROR("<%s  %d> %s(buf: %s)", __FILE__, __LINE__, __FUNCTION__, buf);
		zssLogWARN("<%s  %d> %s(buf: %s)", __FILE__, __LINE__, __FUNCTION__, buf);
// 	}

	return 0;
}
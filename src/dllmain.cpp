#include "stdafx.h"



#ifndef zssLogINFO
#	define zssLogINFO	LogInfo
#endif

#ifndef zssLogERROR
#	define zssLogERROR	LogError
#endif

#ifndef zssLogWARN
#	define zssLogWARN	LogWarn
#endif

// #ifndef zssLogDEBUG
// #	ifdef _DEBUG
// #		define zssLogDEBUG				LogDebug
// #	else // _DEUBG
// #		if _MSC_VER <1300
// #			define zssLogDEBUG			((void)0)
// #		else
// #			define zssLogDEBUG          (__noop)
// #		endif
// #	endif
// #endif

int main()
{
	int a = 1;
	int b = 2;
	char *buf = "string";
	unsigned char *str = (unsigned char *)"test";
	ZssLog(str);
// 	while(1)
// 	{
		zssLogINFO("%d.%d_%s_OK", a, b, buf);
		/*zssLogDEBUG("%d.%d_%s_OK", a, b, buf);*/
		zssLogERROR("%d.%d_%s_OK", a, b, buf);
		zssLogWARN("%d.%d_%s_OK", a, b, buf);
		
// 		Sleep(3000);
// 	}

	return 0;
}
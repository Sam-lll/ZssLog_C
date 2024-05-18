#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdarg.h>
#ifdef WIN32
	#include <windows.h>
	#include <io.h>
	#include <direct.h>
#else
	#include <unistd.h>
	#include <sys/time.h>
#endif

//#include <dirent.h>

#include "Zss.ZssLog_C.h"
#include "Util.h"
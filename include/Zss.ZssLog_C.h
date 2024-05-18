#pragma once

#ifdef __cplusplus
extern "C" {
#endif


// dll exports interface, you must use /DZSSLOG_EXPORTS in makefile.
#ifdef ZSSLOG_EXPORTS
#define ZSSLOG_API __declspec(dllexport)
#else
#define ZSSLOG_API __declspec(dllimport)
#endif

enum EnumType{
	CX_LOG_MESSAGE = 0,
	CX_LOG_WARNING,
	CX_LOG_EXCEPTION,
	CX_LOG_ERROR,
	CX_LOG_DEBUG
};

#ifndef zssLogINFO
#	define zssLogINFO	LogInfo
#endif

#ifndef zssLogERROR
#	define zssLogERROR	LogError
#endif

#ifndef zssLogWARN
#	define zssLogWARN	LogWarn
#endif

#ifndef zssLogDEBUG
#	ifdef _DEBUG
#		define zssLogDEBUG				LogDebug
#	else // _DEUBG
#		if _MSC_VER <1300
#			define zssLogDEBUG			((void)0)
#		else
#			define zssLogDEBUG          (__noop)
#		endif
#	endif
#endif
//
//
//

#ifdef WIN32

ZSSLOG_API int 		Open(const char* log_base_dir, int enable_auto_delete, int auto_delete_keep_days);
ZSSLOG_API void 	Close();
ZSSLOG_API void 	LogInfo(const char* lpszFormat, ...);
ZSSLOG_API void 	LogError(const char* lpszFormat, ...);
ZSSLOG_API void 	LogWarn(const char* lpszFormat, ...);
ZSSLOG_API void 	LogDebug(const char* lpszFormat, ...);
ZSSLOG_API void 	LogException(const char* lpszFormat, ...);
ZSSLOG_API void 	ZssLog(unsigned char* pszSubName);
ZSSLOG_API void 	Logv(int type, const char* lpszFormat, va_list arg);
ZSSLOG_API void 	CheckChangeFile(/*const char* &st*/ int curr_stamp, int day_sec);
ZSSLOG_API void 	WriteRecord(const char *line);
ZSSLOG_API void 	CleanFiles();

#else

int 	Open(const char* log_base_dir, int enable_auto_delete, int auto_delete_keep_days);
void 	Close();
void 	LogInfo(const char* lpszFormat, ...);
void 	LogError(const char* lpszFormat, ...);
void 	LogWarn(const char* lpszFormat, ...);
void 	LogDebug(const char* lpszFormat, ...);
void 	LogException(const char* lpszFormat, ...);
void 	ZssLog(unsigned char* pszSubName);
void 	Logv(int type, const char* lpszFormat, va_list arg);
void 	CheckChangeFile(/*const char* &st*/ int curr_stamp, int day_sec);
void 	WriteRecord(const char *line);
void 	CleanFiles();

#endif

/* C-compatible headers here */

#ifdef __cplusplus
}
#endif
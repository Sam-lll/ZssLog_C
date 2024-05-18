#include "stdafx.h"

char g_logdir[260];
FILE *g_logfile;
int g_log_enable;
int g_logfile_stamp;
int g_auto_delete;
int g_auto_delete_keep_days;
FILE* g_fp; 

#ifdef WIN32
	void ZssLog(unsigned char* pszSubName)
#else
	void ZssLog(unsigned char* pszSubName)
#endif
{
	char tmp[260] = {0};
	char logdir[260] = {0};
	int auto_delete = 0;
	int keep_days = 0;
	g_log_enable = 0;

 	strcpy(tmp, "C:\\zsslog.ini");
	if (access(tmp, 0) != -1)
	{
		if(IniGetProfileInt(tmp, "ZssConfig", "EnableLog") != -1)
		{
			IniGetProfileStr(tmp, "ZssConfig", "LogDir_WinSNMPDll", logdir);
			sprintf(logdir, "%s\\%s", logdir, pszSubName);
			auto_delete = IniGetProfileInt(tmp, "ZssConfig", "EnableAutoDelete");
			keep_days = IniGetProfileInt(tmp, "ZssConfig", "AutoDeleteKeepDays") < 90 ? IniGetProfileInt(tmp, "ZssConfig", "AutoDeleteKeepDays") : 90;
			Open(logdir, auto_delete, keep_days);
		}
	}
}
#ifdef WIN32
	int Open(const char* log_base_dir, int enable_auto_delete, int auto_delete_keep_days)
#else
	int Open(const char* log_base_dir, int enable_auto_delete, int auto_delete_keep_days)
#endif
{
	char pszIt[260] = {0};
	int i = 0, n = 0;
	TIME stTime;
	char tmp[260] = {0};
	int day_sec;
	if(0 != strlen((char*)log_base_dir))
	{
		char szPath[260] = {0};
		char* pszName = strcpy(szPath, log_base_dir);
		AddBackslashEnd(pszName);
		strcpy(pszIt, pszName);
		for (i = 0; pszIt[i]; i++)
		{
			if(pszIt[i] == '\\' || pszIt[i] == '/')
			{
				pszIt[i] = '\0';
#ifdef WIN32
				if(_access(pszIt, 0) == -1)
#else
				if(access(pszIt, 0) == -1)
#endif
				{
					/*_get_errno(&n);*/
#ifdef WIN32
					if(_mkdir(pszIt) == -1)
#else
					if(mkdir(pszIt, 0755) == -1)
#endif
					{
						/*_get_errno(&n)*/;
					}
				}
					
						
				pszIt[i] = '\\'; 
			}
		}
		strcpy(g_logdir, log_base_dir);
	}
	g_auto_delete = enable_auto_delete;
	g_auto_delete_keep_days = auto_delete_keep_days;

	GetTime(&stTime);
	g_logfile_stamp = stTime.nYear * 10000 + stTime.nMonth * 100 + stTime.nDay;
	day_sec = stTime.nHour * 3600 + stTime.nMinute * 60 + stTime.nSecond;

	sprintf(tmp, "%s\\%04d%02d%02d.log", g_logdir, stTime.nYear, stTime.nMonth, stTime.nDay);

	g_fp = fopen(tmp, "a+");                                                                    ////////////////////////////////////////////////////////
	if(g_fp == NULL)
		return 0;

	g_log_enable = 1;

	return 1;
	
}
#ifdef WIN32
	void Close()
#else
	void Close()
#endif
{
	if (g_log_enable)
	{
		if (g_logfile != NULL)
			fclose(g_logfile);
		g_log_enable = 0;
	}
}
#ifdef WIN32
	void LogInfo(const char* lpszFormat, ...)
#else
	void LogInfo(const char* lpszFormat, ...)
#endif
{
	va_list arg;
	if (!g_log_enable)
		return;
	
	va_start(arg, lpszFormat);
	Logv(CX_LOG_MESSAGE, lpszFormat, arg);
	va_end(arg);
}
#ifdef WIN32
	void LogError(const char* lpszFormat, ...)
#else
	void LogError(const char* lpszFormat, ...)
#endif
{
	va_list arg;
	if (!g_log_enable)
		return;
	
	va_start(arg, lpszFormat);
	Logv(CX_LOG_ERROR, lpszFormat, arg);
	va_end(arg);
}
#ifdef WIN32
	void LogWarn(const char* lpszFormat, ...)
#else
	void LogWarn(const char* lpszFormat, ...)
#endif
{
	va_list arg;
	if (!g_log_enable)
		return;
	
	va_start(arg, lpszFormat);
	Logv(CX_LOG_WARNING, lpszFormat, arg);
	va_end(arg);
}
#ifdef WIN32
	void LogDebug(const char* lpszFormat, ...)
#else
	void LogDebug(const char* lpszFormat, ...)
#endif
{
	va_list arg;
	if (!g_log_enable)
		return;
	
	va_start(arg, lpszFormat);
	Logv(CX_LOG_DEBUG, lpszFormat, arg);
	va_end(arg);
}
#ifdef WIN32
	void LogException(const char* lpszFormat, ...)
#else
	void LogException(const char* lpszFormat, ...)
#endif
{
	va_list arg;
	if (!g_log_enable)
		return;
	
	va_start(arg, lpszFormat);
	Logv(CX_LOG_EXCEPTION, lpszFormat, arg);
	va_end(arg);
}
#ifdef WIN32
	void Logv(int type, const char* lpszFormat, va_list arg)
#else
	void Logv(int type, const char* lpszFormat, va_list arg)
#endif
{
	static const char* szType[] = {"Message", "Warning", "Exception", "Error  ", "Debug  "};
	int stamp;
	int day_sec;
	TIME st;
	char szBuffer[2048];
	char prefix[256]; 
	GetTime(&st);
	stamp = st.nYear * 10000 + st.nMonth * 100 + st.nDay;
	day_sec = st.nHour * 3600 + st.nMinute * 60 + st.nSecond;

	CheckChangeFile( stamp, day_sec);
 	if (g_fp == NULL)
 		return;
	// vsnprintf(szBuffer, strlen(szBuffer), lpszFormat, arg);	//	error format, strlen(szBuffer) maybe always 0.
	vsnprintf(szBuffer, sizeof(szBuffer), lpszFormat, arg);
	//ATL::CT2A sz(szBuffer);

	                 
	sprintf(prefix, "%04d-%02d-%02d %02d:%02d:%02d.%03d %s ():", 
		st.nYear, st.nMonth, st.nDay, st.nHour, st.nMinute, st.nSecond, st.nMilliseconds, 
		szType[type]);
	WriteRecord(prefix);
	WriteRecord(szBuffer);
	WriteRecord("\n");
	fflush(g_fp);
}
#ifdef WIN32
	void CheckChangeFile(/*TIME *st*/int curr_stamp, int day_sec)
#else
	void CheckChangeFile(/*TIME *st*/int curr_stamp, int day_sec)
#endif
{
	
	if (curr_stamp != g_logfile_stamp) 
	{
		TIME st;
		char tmp[260];
		fclose(g_fp);
		g_fp = NULL;
		GetTime(&st);
		g_logfile_stamp = curr_stamp;
		
		sprintf(tmp, "%s\\%04d%02d%02d.log", g_logdir, st.nYear, st.nMonth, st.nDay);
		g_fp = fopen(tmp, "a+");
// 		g_logfile = CreateFile(tmp, 
// 			GENERIC_READ | GENERIC_WRITE,
// 			FILE_SHARE_READ,
// 			NULL,
// 			OPEN_ALWAYS,
// 			FILE_ATTRIBUTE_NORMAL,
// 			NULL);
// 		if (g_logfile != INVALID_HANDLE_VALUE)
// 		{
// 			SetFilePointer(g_logfile, 0, NULL, FILE_END);
// 		}
		if (g_auto_delete)
		{
			CleanFiles();
		}
	}
}
#ifdef WIN32
	void WriteRecord(const char *line)
#else
	void WriteRecord(const char *line)
#endif
{
	int nWrite = 0;
	int len = line ? strlen(line) : 0;
	if (len)
	{
		unsigned long ulWritten = 0;
		//WriteFile(g_logfile, line, len, &ulWritten, NULL);
		nWrite = fwrite(line, len, 1, g_fp);
	}
}

static int rdn(int y, int m, int d) 
{
	if (m < 3)
		y--, m += 12;
	return 365*y + y/4 - y/100 + y/400 + (153*m - 457)/5 + d - 306;
}

static int get_date_distance(int y1, int m1, int d1, int y2, int m2, int d2)
{
	return rdn(y1,m1,d1) - rdn(y2,m2,d2);
}
#ifdef WIN32
	void CleanFiles()
#else
	void CleanFiles()
#endif
{
	long	hFind;
	char	TempPath[260] = {0};
	int		i = 0;
	char	time[64] = {0};
	int year, month, day;
	sprintf(TempPath, "%s\\*.log", g_logdir);

	for(i = 0; i < 100; i++)
	{
		SubTime(i, time);
		
		
		if (sscanf(time, "%04d%02d%02d", &year, &month, &day) == 3) 
		{
			int curr_year = g_logfile_stamp / 10000;
			int curr_month = (g_logfile_stamp /100) % 100;
			int curr_day = g_logfile_stamp % 100;
			if (get_date_distance(curr_year, curr_month, curr_day, year, month, day) > g_auto_delete_keep_days)
			{
				char szFile[260];
				strcpy(szFile, g_logdir);
				strcat(szFile, "\\");
				strcat(szFile, time);
				strcat(szFile, ".log");
				remove(szFile);
			}
		}
		
	}
	
}

#include <windows.h>
#include <stdio.h>
#include <time.h>

#include "LOG_MGR.h"


LogMgr::LogMgr( void ) : m_day( 0 ), m_logType( LOG_FILE )
{

}

LogMgr::~LogMgr( void )
{

}

void	LogMgr::initLogMgr( LOG_TYPE logType )
{
	m_logType	= logType;

	if( m_logType & LOG_CONSOLE )
	{
		if( AllocConsole() )
		{		  
			FILE	*fp = NULL;
			AttachConsole(GetCurrentProcessId());
			freopen_s( &fp, "CON","w",stdout);
		}
	}

	 if( m_logType & LOG_FILE )
	 {					  
		 CreateDirectory( TEXT("log"), NULL );

		 time_t			nowTime			= time(NULL);
		 struct	tm		tdata			= {0};

		 localtime_s( &tdata, &nowTime );

		 if( tdata.tm_mday != m_day )
		 {
			 m_day = tdata.tm_mday;

			 sprintf_s( m_logfileName, 21, "log\\%02d��%02d��%02d��.log",
				 tdata.tm_year % 100, tdata.tm_mon+1, tdata.tm_mday);
		 }
	 }
}


void LogMgr::AddLog( const char* logMsg, const char* srcFile, unsigned int lineNum, ... )
{
	char			*LogStr			= NULL;  
	time_t			nowTime			= time(NULL); 
	struct	tm		tdata			= {0};
	

	localtime_s( &tdata, &nowTime );

	//:: �����̸� üũ
	if( m_logType & LOG_FILE)
	{
		if( tdata.tm_mday != m_day )
		{
			m_day = tdata.tm_mday;

			sprintf_s( m_logfileName, 21, "log\\%02d��%02d��%02d��.log",
					   tdata.tm_year % 100, tdata.tm_mon+1, tdata.tm_mday);
		}
	}

	//:: �α׸޼��� ���� ����
	if( logMsg != NULL )
	{	
		size_t strSize = strlen(logMsg) + strlen(srcFile) + 100;
		LogStr		   = new char[ strSize ];

		if( LogStr != NULL )
		{
			sprintf_s( LogStr, strSize, "�ð� : %02d��%02d��%02d��\n���� : %s\n��ġ : %s %d\n",
					 tdata.tm_hour, tdata.tm_min, tdata.tm_sec, logMsg, srcFile, lineNum );

			if( m_logType & LOG_CONSOLE )
			{			
				va_list list;
				va_start( list, lineNum );
				printLog( LogStr, list  );
			}

			if( m_logType & LOG_FILE )
			{
				va_list list;
				va_start( list, lineNum );
				fileLog( LogStr, list );
			}

			delete [] LogStr;
		}
	}
}

//:: �ֿܼ� ���
void LogMgr::printLog( const char* logMsg, va_list list )
{
	char Log[1024];
    vsprintf(Log,logMsg,list);
	printf("%s", Log);
}

//:: ���Ͽ� ���
void LogMgr::fileLog( const char* logMsg, va_list list )
{							 
	char Log[1024];
	FILE* logFp;
	fopen_s( &logFp, m_logfileName, "a+" );
	if( logFp != NULL )
	{
		vsprintf(Log,logMsg,list);
		fprintf_s( logFp, "%s\n", Log );
		fclose( logFp );
	}
}

LogMgr*   GetLogInstance( void ) { static LogMgr mgr; return &mgr; }


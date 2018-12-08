#ifndef _LOGMGR_H_
#define _LOGMGR_H_


//:: 로그 타입
typedef enum tag_logtype { LOG_CONSOLE = 1, LOG_FILE, LOG_CONSOLE_FILE, LOG_ALL }LOG_TYPE;

class LogMgr
{
	//:: 싱글턴으로 사용.
	friend	__declspec( dllexport ) LogMgr*	 GetLogInstance( void );
private:
	//:: 생성자
	LogMgr( void );
	//:: 소멸자
	~LogMgr( void );

public:
	//:: 로그 초기화
	void initLogMgr( LOG_TYPE logType );
	//:: 로그 찍기 ( 디버그 모드 )
	void AddLog( const char* logMsg, const char* srcFile, unsigned int lineNum,... );

private:
	//:: 파일 찍기
	void fileLog( const char* logMsg, va_list list );
	//:: 콘솔찍기
	void printLog( const char* logMsg, va_list list );

private:
	//:: 로그 타입
	LOG_TYPE	m_logType;
	//:: 로그 파일  ( 오늘 날짜 )
	char		m_logfileName[21];
	//:: 파일 이름 변경 확인
	int			m_day;
};

//:: 로그매니저 인스턴스 얻기
LogMgr*   GetLogInstance( void );



//:: 매니저 초기화
	#define INIT_LOG( LOGTYPE )	   { GetLogInstance()->initLogMgr( LOGTYPE ); }
//:: 로그 찍기
#ifdef _DEBUG
	#define ADD_LOG( STR, ... )	   { GetLogInstance()->AddLog( STR, __FILE__, __LINE__, __VA_ARGS__ ); }
#elif _UNITY_DEBUG
	#define ADD_LOG( STR, ... )	   { GetLogInstance()->AddLog( STR, __FILE__, __LINE__, __VA_ARGS__ ); }
#endif

#endif




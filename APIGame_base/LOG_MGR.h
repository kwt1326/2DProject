#ifndef _LOGMGR_H_
#define _LOGMGR_H_


//:: �α� Ÿ��
typedef enum tag_logtype { LOG_CONSOLE = 1, LOG_FILE, LOG_CONSOLE_FILE, LOG_ALL }LOG_TYPE;

class LogMgr
{
	//:: �̱������� ���.
	friend	__declspec( dllexport ) LogMgr*	 GetLogInstance( void );
private:
	//:: ������
	LogMgr( void );
	//:: �Ҹ���
	~LogMgr( void );

public:
	//:: �α� �ʱ�ȭ
	void initLogMgr( LOG_TYPE logType );
	//:: �α� ��� ( ����� ��� )
	void AddLog( const char* logMsg, const char* srcFile, unsigned int lineNum,... );

private:
	//:: ���� ���
	void fileLog( const char* logMsg, va_list list );
	//:: �ܼ����
	void printLog( const char* logMsg, va_list list );

private:
	//:: �α� Ÿ��
	LOG_TYPE	m_logType;
	//:: �α� ����  ( ���� ��¥ )
	char		m_logfileName[21];
	//:: ���� �̸� ���� Ȯ��
	int			m_day;
};

//:: �α׸Ŵ��� �ν��Ͻ� ���
LogMgr*   GetLogInstance( void );



//:: �Ŵ��� �ʱ�ȭ
	#define INIT_LOG( LOGTYPE )	   { GetLogInstance()->initLogMgr( LOGTYPE ); }
//:: �α� ���
#ifdef _DEBUG
	#define ADD_LOG( STR, ... )	   { GetLogInstance()->AddLog( STR, __FILE__, __LINE__, __VA_ARGS__ ); }
#elif _UNITY_DEBUG
	#define ADD_LOG( STR, ... )	   { GetLogInstance()->AddLog( STR, __FILE__, __LINE__, __VA_ARGS__ ); }
#endif

#endif




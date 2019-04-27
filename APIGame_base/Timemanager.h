#ifndef  _TIMEMANAGER_H_
#define  _TIMEMANAGER_H_
#include <Windows.h>
#include <time.h>

#define TIME_MGR Timemanager::GetInstance()

class Timemanager
{

private:
	static Timemanager* minstance;

public:
	static Timemanager* GetInstance()
	{
		if (minstance == NULL) minstance = new Timemanager;
		return minstance;
	}

private:
	Timemanager();
	Timemanager(const Timemanager& val);
	~Timemanager();

private:
	Timemanager& operator=(const Timemanager& val);

public:
	void Update();
	float GetFPS();
	float GetWorldTime() { return mWorldtime; }
	float GetDeltaTime() { return mDeltatime; }

	void BeginStopWatch();
	float StopStopWatch(bool binit = true);

private:
	//TimeGetTime();  ->멀티미디어 타이머 사용
	//GetTickCount(); ->시스템 타이머 사용
	//QueryPerformanceCounter(); -> high Precision 이벤트 타이머 정확도가 가장 높음
	BOOL mHardwareAble;		  // 하드웨어 지원여부
	LARGE_INTEGER mFrequency; // 하드웨어 지원하는 정밀도
	LARGE_INTEGER mCheckTime; // 시간측정용 변수
	LONGLONG mBeginTime;	  // 이전 프레임 시간
	LONGLONG mEndTime;		  // 현재 프레임 시간
	float mWorldtime;		  // 프로그램 시작이후 경과시간
	float mDeltatime;		  // 지난 갱신으로부터 현재 갱신까지 경과된 시간

	clock_t mStopWatchTime;   // 스톱워치 기능을 위한 저장시간 ( 초 )
};

#endif // ! _TIMEMANAGER_H_

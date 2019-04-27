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
	//TimeGetTime();  ->��Ƽ�̵�� Ÿ�̸� ���
	//GetTickCount(); ->�ý��� Ÿ�̸� ���
	//QueryPerformanceCounter(); -> high Precision �̺�Ʈ Ÿ�̸� ��Ȯ���� ���� ����
	BOOL mHardwareAble;		  // �ϵ���� ��������
	LARGE_INTEGER mFrequency; // �ϵ���� �����ϴ� ���е�
	LARGE_INTEGER mCheckTime; // �ð������� ����
	LONGLONG mBeginTime;	  // ���� ������ �ð�
	LONGLONG mEndTime;		  // ���� ������ �ð�
	float mWorldtime;		  // ���α׷� �������� ����ð�
	float mDeltatime;		  // ���� �������κ��� ���� ���ű��� ����� �ð�

	clock_t mStopWatchTime;   // �����ġ ����� ���� ����ð� ( �� )
};

#endif // ! _TIMEMANAGER_H_

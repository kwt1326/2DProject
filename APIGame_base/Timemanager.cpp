#include "Timemanager.h"

Timemanager* Timemanager::minstance;

Timemanager::Timemanager()
{
	// 하드웨어 지원여부 확인 및 하드웨어 정밀도 확인
	mHardwareAble = QueryPerformanceFrequency(&mFrequency);
	// 시작값 초기화
	mDeltatime = mWorldtime = 0.f;

	// 최초시작시간 설정
	if (mHardwareAble == TRUE)
	{
		QueryPerformanceCounter(&mCheckTime);
		mBeginTime = mCheckTime.QuadPart;
	}
	else
	{
		mBeginTime = GetTickCount();
	}
}
	
Timemanager::~Timemanager()
{

}

void Timemanager::Update()
{
	if (mHardwareAble == TRUE)
	{
		QueryPerformanceCounter(&mCheckTime);
		mEndTime = mCheckTime.QuadPart;
	}

	else
	{
		mEndTime = GetTickCount(); 
	}

	// 델타 타임 계산
	mDeltatime = (float)(mEndTime - mBeginTime) / 
	((mHardwareAble == TRUE) ? mFrequency.QuadPart : 1000); // 1초(1000) 단위로 바꿔준다.

	if (mDeltatime >= 1.f / 60.f/*FPS*/)
	{
		mBeginTime = mEndTime;
	}
	else
	{
		Sleep(0.016f *1000 /*mDeltatime - 1.f / 60.f*/); // 60FPS 고정
	}

	if (mDeltatime > 0.1f) mDeltatime = 0.1f;
	// 월드 타임 계산 (누적하면 나옴)
	mWorldtime += mDeltatime;

	mBeginTime = mEndTime;
}

float Timemanager::GetFPS()
{
	static int Frames = 0;
	static float FPS = 0.0f;
	static float UpdateTime = 0.f;

	Frames++;
	UpdateTime += mDeltatime;

	if (UpdateTime >= 0.5f)
	{
		FPS = Frames / UpdateTime;
		UpdateTime = 0.f;
		Frames = 0.f;
	}

	return FPS;
}
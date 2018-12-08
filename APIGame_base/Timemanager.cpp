#include "Timemanager.h"

Timemanager* Timemanager::minstance;

Timemanager::Timemanager()
{
	// �ϵ���� �������� Ȯ�� �� �ϵ���� ���е� Ȯ��
	mHardwareAble = QueryPerformanceFrequency(&mFrequency);
	// ���۰� �ʱ�ȭ
	mDeltatime = mWorldtime = 0.f;

	// ���ʽ��۽ð� ����
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

	// ��Ÿ Ÿ�� ���
	mDeltatime = (float)(mEndTime - mBeginTime) / 
	((mHardwareAble == TRUE) ? mFrequency.QuadPart : 1000); // 1��(1000) ������ �ٲ��ش�.

	if (mDeltatime >= 1.f / 60.f/*FPS*/)
	{
		mBeginTime = mEndTime;
	}
	else
	{
		Sleep(0.016f *1000 /*mDeltatime - 1.f / 60.f*/); // 60FPS ����
	}

	if (mDeltatime > 0.1f) mDeltatime = 0.1f;
	// ���� Ÿ�� ��� (�����ϸ� ����)
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
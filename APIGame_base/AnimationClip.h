#ifndef _ANIMATIONCLIP_H_
#define _ANIMATIONCLIP_H_

class GameObject;
class Renderer;
class image;

class AnimationClip
{
public:
	AnimationClip(GameObject* obj);
	~AnimationClip();

public:
	void Init(image* image, float Time, int Framecnt, int Directioncnt, bool loop, bool HasExittime, bool bReverse = false);
	void Update(float dt);

public:
	void Play();
	void Stop();

	// �ִϸ��̼� ���� ����
	void SetAnimationTime(float Time) { m_AnimationTime = Time; }
	void SetLoop(bool loop) { m_Loop = loop; }
	void SetHasExitTime(bool ExitTime) { m_HasExitTime = ExitTime; }
	void SetFrameCnt(int cnt);
	void SetDirectionCnt(int cnt);
	void SetDirection(float angle);
	void SetName(std::string strName) { m_strName = strName; }

	// �ִϸ��̼� ���� ���
	float GetProgress() { return m_Progress; }
	int GetFrameCnt() { return m_FrameCnt; }
	int GetDirectionCnt() { return m_DirectionCnt; }
	bool IsLoop() { return m_Loop; }
	bool IsPlay() { return m_IsPlay; }
	void SetImage(image* image);
	image* GetImage() { return m_image; }
	int Getloopcnt() { return m_LoopCnt; }
	bool GetHasExitTime() { return m_HasExitTime; }
	std::string GetName() { return m_strName; }

private:
	bool		m_bReverse;

	int			m_LoopCnt;
	int			m_nextcnt;

	float		m_AnimationTime; // �ִϸ��̼��� �� ���� ¥������
	float		m_Progress;		 // �ִϸ��̼� �����
	int			m_DirectionCnt;  // �� ����¥�� �ִϸ��̼� ����
	int			m_FrameCnt;		 // �� ��¥�� �ִϸ��̼� ����
	int			m_NowDirection;	 // ���� ����

	bool		m_Loop;			 // ��������� �����Ѱ�
	bool		m_IsPlay;		 // ������ΰ�
	bool		m_HasExitTime;	 // �ִϸ��̼� Stop �ÿ� �������� �Ϸ�ɶ� ���� ����� ����

	int			m_ImageWidth;
	int			m_ImageHeight;
	int			m_SizeX;
	int			m_SizeY;

	std::string m_strName;
	
	image*		m_image;
	GameObject* m_GameObject; // ���� �ִϸ��̼� ������Ʈ�� �����ϰ� �ִ� ���ӿ�����Ʈ
	Renderer*	m_Renderer;	  // ������ ���� �ʿ�1

};

#endif // !_ANIMATIONCLIP_H_

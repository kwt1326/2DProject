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

	// 애니메이션 정보 설정
	void SetAnimationTime(float Time) { m_AnimationTime = Time; }
	void SetLoop(bool loop) { m_Loop = loop; }
	void SetHasExitTime(bool ExitTime) { m_HasExitTime = ExitTime; }
	void SetFrameCnt(int cnt);
	void SetDirectionCnt(int cnt);
	void SetDirection(float angle);
	void SetName(std::string strName) { m_strName = strName; }

	// 애니메이션 정보 얻기
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

	float		m_AnimationTime; // 애니메이션이 총 몇초 짜리인지
	float		m_Progress;		 // 애니메이션 진행률
	int			m_DirectionCnt;  // 몇 방향짜리 애니메이션 인지
	int			m_FrameCnt;		 // 몇 장짜리 애니메이션 인지
	int			m_NowDirection;	 // 현재 방향

	bool		m_Loop;			 // 루프재생이 가능한가
	bool		m_IsPlay;		 // 재생중인가
	bool		m_HasExitTime;	 // 애니메이션 Stop 시에 프레임이 완료될때 까지 재생할 건지

	int			m_ImageWidth;
	int			m_ImageHeight;
	int			m_SizeX;
	int			m_SizeY;

	std::string m_strName;
	
	image*		m_image;
	GameObject* m_GameObject; // 현재 애니메이션 컴포넌트를 소유하고 있는 게임오브젝트
	Renderer*	m_Renderer;	  // 렌더러 정보 필요1

};

#endif // !_ANIMATIONCLIP_H_

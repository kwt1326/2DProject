#ifndef _IMAGESCENE_H_
#define _IMAGESCENE_H_

#include "Scene.h"
#include "Vector2.h"
class image;

class imageScene : public Scene
{
public:
	imageScene();
	virtual ~imageScene();

public:
	virtual void Update(float dt);
	virtual void Render(HDC hdc);
	virtual void Init();
	virtual void Release();
	virtual LRESULT SceneProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

private:
	
	Vector2 m_playerPosition;
	Vector2 m_Direction;
	Vector2 m_Dest;
	float m_Playerspeed;

	// idle 애니메이션
	image* m_playerimage;
	int m_framecnt;
	int m_directioncnt;
	int m_Framewidth;
	int m_Frameheight;
	
	// walk 애니메이션
	image* m_playerwalkimage;
	int m_walkframecnt;
	//int m_walkdirectioncnt; 위에 걸로 씀
	int m_walkFramewidth;
	int m_walkFrameheight;
	
	// 맵이미지
	image* m_map;
	Vector2 m_scroll;

	float m_frameProgress;
	float m_directionangle;
	
	float m_iswalk;
	bool m_walk;
	bool m_LR;
};

#endif
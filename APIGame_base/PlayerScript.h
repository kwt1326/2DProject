#ifndef  _PLAYERSCRIPT_H_
#define  _PLAYERSCRIPT_H_

#include <assert.h>
#include <vector>
#include <list>
#include "Component.h"
#include "Vector2.h"
#include "AnimationClipManager.h"
#include "Enumdefinition.h"
#include "PlayerObject.h"

class PlayerObject;
class AnimationClip;
class Animation;
class Collider;
class Camera2D;
class Rigidbody;
class FSMMarcine;
class TState;
class PlayerScript : public Component
{
public:
	PlayerScript();
	virtual ~PlayerScript();
public:
	virtual void Update(float dt);
	virtual void Init();
	virtual void Release();
private:
	float			p_PlayerSpeed;
	float			m_maxspeed;
	float		    p_PlayerDir;
	float			m_dt_time;
	float			m_Cooltime;
	const float		m_flystarttime = 0.1f; // 처음 땅을 박차고 점프하는 시간
	BOOL			m_wparam[255]; // 동시 키 입력 위함
	TState*		m_playerstate;

	bool GameStart(PlayerObject* player);

public:
	PlayerObject * m_pPlayer;
	FSMMarcine * m_pMachine;
	Camera2D*	m_pRelationCamera;
	Rigidbody*  m_pRigidbody;
	Animation * p_Anim;
	bool		m_ChangeDirection;
	bool		m_isjump;
	bool		m_gamestart;
	bool		m_bStartCharge;
public:
	void ProcessPlayer(float dt);
	void Move(float dt);
	void ReplaceHealth(int nValue);
	void ChangePlayerAnimState(std::string state);
	void SetComparePosition(Vector2 vPos, Vector2 vWorldPos);
	void InputKeycode(int input, BOOL istrue) { m_wparam[input] = istrue; }
	BOOL GetInput(int input) { return m_wparam[input]; }

	void DrawHealthBar();
	void ChangeShotAnimByState(int enumChargeState);
	void UpdateShot();

	bool IsScrolling(bool bX);

};

#endif // ! _PLAYERSCRIPT_H_

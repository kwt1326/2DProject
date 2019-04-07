#ifndef _PLAYEROBJECT_H_
#define _PLAYEROBJECT_H_

#include <mutex>
#include "Gamemanager.h"
#include "GameObject.h"
#include "Vector2.h"
#include "Rigidbody.h"
#include "Enumdefinition.h"
#include "Transform.h"
#include "ColliderPixel.h"
#include "AnimationClipManager.h"

#define PLAYER_INSTANCE PlayerObject::GetInstance()
#define PLAYER_H_HALFSIZE 20
#define PLAYER_V_HALFSIZE 50

class PlayerShotPos : public GameObject
{
public:
	PlayerShotPos() {};
	virtual ~PlayerShotPos() {};

	virtual void Init();
	virtual void Update();
	virtual void Release();
public:
	void ShotPosChangeofDir(bool dir) 
	{
		if (dir) GetComponent<Transform>()->SetlocalPosition(Vector2(17.0f, -20.0f));
		else GetComponent<Transform>()->SetlocalPosition(Vector2(-27.0f, -20.0f));
	}
};

class PlayerObject : public GameObject
{
private:
	static std::unique_ptr<PlayerObject> m_instance;
	static std::once_flag _flag;

public:
	PlayerObject();
	virtual ~PlayerObject();

	PlayerObject(const PlayerObject &) = delete;
	PlayerObject &operator=(const PlayerObject &) = delete;

	static PlayerObject* GetInstance()
	{
		std::call_once(_flag,
			[]() { m_instance.reset(new PlayerObject); });
		return m_instance.get();
	}

public:
	virtual void Init();
	virtual void Update();
	virtual void Release();

	void SetChargeTime(clock_t ftime) { m_fChargeTime = ftime; }
	clock_t GetChargeTime() { return m_fChargeTime; }
	UINT GetHealth() { return m_nHealth; }
	void SetHealth(UINT nHealth) { m_nHealth = nHealth; }
	float GetPlayerSpeed() { return m_PlayerSpeed; }
	void SetPlayerSpeed(float speed) { m_PlayerSpeed = speed; }
	float GetDashSpeed() { return m_PlayerDashSpeed; }
	void SetDashSpeed(float speed) { m_PlayerDashSpeed = speed; }
	float GetMaxSpeed() { return m_Maxspeed; }
	void SetMaxSpeed(float speed) { m_Maxspeed = speed; }
	void SetBlockState(Block state) { m_blockstate = state; }
	Block GetBlockState() { return m_blockstate; }
	void SetGamestart(bool bstart) { mb_gamestart = bstart; }
	bool GetGamestart() { return mb_gamestart; }
	void SetMove(bool bmove) { mb_move = bmove; }
	bool GetMove() { return mb_move; }
	void SetPosition(Vector2 pos) {	GetComponent<Transform>()->SetPosition(pos); }
	Vector2 GetPosition() { return GetComponent<Transform>()->GetPosition(); }

	void SetWorldPosition(Vector2 pos) { m_worldposition = pos; }
	Vector2 GetWorldPosition() { return m_worldposition; }
	Rect GetWorldRect() {
		Rect rt(m_worldposition.x - PLAYER_H_HALFSIZE,
			m_worldposition.y - PLAYER_V_HALFSIZE,
			m_worldposition.x + PLAYER_H_HALFSIZE,
			m_worldposition.y + PLAYER_V_HALFSIZE); 
		return rt;
	}
	Rect GetLocalRect() {
		Vector2 pos = GetPosition();
		Rect rt(pos.x - PLAYER_H_HALFSIZE,
				pos.y - PLAYER_V_HALFSIZE,
				pos.x + PLAYER_H_HALFSIZE,
				pos.y + PLAYER_V_HALFSIZE);
		return rt;
	}

	bool GetDirection() { return mb_dir; }
	void SetDirection(bool dir) { mb_dir = dir; }
	void SetScrollUse(bool buse) { mb_scrolluse = buse; }
	bool GetScrollUse() { return mb_scrolluse; }

	bool GetJump() { return mb_isjump; }
	void SetJump(bool bjump) { mb_isjump = bjump; }

	PlayerShotPos* GetShotpos() { return m_shotpos; }
	Vector2 GetShotLoc() { return m_shotpos->GetComponent<Transform>()->GetPosition(); }

	AnimationClip* GetClip(std::string strclip) { 
		if (m_playerClips.find(strclip) != m_playerClips.end()) { return m_playerClips.find(strclip)->second; } else return nullptr; 
	};

private:
	Vector2 m_worldposition;
	float m_PlayerSpeed;
	float m_PlayerDashSpeed;
	float m_Maxspeed;
	clock_t m_fChargeTime;
	Block m_blockstate;
	bool  mb_gamestart;
	bool  mb_move;
	bool  mb_scrolluse;
	bool  mb_dir;
	bool  mb_isjump;
	UINT  m_nHealth;

	PlayerShotPos* m_shotpos;
	ObjectCamp m_type;

	std::map<std::string, AnimationClip*> m_playerClips;
public:
	float m_movedist;
};

#endif // !_PLAYEROBJECT_H_

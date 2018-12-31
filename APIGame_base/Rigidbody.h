#ifndef _RIGIDBODY_H_
#define _RIGIDBODY_H_

#include "Component.h"
#include "Vector2.h"
#include "Physic.h"
#include "ColliderPixel.h"
#include "Enumdefinition.h"
#include "GameObject.h"
#include <list>

struct ColliderInfo;
class ColliderManager;
typedef struct CollisionStay
{
	bool  mb_stay;
	unsigned int m_staypoint;
	Vector2 m_coord;
	bool  m_bOnMap;
	bool  m_bOnHWall;
}STAY;
class PlayerObject;
class Rigidbody : public Component
{
public:
	Rigidbody();
	~Rigidbody();
public:
	void Init();
	void Update(float dt);
	void Release();
public:
	// Player Check
	bool OnRectColliderEnter_PLAYER(PlayerObject* player);
	bool OnRectColliderEnter_Check_PLAYER(PlayerObject* player, Rect& playercol, ColliderInfo& mapinfo);
	bool OnDiagonelColliderEnter_Check_PLAYER(PlayerObject* player, ColliderInfo& mapCol);
	bool OnStairColliderEnter_Check_PLAYER(PlayerObject* player, Rect& playercol, Rect& mapcol);

	bool HitColliderOnMap(const Rect playercol, const Rect Mapcol);
	int HitColliderToHorizon(const Rect playercol, const Rect Mapcol);

	bool OnPixleCollisionEdgePoint(POINT& pt, ColliderPixel* pColPixel, PIXEL colorrgb = { 255,0,255 });
	bool OnPixleCollisionPoint(POINT& pt, ColliderPixel* pColPixel, PIXEL colorrgb = { 255,0,255 });
	bool OnPixleCollisionEnter(Vector2* vArr, ColliderPixel* pColPixel, PIXEL colorrgb = { 255,0,255 });
	bool OnPixleCollisionEnter(Rect& rt,  ColliderPixel* pColPixel, PIXEL colorrgb = { 255,0,255 });
	bool OnPixleCollisionStay(Rect& rt, ColliderPixel* pColPixel, PIXEL colorrgb = { 255,0,255 });

	// player only
	bool OnPixleCollisionLanding(PlayerObject* pObject, ColliderPixel* pColPixel, PIXEL colorrgb = { 255,0,255 });
	bool OnPixleCollisionHorizon(PlayerObject* pObject, bool bdirection, ColliderPixel* pColPixel, PIXEL colorrgb = { 255,0,255 });

	bool IsPrevCollisionEnter() { return m_strstay.mb_stay; }
	
	void SetAirTime(float time) { m_airtime = time; }
	void SetUseGravity(bool buse) { m_bUseGravity = buse; }
	void SetGravity(Vector2 gravity) { m_gravity = gravity; }
	Vector2& GetGravity() { return m_gravity; }
	STAY& GetStateInfo() { return m_strstay; }
	float GetAirTime() { return m_airtime; }

	void ProcessPlayer(PlayerObject* pPlayer, float dt);

private:
	ColliderManager * m_Colmrg;
	bool m_bUseGravity;
	STAY m_strstay;
	Vector2 m_Velocity;
	Vector2 m_gravity;
	Vector2 m_DefaultGravity;
	// player
	float m_airtime;
	// other
	int m_previnfoIndex;
};

#endif // !_RIGIDBODY_H_

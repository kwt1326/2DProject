#include "BulletScript.h"
#include "Attack.h"
#include "Rigidbody.h"
#include "ColliderManager.h"

BulletScript::BulletScript()
{
	m_durationtime = 0;
	if (PLAYER_INSTANCE->GetDirection())
	{
		m_dir = TRUE;
	}
	else if (!PLAYER_INSTANCE->GetDirection())
	{
		m_dir = FALSE;
	}
}


BulletScript::~BulletScript()
{
}

void BulletScript::Update(float dt)
{
	if (m_dir == TRUE)
	{
		GetComponent<Transform>()->SetPosition(
			Vector2(GetComponent<Transform>()->GetPosition().x + (500.f * dt), GetComponent<Transform>()->GetPosition().y));
		m_durationtime += dt;
		if (m_durationtime > 2.0f) 
			COLLIDER_MGR->RemoveObj(this->m_GameObject);
	}
	else if (m_dir == FALSE)
	{
		GetComponent<Transform>()->SetPosition(
			Vector2(GetComponent<Transform>()->GetPosition().x - (500.f * dt), GetComponent<Transform>()->GetPosition().y));
		m_durationtime += dt;
		if (m_durationtime > 2.0f) 
			COLLIDER_MGR->RemoveObj(this->m_GameObject);
	}

};

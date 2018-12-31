#include "Camera2D.h"
#include "ColliderManager.h"
#include "Gamemanager.h"
#include "Transform.h"
#include "input.h"
#include "image.h"
#include "Renderer.h"
#include "Component.h"
#include "ObjectManager.h"
#include "LOG_MGR.h"
#include "PlayerObject.h"
#include "PlayerScript.h"
#include "Enumdefinition.h"

Camera2D::Camera2D()
	:m_active(false)
{
	m_strfilter.clear();
}

Camera2D::~Camera2D()
{
}

void Camera2D::Update(float dt)
{
	auto player = PLAYER_INSTANCE;

	Vector2 rectpoint(m_pGamemrg->Getrect().right, m_pGamemrg->Getrect().bottom);

	//if (!player->GetGamestart()) return;

	Scroll(player, rectpoint);
}
void Camera2D::Init()
{
	m_mapRect = Vector2(GetComponent<Renderer>()->GetImage()->GetWidth(), GetComponent<Renderer>()->GetImage()->GetHeight());
	m_tr = GetComponent<Transform>();
	m_pGamemrg = GAME_MGR;
	m_pObjmrg = OBJECT_MGR->GetInstance();

	m_strfilter.push_back("Player");
	m_strfilter.push_back("Field");
	m_strfilter.push_back("Background");
}
void Camera2D::Release()
{

}

Vector2 Camera2D::GetPosition()
{
	return (m_tr->GetPosition() * (-1));
}
Vector2 Camera2D::GetMaxMovablePosition() // 최대 스크롤 가능 범위
{
	Vector2 rectpoint(m_pGamemrg->Getrect().right, m_pGamemrg->Getrect().bottom);
	return (m_mapRect - (rectpoint/2));
}

// Player 의 OffSet을 따라간다.
void Camera2D::Scroll(PlayerObject* player, Vector2 rectpoint)
{
	PlayerScript* script = player->GetComponent<PlayerScript>();
	Vector2 point = player->GetWorldPosition();
	Vector2 prevCamPos = m_tr->GetPosition();
	float rectcenterX = rectpoint.x *0.5;
	float rectcenterY = rectpoint.y *0.5;
	Vector2 calcCameraPoint = (point - (rectpoint / 2)) *(-1); // 이미지는 반대로 움직여야한다.
	Vector2 moveCameraPoint = Vector2::Zero;

	if (point.x >= rectcenterX && point.x <= m_mapRect.x - rectpoint.x / 2)
	{
		m_tr->SetPosition(Vector2(calcCameraPoint.x, m_tr->GetPosition().y));
	}
	else
	{
		if(m_tr->GetPosition().x > 0)
			m_tr->SetPosition(Vector2(0, m_tr->GetPosition().y));
		else if(m_tr->GetPosition().x < -(m_mapRect.x - rectcenterX)) // (맵 최대치 - 화면 절반) *(-1) 보다 작으면 허용치를 넘은것.
			m_tr->SetPosition(Vector2(-(m_mapRect.x - rectcenterX), m_tr->GetPosition().y));
	}

	if (point.y >= rectcenterY && point.y <= m_mapRect.y - rectpoint.y / 2)
	{
		m_tr->SetPosition(Vector2(m_tr->GetPosition().x, calcCameraPoint.y));
	}
	else
	{
		if (m_tr->GetPosition().y > 0)
			m_tr->SetPosition(Vector2(m_tr->GetPosition().x, 0));
		else if (m_tr->GetPosition().y < -(m_mapRect.y - rectcenterY)) // (맵 최대치 - 화면 절반) *(-1) 보다 작으면 허용치를 넘은것.
			m_tr->SetPosition(Vector2(m_tr->GetPosition().x ,-(m_mapRect.y - rectcenterY)));
	}

	// Object (enemy, bullet 등) All Scroll
	std::vector<GameObject*>& vecObjlist = m_pObjmrg->GetObjectList();
	std::vector<GameObject*>::iterator itr = vecObjlist.begin();
	moveCameraPoint = m_tr->GetPosition() - prevCamPos; 

	for ( ;itr != vecObjlist.end(); ++itr)
	{
		GameObject* pObject = (*itr);
		bool bFilltering = false; 
		for (int i = 0; i < m_strfilter.size(); ++i)
		{
			if (pObject->GetName().compare(m_strfilter[i]) == 0)
			{
				bFilltering = true; break;
			}
		}
		if (!bFilltering)
		{
			Vector2 curpos = pObject->GetTransform()->GetPosition();
			pObject->GetTransform()->SetPosition(pObject->GetTransform()->GetPosition() + moveCameraPoint);
		}
	}

	// Field Collider All Scroll
	std::list<ColliderInfo>& rectcolliderlist = COLLIDER_MGR->GetCurField();
	std::list<ColliderInfo>::iterator it = rectcolliderlist.begin();
	Rect moverect = { moveCameraPoint.x,moveCameraPoint.y,moveCameraPoint.x,moveCameraPoint.y };
	for ( ; it != rectcolliderlist.end() ; ++it){
		(*it).col += moverect;
		if((*it).nType != 0) {
			std::list <Rect>& staircollist = (*it).m_listlinecol;
			std::list <Rect>::iterator itr = staircollist.begin();
			for (; itr != staircollist.end(); ++itr) {
				(*itr) += moverect;
			}
		}
	}
}
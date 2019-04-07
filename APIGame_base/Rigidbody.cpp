#include "Rigidbody.h"
#include "LOG_MGR.h"
#include "ObjectManager.h"
#include "PlayerObject.h"
#include "PlayerScript.h"
#include "ColliderManager.h"
#include "Gamemanager.h"

Rigidbody::Rigidbody()
{
	m_Velocity = Vector2::Zero;
	m_strstay = { false, 0 ,Vector2(0,0),false,false };
	m_Enable = true;
	m_gravity = m_DefaultGravity = Vector2(0, 300);
	m_bUseGravity = true;
	m_airtime = 0.f;
	m_Colmrg = COLLIDER_MGR;
	m_previnfoIndex = 0;
}
Rigidbody::~Rigidbody()
{
}

// Rect �浹 (�� �⺻ �浹) 
bool Rigidbody::OnRectColliderEnter_PLAYER(PlayerObject* player)
{
	PlayerScript* pScript = player->GetComponent<PlayerScript>();
	Rect& playercol = player->GetLocalRect();

	player->SetBlockState(NO_BLOCK);
	m_strstay.m_bOnMap = false;
	m_strstay.m_bOnHWall = false;

	std::list<ColliderInfo>& colliderlist = m_Colmrg->GetCurField();
	std::list<ColliderInfo>::iterator it = colliderlist.begin();
	std::list<ColliderInfo>::iterator instance_it = colliderlist.begin();
	std::advance(instance_it, m_previnfoIndex);

	if (Physic::RectToRectCollisionCheck(playercol, (*instance_it).col)) {
		if ((*instance_it).nType != 0) {
			auto collist = (*instance_it).m_listlinecol;
			if (!collist.empty()) {
				for (auto itr = collist.begin(); itr != collist.end(); ++itr) {
					if (OnStairColliderEnter_Check_PLAYER(player, playercol, (*itr))) {
						return true;
					}
				}
			}
		}
		else {
			if (OnRectColliderEnter_Check_PLAYER(player, playercol, (*instance_it))) {
				return true;
			}
		}
	}

	int nCount = 0;
	for (; it != colliderlist.end(); ++it)
	{
		m_strstay.m_coord = Vector2::Zero;
		Rect& Mapcol = (*it).col;

		if (Physic::RectToRectCollisionCheck(playercol, Mapcol))
		{
			if ((*it).nType != 0) {
				auto collist = (*it).m_listlinecol;
				if (!collist.empty()) {
					for (auto itr = collist.begin(); itr != collist.end(); ++itr) {
						if (OnStairColliderEnter_Check_PLAYER(player, playercol, (*itr))) {
							m_previnfoIndex = nCount;
							return true;
						}
					}
				}
			}

			if (OnRectColliderEnter_Check_PLAYER(player, playercol, (*it))) {
				return true;
			}
		}
		++nCount;
	}
	return false;
}
// Line �浹 [Diagonel]
bool Rigidbody::OnDiagonelColliderEnter_Check_PLAYER(PlayerObject* player, ColliderInfo& mapCol)
{
	PlayerScript* pScript = player->GetComponent<PlayerScript>();
	Rect& Mapcol = mapCol.col;

	Vector2 playerRay_Spoint(player->GetPosition().x, player->GetPosition().y);
	Vector2 playerRay_Epoint(player->GetPosition().x, player->GetPosition().y + PLAYER_V_HALFSIZE);
	Vector2 s, d;

	if (mapCol.nType == 0) {
		return false;
	}

	if (mapCol.nType == 1) {
		s = Vector2(Mapcol.Left, Mapcol.Top);
		d = Vector2(Mapcol.Right, Mapcol.Bottom);
	}
	else if (mapCol.nType == 2) {
		s = Vector2(Mapcol.Left, Mapcol.Bottom);
		d = Vector2(Mapcol.Right, Mapcol.Top);
	}
	Vector2 result = Vector2::Zero;
	if (Vector2::SegmentIntersection(s, d, playerRay_Spoint, playerRay_Epoint, result))
	{
		Vector2 movew(player->GetWorldPosition().x, result.y - PLAYER_V_HALFSIZE);
		Vector2 move(player->GetPosition().x, result.y - PLAYER_V_HALFSIZE);
		pScript->SetComparePosition(move, movew);
		m_strstay.m_bOnMap = true;
		player->SetJump(false);
		SetGravity(Vector2::Zero);
		return true;
	}
	return false;
}
bool Rigidbody::OnStairColliderEnter_Check_PLAYER(PlayerObject* player, Rect& playercol, Rect& mapcol) {

	PlayerScript* pScript = player->GetComponent<PlayerScript>();
	Rect Mapcol = mapcol;
	Rect Mergecol;

	std::function<bool()> SetPosition = [&]() mutable -> bool {
		Vector2 movew = player->GetWorldPosition() + m_strstay.m_coord;
		Vector2 move = player->GetPosition() + m_strstay.m_coord;
		pScript->SetComparePosition(move, movew);
		m_strstay.m_coord = Vector2::Zero;
		return true;
	};

	Mergecol.Left = (playercol.Left > Mapcol.Left) ? playercol.Left : Mapcol.Left;
	Mergecol.Right = (playercol.Right < Mapcol.Right) ? playercol.Right : Mapcol.Right;
	Mergecol.Top = (playercol.Top > Mapcol.Top) ? playercol.Top : Mapcol.Top;
	Mergecol.Bottom = (playercol.Bottom < Mapcol.Bottom) ? playercol.Bottom : Mapcol.Bottom;

	float MergecolHorizontal = Mergecol.Right - Mergecol.Left;
	float MergecolVertical = Mergecol.Bottom - Mergecol.Top;

	if(MergecolHorizontal > MergecolVertical)
	{
		if (playercol.Bottom > Mapcol.Top && playercol.Top < Mapcol.Bottom || playercol.Top < Mapcol.Bottom && playercol.Bottom > Mapcol.Top)
		{
			if (Mergecol.Top == Mapcol.Top) { // �ٴ� ����
				m_strstay.m_coord.y = -MergecolVertical + /*������*/0.5;
				m_strstay.m_bOnMap = true;
				player->SetJump(false);
				SetGravity(Vector2::Zero);
			}
			return SetPosition();
		}
	}
	return false;
}

bool Rigidbody::OnRectColliderEnter_Check_PLAYER(PlayerObject* player, Rect& playercol, ColliderInfo& mapinfo) {

	PlayerScript* pScript = player->GetComponent<PlayerScript>();
	Rect Mapcol = mapinfo.col;
	Rect Mergecol;

	if (mapinfo.nType != 0) {
		return false;
	}

	std::function<bool()> SetPosition = [&]() mutable -> bool {
		Vector2 movew = player->GetWorldPosition() + m_strstay.m_coord;
		Vector2 move = player->GetPosition() + m_strstay.m_coord;
		pScript->SetComparePosition(move, movew);
		m_strstay.m_coord = Vector2::Zero;
		return true;
	};

	Mergecol.Left = (playercol.Left > Mapcol.Left) ? playercol.Left : Mapcol.Left;
	Mergecol.Right = (playercol.Right < Mapcol.Right) ? playercol.Right : Mapcol.Right;
	Mergecol.Top = (playercol.Top > Mapcol.Top) ? playercol.Top : Mapcol.Top;
	Mergecol.Bottom = (playercol.Bottom < Mapcol.Bottom) ? playercol.Bottom : Mapcol.Bottom;

	float MergecolHorizontal = Mergecol.Right - Mergecol.Left;
	float MergecolVertical = Mergecol.Bottom - Mergecol.Top;

	if (MergecolHorizontal < MergecolVertical)
	{
		// ���� �浹
		if (playercol.Right > Mapcol.Right && playercol.Left > Mapcol.Left || playercol.Left < Mapcol.Left && playercol.Right < Mapcol.Right)
		{
			if (Mergecol.Right == Mapcol.Right)
			{
				m_strstay.m_coord.x = MergecolHorizontal;
				player->SetBlockState(LEFT_BLOCK);
			}
			else if (Mergecol.Left == Mapcol.Left)
			{
				m_strstay.m_coord.x = -MergecolHorizontal;
				player->SetBlockState(RIGHT_BLOCK);
			}
			m_strstay.m_bOnHWall = true;
			return SetPosition();
		}
	}
	else
	{
		// ���� �浹
		if (playercol.Bottom > Mapcol.Top && playercol.Top < Mapcol.Bottom || playercol.Top < Mapcol.Bottom && playercol.Bottom > Mapcol.Top)
		{
			if (Mergecol.Top == Mapcol.Top) { // �ٴ� ����
				m_strstay.m_coord.y = -MergecolVertical + /*������*/2;
				m_strstay.m_bOnMap = true;
				player->SetJump(false);
				SetGravity(Vector2::Zero);
			}

			else if (Mergecol.Bottom == Mapcol.Bottom) { // õ�� �浹
				m_strstay.m_coord.y = MergecolVertical;
			}
			return SetPosition();
		}
	}
	return false;
}
//[����]
bool Rigidbody::OnRectColliderEnter(GameObject * pObject)
{
	std::function<bool()> SetPosition = [&]() mutable -> bool {
		Vector2 move = pObject->GetComponent<Transform>()->GetPosition() + m_strstay.m_coord;
		m_strstay.m_coord = Vector2::Zero;
		pObject->GetComponent<Transform>()->SetPosition(move);
		return true;
	};

	Rect col = pObject->GetComponent<Collider>()->GetRect();
	std::list<ColliderInfo>& colliderlist = m_Colmrg->GetCurField();
	std::list<ColliderInfo>::iterator it = colliderlist.begin();

	for (auto itr = colliderlist.begin(); itr != colliderlist.end(); ++itr) 
	{
		if (Physic::RectToRectCollisionCheck(col, (*itr).col)) 
		{
			Rect Mapcol = (*itr).col;
			Rect Mergecol;

			Mergecol.Left = (col.Left > Mapcol.Left) ? col.Left : Mapcol.Left;
			Mergecol.Right = (col.Right < Mapcol.Right) ? col.Right : Mapcol.Right;
			Mergecol.Top = (col.Top > Mapcol.Top) ? col.Top : Mapcol.Top;
			Mergecol.Bottom = (col.Bottom < Mapcol.Bottom) ? col.Bottom : Mapcol.Bottom;

			float MergecolHorizontal = Mergecol.Right - Mergecol.Left;
			float MergecolVertical = Mergecol.Bottom - Mergecol.Top;

			if (MergecolHorizontal < MergecolVertical)
			{
				// ���� �浹
				if (col.Right > Mapcol.Right && col.Left > Mapcol.Left || col.Left < Mapcol.Left && col.Right < Mapcol.Right)
				{
					if (Mergecol.Right == Mapcol.Right) {
						m_strstay.m_coord.x = MergecolHorizontal;
					}
					else if (Mergecol.Left == Mapcol.Left) {
						m_strstay.m_coord.x = -MergecolHorizontal;
					}
					m_strstay.m_bOnHWall = true;
					return SetPosition();
				}
			}
			else
			{
				// ���� �浹
				if (col.Bottom > Mapcol.Top && col.Top < Mapcol.Bottom || col.Top < Mapcol.Bottom && col.Bottom > Mapcol.Top)
				{
					if (Mergecol.Top == Mapcol.Top) { // �ٴ� ����
						m_strstay.m_coord.y = -MergecolVertical;
						m_strstay.m_bOnMap = true;
						SetGravity(Vector2::Zero);
					}
					else if (Mergecol.Bottom == Mapcol.Bottom) { // õ�� �浹
						m_strstay.m_coord.y = MergecolVertical;
					}
					return SetPosition();
				}
			}
		}
	}
	m_strstay.m_bOnHWall = false;
	m_strstay.m_bOnMap = false;
	return false;
}

// �÷��̾ �� �ݶ��̴� ���� ������ �� �Ǵܿ� (���� ��� X)
bool Rigidbody::HitColliderOnMap(const Rect playercol, const Rect Mapcol)
{
	Rect Mergecol;

	Mergecol.Top = (playercol.Top > Mapcol.Top) ? playercol.Top : Mapcol.Top;

	if (playercol.Bottom > Mapcol.Top && playercol.Top < Mapcol.Bottom)
	{
		if (Mergecol.Top == Mapcol.Top)
		{
			return true;
		}
		else
			return false;
	}
	else return false;
}
// [Rect]
int Rigidbody::HitColliderToHorizon(const Rect playercol, const Rect Mapcol)
{
	if (playercol.Right > Mapcol.Right && playercol.Left > Mapcol.Left)		 return 1; // �����ʿ��� ���� ���� �浹��
	else if (playercol.Left < Mapcol.Left && playercol.Right < Mapcol.Right) return 2; // ���ʿ��� ������ ���� �浹��
	else return 0;
}

bool Rigidbody::OnPixleCollisionEnter(Vector2* vArr, ColliderPixel* pColPixel, PIXEL colorrgb) // Ray �浹
{
	std::vector<PIXEL>& RasterData = pColPixel->GetPixel();
	int iwidth = pColPixel->GetWidth();
	int iheight = pColPixel->GetHeight();

	int startX, startY;
	int EndX, EndY;

	startX = vArr[0].x < 0 ? 0 : vArr[0].x;
	startY = vArr[0].y < 0 ? 0 : vArr[0].y;
	EndX = vArr[1].x >= iwidth ? iwidth - 1 : vArr[1].x;
	EndY = vArr[1].y >= iheight ? iheight - 1 : vArr[1].y;

	for (int i = startY; i <= EndY; ++i)
	{
		for (int j = startX; j <= EndX; ++j)
		{
			unsigned int idx = (i * iwidth) + j;
			PIXEL& pixel = RasterData[idx];
			if (pixel.Compare(colorrgb))
			{
				m_strstay = { true, idx, Vector2(j, i) }; // stay check
				return true;
			}
		}
	}

	return false;
}
// [Pixel]�ٴ� �˻� �̹Ƿ� �ٴ� ���ٸ� �˻��Ѵ�. (����, �� ��ũ�Ѹ� �߿��� ��Ʈ�� �ȼ���ǥ�� ���Ͻ� ���� �����Ƿ� ���� Ʈ������ �̿�)
bool Rigidbody::OnPixleCollisionLanding(PlayerObject* pObject, ColliderPixel* pColPixel, PIXEL colorrgb)
{
	Rect rt = pObject->GetWorldRect();
	std::vector<PIXEL>& RasterData = pColPixel->GetPixel();
	int iwidth = pColPixel->GetWidth();
	int iheight = pColPixel->GetHeight();

	int startX, startY;
	int EndX, EndY;

	startX = rt.Left < 0 ? 0 : rt.Left;
	EndX = rt.Right >= iwidth ? iwidth - 1 : rt.Right;
	EndY = rt.Bottom >= iheight ? iheight - 1 : rt.Bottom;
	
	int center = (startX + EndX) / 2;
	for (int j = center - 5; j <= center + 5; ++j)
	{
		unsigned int idx = (EndY * iwidth) + j;
		if (idx > RasterData.size())
			return false;

		PIXEL& pixel = RasterData[idx];
		if (pixel.Compare(colorrgb))
		{
			while (true)
			{
				unsigned int idx2 = (EndY * iwidth) + j;
				if (idx2 > RasterData.size())
					return false;

				PIXEL& pixel2 = RasterData[idx2];
				if (pixel2.Compare(colorrgb))
				{
					EndY -= 1;
				}
				else
				{
					m_strstay = { true, idx2, Vector2(j,EndY + 1) };
					break;
				}
			}
			return true;
		}
	}
	return false;
}
// [Pixel]���� �� �浹 (�ٴ� - 5 ��ġ �˻�)
bool Rigidbody::OnPixleCollisionHorizon(PlayerObject* pObject, bool bdirection, ColliderPixel* pColPixel, PIXEL colorrgb)
{
	Rect rt = pObject->GetWorldRect();
	std::vector<PIXEL>& RasterData = pColPixel->GetPixel();
	int iwidth = pColPixel->GetWidth();
	int iheight = pColPixel->GetHeight();

	int startX, startY;
	int EndX, EndY;

	startX = rt.Left < 0 ? 0 : rt.Left;
	startY = rt.Top < 0 ? 0 : rt.Top;
	EndX = rt.Right >= iwidth ? iwidth - 1 : rt.Right;
	EndY = rt.Bottom >= iheight ? iheight - 1 : rt.Bottom;

	unsigned int idx = (((EndY-5) * iwidth) + ((bdirection) ? EndX : startX));
	if (idx > RasterData.size())
		return false;

	PIXEL& pixel = RasterData[idx];
	if (pixel.Compare(colorrgb))
	{
		return true;
	}

	return false;
}
// �밢�� ��� ���� �ٴ� ������ �浹 �˻�
bool Rigidbody::OnPixleCollisionEdgePoint(POINT& pt, ColliderPixel* pColPixel, PIXEL colorrgb) // POINT �浹
{
	std::vector<PIXEL>& RasterData = pColPixel->GetPixel();
	int x = pt.x < 0 ? 1 : pt.x;
	int y = pt.y < 0 ? 1 : pt.y;
	unsigned int idx = (y * pColPixel->GetWidth()) + x;

	if (idx > RasterData.size())
		return false;

	PIXEL& pixel = RasterData[idx];
	if (pixel.Compare(colorrgb))
	{
		POINT pt2 = { pt.x, pt.y - 1 };
		while (pixel.Compare(colorrgb))
		{
			unsigned int idx = (pt2.y * pColPixel->GetWidth()) + x;
			if (idx > RasterData.size())
				return false;

			pixel = RasterData[idx];
			pt2.y -= 1;
			if (pt2.y == -1)
			{
				m_strstay = { true, idx, Vector2(pt.x, pt.y) };
				return true;
			}
		}
		m_strstay = { true, idx, Vector2(pt2.x + 2, pt2.y + 2) }; // stay check only player
		return true;
	}
	return false;
}
// ����
bool Rigidbody::OnPixleCollisionPoint(POINT& pt, ColliderPixel* pColPixel, PIXEL colorrgb)
{
	std::vector<PIXEL>& RasterData = pColPixel->GetPixel();
	int x = pt.x < 0 ? 1 : pt.x;
	int y = pt.y < 0 ? 1 : pt.y;
	unsigned int idx = (y * pColPixel->GetWidth()) + x;
	PIXEL& pixel = RasterData[idx];
	if (pixel.Compare(colorrgb))
	{
		return true;
	}
	else return false;
}

bool Rigidbody::OnPixleCollisionEnter(Rect& rt, ColliderPixel* pColPixel, PIXEL colorrgb) // RECT �浹
{
	std::vector<PIXEL>& RasterData = pColPixel->GetPixel();
	int iwidth = pColPixel->GetWidth();
	int iheight = pColPixel->GetHeight();

	int startX, startY;
	int EndX, EndY;

	startX = rt.Left < 0 ? 0 : rt.Left;
	startY = rt.Top < 0 ? 0 : rt.Top;
	EndX = rt.Right >= iwidth ? iwidth - 1 : rt.Right;
	EndY = rt.Bottom >= iheight ? iheight - 1 : rt.Bottom;

	for (int i = startY; i <= EndY; ++i)
	{
		for (int j = startX; j <= EndX; ++j)
		{
			unsigned int idx = (i * iwidth) + j;
			PIXEL& pixel = RasterData[idx];
			if (pixel.Compare(colorrgb))
			{
				m_strstay = { true, idx, Vector2(j, i) }; // stay check
				return true;
			}
		}
	}

	return false;
}

bool Rigidbody::OnPixleCollisionStay(Rect & rt, ColliderPixel * pColPixel, PIXEL colorrgb)
{
	if (m_strstay.mb_stay)
	{

	}
	return false;
}

void Rigidbody::Init()
{
}
void Rigidbody::Update(float dt)
{
	if (m_bUseGravity)
	{
		if (m_gravity.y == 0) 
			m_Velocity.y = 0;
		if (m_GameObject->GetName().compare("Player") == 0)
		{
			ProcessPlayer(PLAYER_INSTANCE, dt);
		}
		else
		{
			if (m_Velocity.y > 50.f)
				m_Velocity.y = 50.f;

			m_Velocity = (m_gravity * dt);
			Transform* tr = m_GameObject->GetComponent<Transform>();
			if (tr != NULL)
				tr->SetPosition(tr->GetPosition() + m_Velocity);
		}
	}	
}
void Rigidbody::ProcessPlayer(PlayerObject* pPlayer, float dt)
{
	if (m_Velocity.y > 50.f) // ������ ����
		m_Velocity.y = 50.f;

	if (m_gravity.y >= 300.f) // �ִ� �߷� ����
		m_gravity.y = 300.f;

	if (PLAYER_INSTANCE->GetJump() == true)
	{
		if (m_airtime <= 0.7f)
		{
			m_gravity.y += 10;
			m_Velocity = (m_gravity * dt);
			m_airtime += dt;
		}
		else
		{
			if (m_gravity.y < 0) m_gravity *= (-1);
			m_gravity.y += 10;
			m_Velocity = (m_gravity * dt);
			m_airtime = 0.f;
		}
	}
	else
	{
		m_Velocity = (m_gravity * dt);
		m_airtime = 0.f;
	}

	PlayerScript* pScript = m_GameObject->GetComponent<PlayerScript>();
	if (pScript != NULL)
		pScript->SetComparePosition(pPlayer->GetPosition() + m_Velocity, pPlayer->GetWorldPosition() + m_Velocity);
}

void Rigidbody::Release()
{

}

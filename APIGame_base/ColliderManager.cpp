#include "ColliderManager.h"
#include "ObjectManager.h"
#include "input.h"

#include "Attack.h"
#include "EnemyBase.h"
#include "NormalEnemy.h"

ColliderManager* ColliderManager::m_Instance = NULL;

ColliderManager::ColliderManager()
{
}

ColliderManager::~ColliderManager()
{
}
void ColliderManager::init(const char* path) 
{
	PreDrawMode(true);
	m_pPlayer = PLAYER_INSTANCE;
	m_pcam = OBJECT_MGR->GetInstance()->FindObject("Background")->GetComponent<Camera2D>();

	// COLLIDER 파일 구문을 읽어 등록 시킨다. (맵 충돌체 리딩)
	FILE* pfile;
	pfile = fopen(path, "r");
	if (pfile == NULL)
		return;
	else
	{
		char strTemp[255];
		char* pGet, *ptoken;
		int nStage = 0;
		std::list<ColliderInfo> rectBuffer;
		bool bHasCollider = false;
		bool bIsLine = false;

		while (!feof(pfile))
		{
			pGet = fgets(strTemp, sizeof(strTemp), pfile);
			if (!bHasCollider)
			{
				if (strstr(pGet, "[STAGE]") != NULL)
				{
					nStage++;
				}
				else if (strstr(pGet, "[COLLIDER]") != NULL)
				{
					bHasCollider = true;
					continue;
				}
			}
			else
			{
				ColliderInfo info;
				bIsLine = false;

				if (strstr(pGet, "[END]") != nullptr)
				{
					m_colliderFieldlist["STAGE" + std::to_string(nStage)] = rectBuffer;
					bHasCollider = false;
					rectBuffer.clear();
					continue;
				}

				char* pline = strstr(pGet, "[LINE]");
				if (pline != NULL)
				{
					pGet = strtok(pline, "[LINE]");
					bIsLine = true;
				}

				int nindex = 0;
				float rectfactor[] = { 0,0,0,0,0 };
				char* presult = strtok(pGet, ",");
				rectfactor[nindex] = atof(presult);
				++nindex;
				while (presult = strtok(NULL, ","))
				{
					rectfactor[nindex] = atof(presult);
					++nindex;
				}
				Rect buffer(rectfactor[0], rectfactor[1], rectfactor[2], rectfactor[3]);
				info.col = buffer;
				info.nType = (bIsLine) ? (int)rectfactor[4] : 0;
				if (bIsLine) {
					int colcount = (buffer.Right - buffer.Left) / m_LineColthink;
					double dHlength = buffer.Right - buffer.Left;
					double dHlength_piece = dHlength / colcount;
					double dVlength = buffer.Bottom - buffer.Top;
					double dVlength_piece = dVlength / colcount;
					for (int i = 0; i < colcount; ++i) {
						if (info.nType == 1) {
							Rect col(/*left*/ rectfactor[0] + dHlength_piece * (i), /*top*/ rectfactor[1] + dVlength_piece * (i + 1), 
									/*right*/ rectfactor[0] + dHlength_piece * (i) + m_LineColthink, /*bottom*/ rectfactor[3]);
							info.m_listlinecol.push_back(col);
						}
						else if (info.nType == 2) {
							Rect col(/*left*/ rectfactor[0] + dHlength_piece * (i), /*top*/ rectfactor[1] + dVlength_piece * (colcount - i),
									/*right*/ rectfactor[0] + dHlength_piece * (i) + m_LineColthink, /*bottom*/ rectfactor[3]);
							info.m_listlinecol.push_back(col);
						}
					}
				}
				rectBuffer.push_back(info);
			}
		}
		fclose(pfile);
	}
}

void ColliderManager::Release()
{
	PreDrawMode(false);
	m_pField = NULL;
	m_InstanceColliderlist.clear();
	m_EnemyColliderlist.clear();
}	
void ColliderManager::Update_CollisionCheck(float dt) // (플레이어 제외) 오브젝트 충돌 이벤트 체크
{
	if (input::GetKeyDown(0x50)) m_bDraw = (m_bDraw) ? false : true;

	Draw(m_bDraw);

	// 적/아군 총알 <-> 필드_충돌
	std::list<ColliderInfo>& curColliderlist = GetCurField();
	std::list<ColliderInfo>::iterator itCol = curColliderlist.begin();

	for (; itCol != curColliderlist.end(); ++itCol) {
		std::list<GameObject*>::iterator itr = m_InstanceColliderlist.begin();
		while (itr != m_InstanceColliderlist.end()) 
		{
			Collider* col = (*itr)->GetComponent<Collider>();
			Rigidbody* rg = (*itr)->GetComponent<Rigidbody>();
			if (col != NULL && rg != NULL) {
				if (col->GetIsInstance()) {
					Rect& rect = col->GetRect();
					if (Physic::RectToRectCollisionCheck(rect, (*itCol).col))
					{
						OBJECT_MGR->Destroy((*itr));
						itr = m_InstanceColliderlist.erase(itr);
						continue;
					}
				}
			}
			++itr;
		}
	}

	// 적/아군 총알 <-> 적/아군 오브젝트
	std::list<GameObject*>::iterator itCol2 = m_EnemyColliderlist.begin();
	for (; itCol2 != m_EnemyColliderlist.end(); ++itCol2) {
		std::list<GameObject*>::iterator itr = m_InstanceColliderlist.begin();
		while (itr != m_InstanceColliderlist.end())
		{
			Collider* col = (*itr)->GetComponent<Collider>();
			Rigidbody* rg = (*itr)->GetComponent<Rigidbody>();
			if (col != NULL && rg != NULL) {
				if (col->GetIsInstance()) {
					Rect& rect = col->GetRect();
					Collider* pCol = (*itCol2)->GetComponent<Collider>();
					if (pCol) {
						if (Physic::RectToRectCollisionCheck(rect, pCol->GetRect()))
						{
							// 적 체력 처리
							Attack* pAtk = dynamic_cast<Attack*>(*itr);
							EnemyBase* penemy = dynamic_cast<EnemyBase*>(*itCol2);

							penemy->SetHealth(penemy->GetHealth() - pAtk->GetDamage());
							if (penemy->GetHealth() == 0) {
								/* 폭발 애니메이션 넣어야함 */
								OBJECT_MGR->Destroy((*itCol2));
								itCol2 = m_EnemyColliderlist.erase(itCol2);
							}

							// 처리 후 불렛 제거
							OBJECT_MGR->Destroy((*itr));
							itr = m_InstanceColliderlist.erase(itr);
							continue;
						}
					}
				}
			}
			++itr;
		}
	}

}

void ColliderManager::RemoveObj(GameObject * pobj)
{
	auto itr = std::find(m_InstanceColliderlist.begin(), m_InstanceColliderlist.end(), pobj);
	if (itr != m_InstanceColliderlist.end())
	{
		OBJECT_MGR->Destroy(pobj);
		m_InstanceColliderlist.erase(itr);
	}
}

void ColliderManager::PreDrawMode(bool btrue)
{
	if (btrue)
	{
		m_hdc = BeginPaint(GAME_MGR->Gethwnd(), &m_ps);
		MyBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		OldBrush = (HBRUSH)SelectObject(m_hdc, MyBrush);
		Mypen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		Oldpen = (HPEN)SelectObject(m_hdc, Mypen);
	}
	else
	{
		SelectObject(m_hdc, OldBrush);
		DeleteObject(MyBrush);
		SelectObject(m_hdc, Oldpen);
		DeleteObject(Mypen);
		EndPaint(GAME_MGR->Gethwnd(), &m_ps);
	}
}
void ColliderManager::Draw(bool btrue)
{
	// Debug Only
	if (btrue)
	{
		std::list<ColliderInfo>& Collist = m_colliderFieldlist["STAGE" + std::to_string(m_nStage)];
		for (auto it = Collist.begin(); it != Collist.end(); ++it){
			Rect col = (*it).col;
			Rectangle(m_hdc, col.Left, col.Top, col.Right, col.Bottom);
			if ((*it).nType == 1)
			{
				for (auto a = (*it).m_listlinecol.begin(); a != (*it).m_listlinecol.end(); ++a) {
					Rectangle(m_hdc, (*a).Left, (*a).Top, (*a).Right, (*a).Bottom);
				}
			}
			else if ((*it).nType == 2)
			{
				for (auto a = (*it).m_listlinecol.begin(); a != (*it).m_listlinecol.end(); ++a) {
					Rectangle(m_hdc, (*a).Left, (*a).Top, (*a).Right, (*a).Bottom);
				}
			}
		}

		Rect PlayerRect = m_pPlayer->GetLocalRect(); 
		Rect PlayerRectW = m_pPlayer->GetWorldRect();

		std::vector<GameObject*>& reflist = OBJECT_MGR->GetInstance()->GetObjectList();
		for (auto a = reflist.begin(); a != reflist.end(); ++a) {
			if ((*a)->GetName().compare("Player") == 0) 
				continue;
			else 
			{
				// 적 감지 범위 확인
				NormalEnemy* pEnemy = dynamic_cast<NormalEnemy*>(*a);
				if (pEnemy) {
					Vector2 center = pEnemy->GetDetectionCircle().Center;
					float radius = pEnemy->GetDetectionCircle().Radius;
					Ellipse(m_hdc, center.x - radius, center.y - radius, center.x + radius, center.y + radius);
				}

				// other
				Collider* pcol = (*a)->GetComponent<Collider>();
				if (pcol != NULL) {
					Rect rect = pcol->GetRect();
					Rectangle(m_hdc, rect.Left, rect.Top, rect.Right, rect.Bottom);
				}
			}
		}

		Rectangle(m_hdc, PlayerRect.Left, PlayerRect.Top, PlayerRect.Right, PlayerRect.Bottom);

		// 맵벡터값 실시간 표시
		char Timestr[255];
		sprintf(Timestr, "MapVector : %.2f, %.2f", m_pcam->GetPosition().x, m_pcam->GetPosition().y);
		TextOut(m_hdc, 0, 45, (Timestr), strlen(Timestr));
		sprintf(Timestr, "playerpos : %.2f, %.2f", m_pPlayer->GetPosition().x, m_pPlayer->GetPosition().y);
		TextOut(m_hdc, 0, 60, (Timestr), strlen(Timestr));
		sprintf(Timestr, "playerpos : %.2f, %.2f", m_pPlayer->GetWorldPosition().x, m_pPlayer->GetWorldPosition().y);
		TextOut(m_hdc, 0, 75, (Timestr), strlen(Timestr));
		sprintf(Timestr, "playerWorldRect : %.2f, %.2f,%.2f, %.2f", PlayerRectW.Left, PlayerRectW.Top, PlayerRectW.Right, PlayerRectW.Bottom);
		TextOut(m_hdc, 0, 90, (Timestr), strlen(Timestr));
		sprintf(Timestr, "playerLocalRect : %.2f, %.2f,%.2f, %.2f", PlayerRect.Left, PlayerRect.Top, PlayerRect.Right, PlayerRect.Bottom);
		TextOut(m_hdc, 0, 105, (Timestr), strlen(Timestr));
	}
}

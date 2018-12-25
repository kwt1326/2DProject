#include "ColliderManager.h"
#include "ObjectManager.h"
#include "input.h"

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

	// COLLIDER 파일 구문을 읽어 등록 시킨다.
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
				ColliderInfo info;
				info.col = buffer;
				info.nType = (bIsLine) ? (int)rectfactor[4] : 0;
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
	m_colliderObjlist.clear();
}
void ColliderManager::UpdateObjectOnField(float dt) // 오브젝트의 픽셀 필드 접촉 이벤트
{
	if (input::GetKeyDown(0x50)) m_bDraw = (m_bDraw) ? false : true;

	Draw(m_bDraw);

	std::list<ColliderInfo>& curColliderlist = GetCurField();
	std::list<ColliderInfo>::iterator itCol = curColliderlist.begin();

	if (curColliderlist.empty()) return;

	for (; itCol != curColliderlist.end(); ++itCol)
	{
		std::list<GameObject*>::iterator itr = m_colliderObjlist.begin();
		while (itr != m_colliderObjlist.end())
		{
			Collider* col = (*itr)->GetComponent<Collider>();
			Rigidbody* rg = (*itr)->GetComponent<Rigidbody>();
			if (col != NULL && rg != NULL)
			{
				if (col->GetIsInstance())
				{
					Rect& rect = col->GetRect();
					if (Physic::RectToRectCollisionCheck(rect, (*itCol).col)) // 인스턴스가 필드에 충돌시 삭제된다.
					{
						OBJECT_MGR->Destroy((*itr));
						itr = m_colliderObjlist.erase(itr);
						continue;
					}
				}
			}
			++itr; // if erase iterator using, must [add 1] part partial.
		}
	}
}

void ColliderManager::RemoveObj(GameObject * pobj)
{
	auto itr = std::find(m_colliderObjlist.begin(), m_colliderObjlist.end(), pobj);
	if (itr != m_colliderObjlist.end())
	{
		OBJECT_MGR->Destroy(pobj);
		m_colliderObjlist.erase(itr);
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
	if (btrue)
	{
		std::list<ColliderInfo>& Collist = m_colliderFieldlist["STAGE" + std::to_string(m_nStage)];
		for (auto it = Collist.begin(); it != Collist.end(); ++it){
			Rect col = (*it).col;
			Rectangle(m_hdc, col.Left, col.Top, col.Right, col.Bottom);
			if ((*it).nType == 1)
			{
				MoveToEx(m_hdc, col.Left, col.Top, NULL);
				LineTo(m_hdc, col.Right, col.Bottom);
			}
			else if ((*it).nType == 2)
			{
				MoveToEx(m_hdc, col.Left, col.Bottom, NULL);
				LineTo(m_hdc, col.Right, col.Top);
			}
		}

		Rect PlayerRect = m_pPlayer->GetLocalRect(); /*Rect(point.x - 20, point.y - 50, point.x + 20, point.y + 50);*/
		Rect PlayerRectW = m_pPlayer->GetWorldRect();
		Rect PlayerRectX = m_pPlayer->GetRect();

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
		sprintf(Timestr, "playerRectXXXX : %.2f, %.2f,%.2f, %.2f", PlayerRectX.Left, PlayerRectX.Top, PlayerRectX.Right, PlayerRectX.Bottom);
		TextOut(m_hdc, 0, 120, (Timestr), strlen(Timestr));
	}
}

#include "stdafx.h"
#include "ObjMgr.h"
#include"Obj.h"
#include "CollisionMgr.h"
#include "ScrollMgr.h"

#include "GunDead.h"
#include "RedGunDead.h"
#include "BlueGunDead.h"
#include "Galme.h"
#include "Mage.h"
#include "Knight.h"

CObjMgr* CObjMgr::m_pInstance = nullptr;
CObjMgr::CObjMgr() : m_bEdit(false)
{
}

CObjMgr::~CObjMgr()
{
	Release();
}

void CObjMgr::Update()
{
	for (int i = 0; i < OBJID::END; i++)
	{
		auto iter = m_listObj[i].begin();
		for (; iter != m_listObj[i].end();)
		{
			int iEvent = (*iter)->Update();
			if (OBJ_DEAD == iEvent)
			{
				SAFE_DELETE(*iter);
				iter = m_listObj[i].erase(iter);
			}
			else
				iter++;
		}
	}

	//플레이어 충돌
	CCollisionMgr::Collision_Player_Tile(m_listObj[OBJID::PLAYER], m_listObj[OBJID::MONSTER]);
	CCollisionMgr::Collision_Obj_EffetBullet(m_listObj[OBJID::M_EFFECTATTACK], m_listObj[OBJID::PLAYER]);
	CCollisionMgr::Collision_RectEx(m_listObj[OBJID::MONSTER],m_listObj[OBJID::PLAYER]);
	
	
	//오브젝트 총알 처리 
	CCollisionMgr::Collision_Obj_Bullet(m_listObj[OBJID::PLAYER], m_listObj[OBJID::M_BULLET]);
	CCollisionMgr::Collision_Obj_Bullet(m_listObj[OBJID::MONSTER], m_listObj[OBJID::P_BULLET]);



	CCollisionMgr::Collision_RectEx(m_listObj[OBJID::MONSTER], m_listObj[OBJID::MONSTER]);


	//총알 충돌
	CCollisionMgr::Collision_BlankShot(m_listObj[OBJID::DEL_BULLET], m_listObj[OBJID::M_BULLET]);
	CCollisionMgr::Collision_Tile_Bullet(m_listObj[OBJID::P_BULLET]);
	CCollisionMgr::Collision_Tile_Bullet(m_listObj[OBJID::M_BULLET]);

	CCollisionMgr::Collision_Monster_Tile((m_listObj[OBJID::MONSTER]));
}

void CObjMgr::Late_Update()
{
	for (int i = 0; i < OBJID::END; i++)
	{
		for (auto& pObj : m_listObj[i])
		{
	
			pObj->Late_Update();
			if (m_listObj[i].empty())
				break;

			RENDERID::ID eID = pObj->Get_RenderID();

			m_listRender[eID].emplace_back(pObj);
		}
	}
}

//스크롤값으로 컬링 -> 스크롤 최대 값+ 오프셋을 넘어가면 컬링을 진행
//컬라이더 체크 -> 방번호가 눌리면 미사일 전부 삭제

void CObjMgr::Render(HDC _DC)
{

	for (int i = 0; i < RENDERID::END; i++)
	{
		if (RENDERID::OBJECT == i)
			m_listRender[i].sort(CompareY<CObj*>);
		for (auto& pObj : m_listRender[i])
		{
			if (pObj->Get_ColInfo().fX< -500
				|| pObj->Get_ColInfo().fX>(WINCX + 500)
				|| pObj->Get_ColInfo().fY < -500
				|| pObj->Get_ColInfo().fY >(WINCY + 500))
				continue;

			pObj->Render(_DC);
		}
		m_listRender[i].clear();
	}

}

void CObjMgr::Release()
{
	for (int i = 0; i < OBJID::END; i++)
	{
		for_each(m_listObj[i].begin(), m_listObj[i].end(), Safe_Delete<CObj*>);
		m_listObj[i].clear();
	}
}

void CObjMgr::Pop_Monster()
{
	m_listObj[OBJID::MONSTER].pop_back();
}

CObj * CObjMgr::Get_Weapon(WEAPONID::ID _eID) const
{
	auto iter = m_listObj[OBJID::WEAPON].begin();
	for (; iter != m_listObj[OBJID::WEAPON].end(); )
	{
		if ((*iter)->Get_WeaponID() == _eID)
			return (*iter);
		iter++;
	}
	return nullptr;
}

void CObjMgr::Delete_ObjID(OBJID::ID _eID)
{
	for_each(m_listObj[_eID].begin(), m_listObj[_eID].end(), Safe_Delete<CObj*>);
	m_listObj[_eID].clear();
}


void CObjMgr::Create_Monster(float fX, float fY, int RoomNum, int MonsterNum)
{
	CObj* Obj = nullptr;
	switch (MonsterNum)
	{
	case 1:
		Obj = CAbstractFactory<CGunDead>::Create(fX, fY, OBJID::MONSTER, RoomNum);
		Obj->Set_MonsterID(MonsterNum);
		Obj->Set_RenderID(RENDERID::OBJECT);
		break;
	case 2:
		Obj = CAbstractFactory<CRedGunDead>::Create(fX, fY, OBJID::MONSTER, RoomNum);
		Obj->Set_MonsterID(MonsterNum);
		Obj->Set_RenderID(RENDERID::OBJECT);
		break;
	case 3:
		Obj = CAbstractFactory<CBlueGunDead>::Create(fX, fY, OBJID::MONSTER, RoomNum);
		Obj->Set_MonsterID(MonsterNum);
		Obj->Set_RenderID(RENDERID::OBJECT);
		break;
	case 4:
		Obj = CAbstractFactory<CMage>::Create(fX, fY, OBJID::MONSTER, RoomNum);
		Obj->Set_MonsterID(MonsterNum);
		Obj->Set_RenderID(RENDERID::OBJECT);
		break;
	case 5:
		Obj = CAbstractFactory<CKnight>::Create(fX, fY, OBJID::MONSTER, RoomNum);
		Obj->Set_MonsterID(MonsterNum);
		Obj->Set_RenderID(RENDERID::OBJECT);
		break;
	case 6:
		Obj = CAbstractFactory<CGalme>::Create(fX, fY, OBJID::MONSTER, RoomNum);
		Obj->Set_MonsterID(MonsterNum);
		Obj->Set_RenderID(RENDERID::OBJECT);
		break;
	}
	m_listObj[OBJID::MONSTER].emplace_back(Obj);
}

void CObjMgr::Save_Monster()
{
	HANDLE hFile = CreateFile(L"../Data/Monster.dat", GENERIC_WRITE
		, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"저장 실패", L"실패", MB_OK);
		return;
	}

	DWORD dwByte = 0;

	for (auto& pObj : m_listObj[OBJID::MONSTER])
	{
		WriteFile(hFile, &pObj->Get_Info(), sizeof(INFO), &dwByte, NULL);
		WriteFile(hFile, &pObj->Get_RoomNum(), sizeof(int), &dwByte, NULL);

		WriteFile(hFile, &pObj->Get_MonsterID(), sizeof(int), &dwByte, NULL);
	}
	CloseHandle(hFile);
	//MessageBox(g_hWnd, L"저장 성공", L"성공", MB_OK);
}

void CObjMgr::Load_Monster()
{
	HANDLE hFile = CreateFile(L"../Data/Monster.dat", GENERIC_READ
		, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"불러오기 실패!", L"실패", MB_OK);
		return;
	}

	Release();

	DWORD	dwByte = 0;
	INFO	tTemp = {};
	int		iMonsterID = 0;

	int		iRoomNum = 0;
	CObj* Obj = nullptr;

	while (true)
	{
		ReadFile(hFile, &tTemp, sizeof(INFO), &dwByte, NULL);
		ReadFile(hFile, &iRoomNum, sizeof(int), &dwByte, NULL);
		ReadFile(hFile, &iMonsterID, sizeof(int), &dwByte, NULL);
		if (0 == dwByte)
			break;

		switch (iMonsterID)
		{
		case 1:
			Obj = CAbstractFactory<CGunDead>::Create(tTemp.fX, tTemp.fY, OBJID::MONSTER, iRoomNum);
			Obj->Set_RenderID(RENDERID::OBJECT);
			m_listObj[OBJID::MONSTER].emplace_back(Obj);
			break;
		case 2:
			Obj = CAbstractFactory<CRedGunDead>::Create(tTemp.fX, tTemp.fY, OBJID::MONSTER, iRoomNum);
			Obj->Set_RenderID(RENDERID::OBJECT);
			m_listObj[OBJID::MONSTER].emplace_back(Obj);
			break;
		case 3:
			Obj = CAbstractFactory<CBlueGunDead>::Create(tTemp.fX, tTemp.fY, OBJID::MONSTER, iRoomNum);
			Obj->Set_RenderID(RENDERID::OBJECT);
			m_listObj[OBJID::MONSTER].emplace_back(Obj);
			break;
		case 4:
			Obj = CAbstractFactory<CMage>::Create(tTemp.fX, tTemp.fY, OBJID::MONSTER, iRoomNum);
			Obj->Set_RenderID(RENDERID::OBJECT);
			m_listObj[OBJID::MONSTER].emplace_back(Obj);
			break;
		case 5:
			Obj = CAbstractFactory<CKnight>::Create(tTemp.fX, tTemp.fY, OBJID::MONSTER, iRoomNum);
			Obj->Set_RenderID(RENDERID::OBJECT);
			m_listObj[OBJID::MONSTER].emplace_back(Obj);
			break;
		case 6:
			Obj = CAbstractFactory<CGalme>::Create(tTemp.fX, tTemp.fY, OBJID::MONSTER, iRoomNum);
			Obj->Set_RenderID(RENDERID::OBJECT);
			m_listObj[OBJID::MONSTER].emplace_back(Obj);			
			break;
		}
	}

	CloseHandle(hFile);
	//MessageBox(g_hWnd, L"불러오기 성공!", L"성공", MB_OK);
}


#include "stdafx.h"
#include "MyEdit.h"
#include "BmpMgr.h"
#include "TileMgr.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
#include "Tile.h"
#include "ObjMgr.h"


#include "GunDead.h"
#include "RedGunDead.h"
#include "BlueGunDead.h"
#include "Galme.h"
#include "Mage.h"
#include "Knight.h"


CMyEdit::CMyEdit()
	:m_iRoomNum(0), m_iTileX(0), m_iTileY(0)
	, m_iScreenCX(0),m_iScreenCY(0), m_bColTile(false)
	, m_bScrollOn(false), KeyOn(false),Monster(L""), m_bMonster(false)
	,m_fMonsterX(0.f),m_fMonsterY(0.f),m_iMonsterNum(0), m_bMonsterEdit(false)
{
	m_vecTileEdit.reserve(11 * 6);
	ZeroMemory(&m_ptDrawID,sizeof(m_ptDrawID));
	ZeroMemory(&m_tPos1, sizeof(m_tPos1));
	ZeroMemory(&m_tPos2, sizeof(m_tPos2));

}


CMyEdit::~CMyEdit()
{
	Release();
}

void CMyEdit::Initialize()
{
	CTileMgr::Get_Instance()->Load_Tile();
	

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tile/Tile.bmp", L"Tile");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Map.bmp", L"Map");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BackGround.bmp", L"BackGround");
	
	//건데드
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/GunDead/GunDead_Up_Left.bmp", L"GunDead_Up_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/GunDead/GunDead_Down_Left.bmp", L"GunDead_Down_Left");

	//레드건데드
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/RedGunDead/RedGunDead_Up_Left.bmp", L"RedGunDead_Up_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/RedGunDead/RedGunDead_Down_Left.bmp", L"RedGunDead_Down_Left");

	//블루건데드
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/BlueGunDead/BlueGunDead_Up_Left.bmp", L"BlueGunDead_Up_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/BlueGunDead/BlueGunDead_Down_Left.bmp", L"BlueGunDead_Down_Left");

	//마법사
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Mage/Mage_Down_Left.bmp", L"Mage_Down_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Mage/Mage_Up_Left.bmp", L"Mage_Up_Left");




	//새
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Bird/Bird.bmp", L"Bird");

	//책
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Book/Book.bmp", L"Book");

	//기사
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Knight/Knight_Down.bmp", L"Knight_Down");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Knight/Knight_Up.bmp", L"Knight_Up");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Knight/Knight_Down_Left.bmp", L"Knight_Down_Left");

	//총탄박쥐
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/BulletBat/BulletBat.bmp", L"BulletBat");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/BulletBat/ShotBat.bmp", L"ShotBat");


	//핀헤드
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/PinHead/PinHead_Down.bmp", L"PinHead_Down");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/PinHead/PinHead_Up.bmp", L"PinHead_Up");


	//갈매기관총
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Boss_Galmea/Boss_Left.bmp", L"Galmea_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Boss_Galmea/Boss_Down_Left.bmp", L"Galmea_Down_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Boss_Galmea/Boss_Up_Left.bmp", L"Galmea_Up_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Boss_Galmea/Boss_Up.bmp", L"Galmea_Up");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Boss_Galmea/Boss_Down.bmp", L"Galmea_Down");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Boss_Galmea/Boss_Pattern.bmp", L"Galmea_Pattern");

	m_iTileX = 11;
	m_iTileY = 6;
	m_iScreenCX = 144;
	m_iScreenCY = 144;

	for (int i = 0; i < m_iTileY; ++i)
	{
		for (int j = 0; j < m_iTileX; ++j)
		{
			float fX = (float)((TILECX >> 1) + j*TILECX);
			float fY = (float)((TILECY >> 1) + i*TILECY);
			m_ptDrawID.x = j;
			m_ptDrawID.y = i;

			m_vecTileEdit.emplace_back(Create_Tile(fX, fY, m_ptDrawID));
		}
	}
	CTileMgr::Get_Instance()->Initialize();
}

void CMyEdit::Update()
{
	if (CKeyMgr::Get_Instance()->Key_Press(VK_LEFT))
		CScrollMgr::Get_Instance()->Set_ScrollX(30.f);
	if (CKeyMgr::Get_Instance()->Key_Press(VK_RIGHT))
		CScrollMgr::Get_Instance()->Set_ScrollX(-30.f);
	if (CKeyMgr::Get_Instance()->Key_Press(VK_UP))
		CScrollMgr::Get_Instance()->Set_ScrollY(30.f);
	if (CKeyMgr::Get_Instance()->Key_Press(VK_DOWN))
		CScrollMgr::Get_Instance()->Set_ScrollY(-30.f);



	if (CKeyMgr::Get_Instance()->Key_Down(VK_NUMPAD4))
		CScrollMgr::Get_Instance()->Set_EditScrollX(36.f);
	if (CKeyMgr::Get_Instance()->Key_Down(VK_NUMPAD6))
		CScrollMgr::Get_Instance()->Set_EditScrollX(-36.f);
	if (CKeyMgr::Get_Instance()->Key_Down(VK_NUMPAD8))
		CScrollMgr::Get_Instance()->Set_EditScrollY(36.f);
	if (CKeyMgr::Get_Instance()->Key_Down(VK_NUMPAD5))
		CScrollMgr::Get_Instance()->Set_EditScrollY(-36.f);


	if (CKeyMgr::Get_Instance()->Key_Down(VK_ONE))
	{
		m_iRoomNum = 1;
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_TWO))
	{
		m_iRoomNum = 2;
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_THREE))
	{
		m_iRoomNum = 3;
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_FOUR))
	{
		m_iRoomNum = 4;
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_FIVE))
	{
		m_iRoomNum = 5;
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_SIX))
	{
		m_iRoomNum = 6;
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_SEVEN))
	{
		m_iRoomNum = 7;
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_EIGHT))
	{
		m_iRoomNum = 8;
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_NINE))
	{
		m_iRoomNum = 9;
	}
	if (CKeyMgr::Get_Instance()->Key_Down('Q'))
	{
		m_iRoomNum = 10;
	}
	if (CKeyMgr::Get_Instance()->Key_Down('W'))
	{
		m_iRoomNum = 11;
	}
	if (CKeyMgr::Get_Instance()->Key_Down('E'))
	{
		m_iRoomNum = 12;
	}
	if (CKeyMgr::Get_Instance()->Key_Down('R'))
	{
		m_iRoomNum = 13;
	}
	if (CKeyMgr::Get_Instance()->Key_Down('T'))
	{
		m_iRoomNum = 14;
	}


	if (CKeyMgr::Get_Instance()->Key_Down('A'))
	{
		m_iMonsterNum = 1;
		swprintf_s(Monster, L"GunDead ");	

	}
	if (CKeyMgr::Get_Instance()->Key_Down('S'))
	{
		m_iMonsterNum = 2;

		swprintf_s(Monster, L"CRedGunDead ");

	}
	if (CKeyMgr::Get_Instance()->Key_Down('D'))
	{
		m_iMonsterNum = 3;
		swprintf_s(Monster, L"CBlueGunDead ");

	}
	if (CKeyMgr::Get_Instance()->Key_Down('F'))
	{
		m_iMonsterNum = 4;

		swprintf_s(Monster, L"CMage ");

	}
	if (CKeyMgr::Get_Instance()->Key_Down('G'))
	{
		m_iMonsterNum = 5;
		swprintf_s(Monster, L"Cknight ");

	}
	if (CKeyMgr::Get_Instance()->Key_Down('H'))
	{
		m_iMonsterNum = 6;
		swprintf_s(Monster, L"CGalme ");
	}

	if (CKeyMgr::Get_Instance()->Key_Down('V'))
	{
		m_bScrollOn = !m_bScrollOn;
	}
	if (CKeyMgr::Get_Instance()->Key_Down('C'))
	{
		m_bColTile = !m_bColTile;
	}
	if (CKeyMgr::Get_Instance()->Key_Down('X'))
	{
		m_iRoomNum = 0;
	}

	if (!m_bMonsterEdit)
	{
		if (!m_bScrollOn)
		{
			if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
			{
				CTileMgr::Get_Instance()->Picking_Tile(m_ptDrawID, m_bColTile, m_iRoomNum);
			}
		}
		else
		{
			if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
			{
				GetCursorPos(&m_tPos1);
				ScreenToClient(g_hWnd, &m_tPos1);
				m_tPos1.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
				m_tPos1.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();
			}
		}

		if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
		{
			m_ptDrawID = {};
			GetCursorPos(&m_ptDrawID);
			ScreenToClient(g_hWnd, &m_ptDrawID);

			m_ptDrawID.x -= (int)CScrollMgr::Get_Instance()->Get_EditScrollX();
			m_ptDrawID.y -= (int)CScrollMgr::Get_Instance()->Get_EditScrollY();

			m_ptDrawID.x = m_ptDrawID.x / TILECX;
			m_ptDrawID.y = m_ptDrawID.y / TILECY;

			Create_Tile((float)m_ptDrawID.x, (float)m_ptDrawID.y, m_ptDrawID);
		}
		if (CKeyMgr::Get_Instance()->Key_Down('B'))
		{
			if (abs(m_tPos1.y - m_tPos2.y) < abs(m_tPos1.x - m_tPos2.x))
			{
				for (int i = (int)m_tPos1.x; i <= (int)m_tPos2.x; i++)
				{
					POINT pt = {};
					pt.x = i;
					pt.y = m_tPos2.y;
					CTileMgr::Get_Instance()->Draw_Tile(pt, m_ptDrawID, m_bColTile, m_iRoomNum);
				}
			}
			else
			{
				int j = 0;
				for (int i = (int)m_tPos1.y; i <= (int)m_tPos2.y; i++)
				{
					POINT pt = {};
					pt.x = m_tPos2.x;
					pt.y = i;
					CTileMgr::Get_Instance()->Draw_Tile(pt, m_ptDrawID, m_bColTile, m_iRoomNum);
				}
			}
		}
	}
	else
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
		{
			GetCursorPos(&m_tPos1);
			ScreenToClient(g_hWnd, &m_tPos1);
			m_tPos1.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
			m_tPos1.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();
			CObjMgr::Get_Instance()->Create_Monster((float)m_tPos1.x, (float)m_tPos1.y, m_iRoomNum, m_iMonsterNum);

		}
	}
		


	if (CKeyMgr::Get_Instance()->Key_Down(VK_NUMPAD0))
	{
		CTileMgr::Get_Instance()->Delete_Tile();
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_NUMPAD1))
	{
		CObjMgr::Get_Instance()->Pop_Monster();
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_NUMPAD2))
	{
		m_bMonsterEdit = !m_bMonsterEdit;
		CObjMgr::Get_Instance()->Set_Edit();
	}
	if (CKeyMgr::Get_Instance()->Key_Down('K'))
		CTileMgr::Get_Instance()->Save_Tile();
	if (CKeyMgr::Get_Instance()->Key_Down('L'))
		CTileMgr::Get_Instance()->Load_Tile();

	if (CKeyMgr::Get_Instance()->Key_Down('O'))
		CObjMgr::Get_Instance()->Save_Monster();
	if (CKeyMgr::Get_Instance()->Key_Down('P'))
		CObjMgr::Get_Instance()->Load_Monster();

}

void CMyEdit::Late_Update()
{
}

void CMyEdit::Render(HDC _DC)
{
	
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	int iEditScrollX = (int)CScrollMgr::Get_Instance()->Get_EditScrollX();
	int iEditScrollY = (int)CScrollMgr::Get_Instance()->Get_EditScrollY();

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Map");
	//HDC hBackDC = CBmpMgr::Get_Instance()->Find_Bmp(L"BackGround");

	BitBlt(_DC, 0, 0, WINCX, WINCY, hMemDC, -iScrollX, -iScrollY, SRCCOPY);
	CTileMgr::Get_Instance()->Render(_DC);
	if(m_bMonsterEdit)
		CObjMgr::Get_Instance()->Render(_DC);

	//BitBlt(_DC, 0, 0, WINCX, WINCY, hMemDC, -iScrollX, -iScrollY, SRCCOPY);
	
	int iCullX = abs(iEditScrollX /TILECX);
	int iCullY = abs(iEditScrollY /TILECY);

	int iCullEndX = iCullX + (m_iScreenCX / TILECX) + 2;
	int iCullEndY = iCullY + (m_iScreenCY / TILECY) + 2;

	for (int i = iCullY; i < iCullEndY; i++)
	{
		for (int j = iCullX; j < iCullEndX; j++)
		{
			int iIdx = i*m_iTileX + j;
			if (0 > iIdx || m_vecTileEdit.size() <= (size_t)iIdx)
				continue;

			m_vecTileEdit[iIdx]->Render(_DC);
		}
	}
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	TCHAR szBuff1[50] = L"";
	TCHAR szBuff2[50] = L"";

	swprintf_s(szBuff1, L"x : %d", (int)pt.x);
	swprintf_s(szBuff2, L"y : %d", (int)pt.y);
	TextOut(_DC, 100, 100, szBuff1, lstrlen(szBuff1));
	TextOut(_DC, 100, 130, szBuff2, lstrlen(szBuff2));

	TCHAR szBuff3[50] = L"";
	swprintf_s(szBuff3, L"ColTile : %d", m_bColTile);
	TextOut(_DC, 100, 150, szBuff3, lstrlen(szBuff3));

	TCHAR szBuff4[50] = L"";
	swprintf_s(szBuff4, L"RoomNum : %d", m_iRoomNum);
	TextOut(_DC, 100, 170, szBuff4, lstrlen(szBuff4));

	TCHAR szBuff5[50] = L"";
	swprintf_s(szBuff5, L"m_bScrollOn : %d", m_bScrollOn);
	TextOut(_DC, 100, 190, szBuff5, lstrlen(szBuff5));

	TextOut(_DC, 100, 210, Monster, lstrlen(Monster));

	TCHAR szBuff6[50] = L"";
	swprintf_s(szBuff6, L"m_bScro llOn : %d", m_bMonster);
	TextOut(_DC, 100, 230, szBuff6, lstrlen(szBuff6));

	TCHAR szBuff7[50] = L"";
	swprintf_s(szBuff7, L"m_bMonsterEdir : %d", m_bMonsterEdit);
	TextOut(_DC, 100, 250, szBuff7, lstrlen(szBuff7));

}

void CMyEdit::Release()
{
	for_each(m_vecTileEdit.begin(), m_vecTileEdit.end(), Safe_Delete<CObj*>);
	m_vecTileEdit.clear();
}



CObj* CMyEdit::Create_Tile(float _x, float _y,POINT _pt)
{
	CObj* pTile = new CTile;
	pTile->Initialize();
	pTile->Set_Pos(_x, _y);
	pTile->Set_DrawID(_pt);
	pTile->Set_Summon(true);
	static_cast<CTile*>(pTile)->Set_Edit();
	return pTile;
}

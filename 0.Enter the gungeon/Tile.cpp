#include "stdafx.h"
#include "Tile.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CTile::CTile()
	: m_bEdit(false)
{
	ZeroMemory(&m_ptDrawID, sizeof(m_ptDrawID));
}

CTile::~CTile()
{
	Release();
}

void CTile::Initialize()
{
	m_tInfo.iCX = TILECX;
	m_tInfo.iCY = TILECY;

	m_tColInfo.iCX = TILECX;
	m_tColInfo.iCY = TILECX;

	m_bColRect = false;

	m_eRenderID = RENDERID::BACKGROUND;
}

void CTile::Render(HDC _DC)
{
	if (m_bSummon)
	{
		Update_Rect();
		Update_ColRect();
		int	iScrollX;
		int	iScrollY;

		if (!m_bEdit)
		{
			iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
			iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
		}
		else if (m_bEdit)
		{
			iScrollX = (int)CScrollMgr::Get_Instance()->Get_EditScrollX();
			iScrollY = (int)CScrollMgr::Get_Instance()->Get_EditScrollY();
		}
		HDC hMemDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Tile");

		BitBlt(_DC, m_tRect.left + iScrollX+7, m_tRect.top -13+ iScrollY, m_tInfo.iCX, m_tInfo.iCY
			, hMemDC, m_ptDrawID.x * TILECX, m_ptDrawID.y * TILECY, SRCCOPY);

		DrawColRect(_DC);
	}

}
void CTile::DrawColRect(HDC _DC)
{
	m_tColInfo.fX = (m_tInfo.fX)+ (float)(CScrollMgr::Get_Instance()->Get_ScrollX())+7;
	m_tColInfo.fY = (m_tInfo.fY)+ (float)(CScrollMgr::Get_Instance()->Get_ScrollY())-13;

	if (m_bColRect)
	{
		float fX = (m_tInfo.fX) - (m_tColInfo.iCX >> 1)+7 + (float)(CScrollMgr::Get_Instance()->Get_ScrollX());
		float fY = (m_tInfo.fY) - (m_tColInfo.iCX >> 1)-13+ (float)(CScrollMgr::Get_Instance()->Get_ScrollY());
	}
}

void CTile::Release()
{
}

int CTile::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	return OBJ_NOEVENT;
}

void CTile::Late_Update()
{
}

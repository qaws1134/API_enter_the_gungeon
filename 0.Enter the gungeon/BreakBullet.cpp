#include "stdafx.h"
#include "BreakBullet.h"
#include "Bullet.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
CBreakBullet::CBreakBullet() : m_iBreakTime(0),m_dwTime(GetTickCount())
{
}


CBreakBullet::~CBreakBullet()
{
}

void CBreakBullet::Initialize()
{
	m_iBreakTime = 3000;

	m_iFrameSize = 100;
	m_tColInfo.iCX = 90;
	m_tColInfo.iCY = 90;



	m_tFrame.iStartX = 0;
	m_tFrame.iStateY = 0;


	m_tInfo.iCX = m_iFrameSize;
	m_tInfo.iCY = m_iFrameSize;
	m_eRenderID = RENDERID::OBJECT;



	m_tColInfo.fX = m_tInfo.fX;
	m_tColInfo.fY = m_tInfo.fY;


}

int CBreakBullet::Update()
{
	if (m_bDead)
	{
		m_tPosin.x = (LONG)m_tColInfo.fX;
		m_tPosin.y = (LONG)m_tColInfo.fY;
		CreateXWayBullet<CBullet>(360.f, 15, 1, 4.f, L"M_BossBullet", OBJID::M_BULLET,m_tInfo);
		return OBJ_DEAD;
	}

	m_tInfo.fX += cosf(m_fAngle*PI / 180)*m_fSpeed;
	m_tInfo.fY -= sinf(m_fAngle*PI / 180)*m_fSpeed;

	Update_Rect();
	Update_ColRect();

	if (m_dwTime + m_iBreakTime < GetTickCount())
	{
		m_bDead = true;
	}
	
	return OBJ_NOEVENT;
}


void CBreakBullet::Late_Update()
{
}

void CBreakBullet::Render(HDC _DC)
{
	Update_Rect();
	Update_ColRect();
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	hMemDC = CBmpMgr::Get_Instance()->Find_Bmp(m_pFrameKey);

	int ioffsetX = 0;
	if (m_bRightRev)
		ioffsetX = -17;
	else
		ioffsetX = 17;

	GdiTransparentBlt(_DC
		, m_tRect.left + ioffsetX + iScrollX, m_tRect.top + 10 + iScrollY
		, m_tInfo.iCX, m_tInfo.iCY
		, hMemDC
		, 0, 0
		, m_iFrameSize, m_iFrameSize
		, RGB(255, 0, 255));


	DrawColRect(_DC);
}

void CBreakBullet::Release()
{
}

void CBreakBullet::DrawColRect(HDC _DC)
{
	int ioffsetX = 0;
	if (m_bRightRev)
		ioffsetX = -17;
	else
		ioffsetX = 17;

	//Ellipse(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	m_tColInfo.fX = (m_tInfo.fX) + ioffsetX + (float)(CScrollMgr::Get_Instance()->Get_ScrollX());
	m_tColInfo.fY = (m_tInfo.fY) + 10 + (float)(CScrollMgr::Get_Instance()->Get_ScrollY());

	if (m_bColRect)
	{
		HPEN hNewPen = CreatePen(PS_SOLID, 2, 0x00ff0000);
		float fX = (m_tInfo.fX) - (m_tColInfo.iCX >> 1) + ioffsetX + (float)(CScrollMgr::Get_Instance()->Get_ScrollX());
		float fY = (m_tInfo.fY) - (m_tColInfo.iCX >> 1) + 10 + (float)(CScrollMgr::Get_Instance()->Get_ScrollY());

		MoveToEx(_DC, (int)fX, (int)fY, false);

		LineTo(_DC, (int)fX + m_tColInfo.iCX, (int)fY);

		LineTo(_DC, (int)fX + m_tColInfo.iCX, (int)fY + m_tColInfo.iCY);
		LineTo(_DC, (int)fX, (int)fY + m_tColInfo.iCY);
		LineTo(_DC, (int)fX, (int)fY);


		MoveToEx(_DC, (int)fX, (int)fY, false);
		LineTo(_DC, (int)fX + m_tColInfo.iCX, (int)fY + m_tColInfo.iCY);


		MoveToEx(_DC, (int)fX, (int)fY, false);

		MoveToEx(_DC, (int)fX + m_tColInfo.iCX, (int)fY, false);
		LineTo(_DC, (int)fX, (int)fY + m_tColInfo.iCY);
		DeleteObject(SelectObject(_DC, hNewPen));
	}

}
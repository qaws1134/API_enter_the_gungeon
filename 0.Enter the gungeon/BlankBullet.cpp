#include "stdafx.h"
#include "BlankBullet.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
CBlankBullet::CBlankBullet()
{
}


CBlankBullet::~CBlankBullet()
{
	Release();
}

void CBlankBullet::Initialize()
{

	m_iFrameSize = 540;
	m_tInfo.iCX = m_iFrameSize;
	m_tInfo.iCY = m_iFrameSize;
	m_tColInfo.iCX = m_iFrameSize+100;
	m_tColInfo.iCY = m_iFrameSize+100;

	//dwTime = GetTickCount();
	m_eRenderID = RENDERID::EFFECT;

	m_tFrame.iStartX = 0;
	m_tFrame.iStateY = 0;
	m_tFrame.dwDelay = 10;
	m_tFrame.iEndX = 15;
	m_tFrame.dwTime = GetTickCount();
	m_pFrameKey = L"BlankShot";
}

int CBlankBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	Update_Frame();
	Update_Rect();
	Update_ColRect();
	return OBJ_NOEVENT;
}

void CBlankBullet::Late_Update()
{
	m_tColInfo.fX = (m_tInfo.fX) + (float)(CScrollMgr::Get_Instance()->Get_ScrollX());
	m_tColInfo.fY = (m_tInfo.fY) + (float)(CScrollMgr::Get_Instance()->Get_ScrollY());

}

void CBlankBullet::Render(HDC _DC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	//Ellipse(_DC, m_tColRect.left, m_tColRect.top, m_tColRect.right, m_tColRect.bottom);


	hMemDC = CBmpMgr::Get_Instance()->Find_Bmp(m_pFrameKey);

	GdiTransparentBlt(_DC
		, m_tRect.left + iScrollX, m_tRect.top + iScrollY
		, m_tInfo.iCX, m_tInfo.iCY
		, hMemDC
		, m_tFrame.iStartX * m_iFrameSize, m_tFrame.iStateY * m_iFrameSize
		, m_iFrameSize, m_iFrameSize
		, RGB(255, 0, 255));

	DrawColRect(_DC);

}

void CBlankBullet::Release()
{
}

void CBlankBullet::Update_Frame()
{
	if (m_tFrame.dwTime + m_tFrame.dwDelay < GetTickCount())
	{
		++m_tFrame.iStartX;

		if (m_tFrame.iStartX >= m_tFrame.iEndX)
		{
			Set_Dead();
		}
		m_tFrame.dwTime = GetTickCount();
	}
}

#include "stdafx.h"
#include "ShieldBullet.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
CShieldBullet::CShieldBullet()
{
}


CShieldBullet::~CShieldBullet()
{
	Release();
}

void CShieldBullet::Initialize()
{
	
	if (!lstrcmp(L"M_Normal", m_pFrameKey))
	{
		m_iFrameSize = 40;
		m_tColInfo.iCX = 25;
		m_tColInfo.iCY = 25;
	}
	if (!lstrcmp(L"M_BossBullet", m_pFrameKey))
	{
		m_iFrameSize = 30;
		m_tColInfo.iCX = 30;
		m_tColInfo.iCY = 30;
	}
	m_tFrame.iStartX = 0;
	m_tFrame.iStateY = 0;

	m_tStat.iAtt = 1;
	m_tInfo.fX = m_pTarget->Get_Info().fX;
	m_tInfo.fY = m_pTarget->Get_Info().fY;


	m_tInfo.iCX = m_iFrameSize;
	m_tInfo.iCY = m_iFrameSize;
	m_eRenderID = RENDERID::OBJECT;

	m_tColInfo.fX = m_tInfo.fX;
	m_tColInfo.fY = m_tInfo.fY;
	
	m_fSpeed = 5.f;

	m_fDis = 100.f;
}

int CShieldBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_tInfo.fX = m_pTarget->Get_Info().fX + cosf(m_fAngle * PI / 180.f) * m_fDis;
	m_tInfo.fY = m_pTarget->Get_Info().fY - sinf(m_fAngle * PI / 180.f) * m_fDis;

	m_fAngle += m_fSpeed;

	Update_Rect();
	Update_ColRect();
	

	return OBJ_NOEVENT;
}

void CShieldBullet::Late_Update()
{
	m_tColInfo.fX = (m_tInfo.fX) + (float)(CScrollMgr::Get_Instance()->Get_ScrollX());
	m_tColInfo.fY = (m_tInfo.fY) + (float)(CScrollMgr::Get_Instance()->Get_ScrollY());
	if (m_tColInfo.fX< -500
		|| m_tColInfo.fX >(WINCX + 500)
		|| m_tColInfo.fY < -500
		|| m_tColInfo.fY >(WINCY + 500))
		m_bDead = true;
}

void CShieldBullet::Render(HDC _DC)
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

void CShieldBullet::Release()
{
}


void CShieldBullet::DrawColRect(HDC _DC)
{
	int ioffsetX = 0;
	if (m_bRightRev)
		ioffsetX = -17;
	else
		ioffsetX = 17;
	m_tColInfo.fX = (m_tInfo.fX) + ioffsetX + (float)(CScrollMgr::Get_Instance()->Get_ScrollX());
	m_tColInfo.fY = (m_tInfo.fY) + 10 + (float)(CScrollMgr::Get_Instance()->Get_ScrollY());



}
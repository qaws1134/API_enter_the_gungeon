#include "stdafx.h"
#include "ChargeEffect.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
CChargeEffect::CChargeEffect()
{
}


CChargeEffect::~CChargeEffect()
{
	Release();
}

void CChargeEffect::Initialize()
{
	m_iFrameSize = 300;
	m_tInfo.iCX = m_iFrameSize;
	m_tInfo.iCY = m_iFrameSize;
	m_eRenderID = RENDERID::EFFECT;
	m_pFrameKey = L"Galmea_Pattern";
	m_tFrame.iStartX = 0;
	m_tFrame.iEndX = 9;
	m_tFrame.iStateY = 5;
	m_tFrame.dwDelay = 50;
	m_tFrame.dwTime = GetTickCount();
}

int CChargeEffect::Update()
{
	if (m_bDead)
		return OBJ_DEAD;


		Bullet_AngleState();
		Update_Rect();
		Update_Frame();
//	}
	return OBJ_NOEVENT;
}

void CChargeEffect::Late_Update()
{
}

void CChargeEffect::Update_Frame()
{
	if (m_tFrame.dwTime + m_tFrame.dwDelay < GetTickCount())
	{

		if (m_tFrame.iStartX >= m_tFrame.iEndX)
		{
			m_tFrame.iStartX = m_tFrame.iEndX - 1;
			m_bDead = true;
		}
		else
		{
			++m_tFrame.iStartX;
		}
		m_tFrame.dwTime = GetTickCount();
	}
}

void CChargeEffect::Render(HDC _DC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	hMemDC = CBmpMgr::Get_Instance()->Find_Bmp(m_pFrameKey);
	int ioffsetX = 0;
	if (m_bRightRev)
		ioffsetX = -17;
	else
		ioffsetX = 20;

	GdiTransparentBlt(_DC
		, m_tRect.left+ ioffsetX + iScrollX, m_tRect.top+30 + iScrollY
		, m_tInfo.iCX, m_tInfo.iCY
		, hMemDC
		, m_tFrame.iStartX * m_iFrameSize, m_tFrame.iStateY * m_iFrameSize
		, m_iFrameSize, m_iFrameSize
		, RGB(255, 0, 255));

}

void CChargeEffect::Release()
{
}
void CChargeEffect::Bullet_AngleState()
{
	if (m_fAngle < 0)
	{
		if (m_fAngle > -90.f)
			m_bRightRev = false;
		else if (m_fAngle > -180.f)
			m_bRightRev = true;
	}
	else
	{
		if (m_fAngle < 90.f)
			m_bRightRev = false;
		else if (m_fAngle < 180.f)
			m_bRightRev = true;
	}
}
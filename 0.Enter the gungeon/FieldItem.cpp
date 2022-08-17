#include "stdafx.h"
#include "FieldItem.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"

CFieldItem::CFieldItem() :m_bFollow(false)
{
}


CFieldItem::~CFieldItem()
{
	Release();
}

void CFieldItem::Initialize()
{
	m_iFrameSize = 50;

	m_tColInfo.fX = m_tInfo.fX;
	m_tColInfo.fY = m_tInfo.fY;
	m_tColInfo.iCX = 40;
	m_tColInfo.iCY = 40;


	m_tInfo.iCX = m_iFrameSize;
	m_tInfo.iCY = m_iFrameSize;
	m_eRenderID = RENDERID::OBJECT;
	m_pFrameKey = L"FieldItem";
	InitState();
}

int CFieldItem::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	m_pTarget = CObjMgr::Get_Instance()->Get_Player();

	if(m_bFollow)
		Follow();


	return OBJ_NOEVENT;
}

void CFieldItem::Late_Update()
{
}

void CFieldItem::Render(HDC _DC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	//렉트비교

	RECT rc = {};

	if (IntersectRect(&rc, &m_pTarget->Get_ColRect(), &m_tColRect))
	{
		
	}
	hMemDC = CBmpMgr::Get_Instance()->Find_Bmp(m_pFrameKey);


	GdiTransparentBlt(_DC
		, m_tRect.left + iScrollX, m_tRect.top + iScrollY
		, m_tInfo.iCX, m_tInfo.iCY
		, hMemDC
		, m_tFrame.iStartX * m_iFrameSize, m_tFrame.iStateY * m_iFrameSize
		, m_iFrameSize, m_iFrameSize
		, RGB(255, 0, 255));

}

void CFieldItem::Release()
{
}


void CFieldItem::Follow()
{
	m_pTarget = CObjMgr::Get_Instance()->Get_Player();

	if (!m_pTarget)
		return;

	float fX = m_pTarget->Get_Info().fX - m_tInfo.fX;
	float fY = m_pTarget->Get_Info().fY - m_tInfo.fY;
	float fDia = sqrtf(fX * fX + fY * fY);

	float	fRad = acosf(fX / fDia);

	m_fAngle = fRad * 180.f / PI;

	if (m_tInfo.fY < m_pTarget->Get_Info().fY)
		m_fAngle *= -1.f;

	m_tInfo.fX += cosf(m_fAngle*PI / 180.f);
	m_tInfo.fY -= sinf(m_fAngle*PI / 180.f);
}



void CFieldItem::InitState()
{
	switch (m_eCurState)
	{
	case GOLD:
		m_tFrame.iStartX = 0;
		m_tFrame.iEndX = 8;
		m_tFrame.iStateY = GOLD;
		m_tFrame.dwDelay = 300;
		m_tStat.iGold = rand() % 9 + 1;
		m_bFollow = true;
		m_tFrame.dwTime = GetTickCount();
		break;
	case HEALTH:
		m_tFrame.iStartX = 0;
		m_tFrame.iEndX = 4;
		m_tFrame.iStateY = HEALTH;
		m_tFrame.dwDelay = 300;
		m_tStat.iHp = 2;
		m_tFrame.dwTime = GetTickCount();
		break;
	case H_HEALTH:
		m_tFrame.iStartX = 0;
		m_tFrame.iEndX = 3;
		m_tFrame.iStateY = H_HEALTH;
		m_tFrame.dwDelay = 80;
		m_tFrame.dwTime = GetTickCount();
		break;
	case ARMO:
		m_tFrame.iStartX = 0;
		m_tFrame.iEndX = 5;
		m_tFrame.iStateY = ARMO;
		m_tFrame.dwDelay = 300;
		m_tFrame.dwTime = GetTickCount();
		break;
	case KEY:
		m_tFrame.iStartX = 0;
		m_tFrame.iEndX = 5;
		m_tFrame.iStateY = KEY;
		m_tFrame.dwDelay = 300;
		m_tFrame.dwTime = GetTickCount();
		break;
	}
}

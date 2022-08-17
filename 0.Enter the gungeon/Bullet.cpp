#include "stdafx.h"
#include "Bullet.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
CBullet::CBullet()
{
}


CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize()
{
	if (!lstrcmp(L"Normal", m_pFrameKey))
	{
		m_iFrameSize = 24;
		m_tColInfo.iCX = 20;
		m_tColInfo.iCY = 20;

	}
	if (!lstrcmp(L"BowBullet", m_pFrameKey))
	{
		m_iFrameSize = 57;
		m_tColInfo.iCX = 20;
		m_tColInfo.iCY = 20;

	}
	if (!lstrcmp(L"M_Normal", m_pFrameKey))
	{
		m_iFrameSize = 40;
		m_tColInfo.iCX = 25;
		m_tColInfo.iCY = 25;
	}

	if (!lstrcmp(L"M_BigBullet", m_pFrameKey))
	{
		m_iFrameSize = 100;
		m_tColInfo.iCX = 90;
		m_tColInfo.iCY = 90;
	}
	if (!lstrcmp(L"M_BossBullet", m_pFrameKey))
	{
		m_iFrameSize = 30;
		m_tColInfo.iCX = 30;
		m_tColInfo.iCY = 30;
	}
	m_tFrame.iStartX = 0;
	m_tFrame.iStateY = 0;

	
	m_tInfo.iCX = m_iFrameSize;
	m_tInfo.iCY = m_iFrameSize;
	m_eRenderID = RENDERID::OBJECT;


	m_tColInfo.fX = m_tInfo.fX;
	m_tColInfo.fY = m_tInfo.fY;


}

int CBullet::Update()
{
	if (m_bDead)
	{
		return OBJ_DEAD;
	}

	m_tInfo.fX += cosf(m_fAngle*PI / 180)*m_fSpeed;
	m_tInfo.fY -= sinf(m_fAngle*PI / 180)*m_fSpeed;
	Bullet_AngleState();

	Update_Rect();
	Update_ColRect();
	return OBJ_NOEVENT;
}

void CBullet::Late_Update()
{

	float fX = (float)(m_tInfo.iCX >> 1);
	float fY = (float)(m_tInfo.iCY >> 1);

	float fDia = sqrtf(fX*fX + fY*fY);

	m_tPos[0].x = (LONG)(fX + cosf((135.f + m_fAngle)*PI / 180.f)*fDia);
	m_tPos[0].y = (LONG)(fY - sinf((135.f + m_fAngle)*PI / 180.f)*fDia);

	m_tPos[1].x = (LONG)(fX + cosf((45.f + m_fAngle)*PI / 180.f)*fDia);
	m_tPos[1].y = (LONG)(fY - sinf((45.f + m_fAngle)*PI / 180.f)*fDia);

	m_tPos[2].x = (LONG)(fX + cosf((225.f + m_fAngle)*PI / 180.f)*fDia);
	m_tPos[2].y = (LONG)(fY - sinf((225.f + m_fAngle)*PI / 180.f)*fDia);




	m_tColInfo.fX = (m_tInfo.fX) + (float)(CScrollMgr::Get_Instance()->Get_ScrollX());
	m_tColInfo.fY = (m_tInfo.fY) + (float)(CScrollMgr::Get_Instance()->Get_ScrollY());
	if (m_tColInfo.fX< -500
		|| m_tColInfo.fX > (WINCX + 500)
		|| m_tColInfo.fY < -500
		|| m_tColInfo.fY >(WINCY + 500))
		m_bDead =true;
}

void CBullet::Render(HDC _DC)
{
	Update_Rect();
	Update_ColRect();
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	//Ellipse(_DC, m_tRect.left+iScrollX, m_tRect.top+ iScrollY, m_tRect.right + iScrollX, m_tRect.bottom+ iScrollY);
	hPlgDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Plg");
	hResetDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Reset");
	hMemDC = CBmpMgr::Get_Instance()->Find_Bmp(m_pFrameKey);
	int ioffsetX = 0;
	if (m_bRightRev)
		ioffsetX = -17;
	else
		ioffsetX = 17;


	PlgBlt(hPlgDC, m_tPos
		, hMemDC
		, m_tFrame.iStartX * m_iFrameSize, m_tFrame.iStateY * m_iFrameSize
		, m_iFrameSize, m_iFrameSize
		, NULL, NULL, NULL);

	
	GdiTransparentBlt(_DC
		, m_tRect.left+ ioffsetX + iScrollX, m_tRect.top+10+ iScrollY
		, m_tInfo.iCX, m_tInfo.iCY
		, hPlgDC
		, 0, 0
		, m_iFrameSize, m_iFrameSize
		, RGB(255, 0, 255));

	BitBlt(hPlgDC, 0, 0, m_iFrameSize, m_iFrameSize, hResetDC, 0, 0, SRCCOPY);
	BitBlt(hStretchDC, 0, 0, m_iFrameSize, m_iFrameSize, hResetDC, 0, 0, SRCCOPY);

	DrawColRect(_DC);

}

void CBullet::Release()
{
}

void CBullet::DrawColRect(HDC _DC)
{
	int ioffsetX = 0;
	if (m_bRightRev)
		ioffsetX = -17;
	else
		ioffsetX = 17;

	//Ellipse(_DC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	m_tColInfo.fX = (m_tInfo.fX )+ ioffsetX + (float)(CScrollMgr::Get_Instance()->Get_ScrollX());
	m_tColInfo.fY = (m_tInfo.fY )+10+ (float)(CScrollMgr::Get_Instance()->Get_ScrollY());

	if (m_bColRect)
	{
		HPEN hNewPen = CreatePen(PS_SOLID, 2, 0x00ff0000);
		float fX = (m_tInfo.fX) - (m_tColInfo.iCX >> 1)+ ioffsetX + (float)(CScrollMgr::Get_Instance()->Get_ScrollX());
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


void CBullet::Bullet_AngleState()
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
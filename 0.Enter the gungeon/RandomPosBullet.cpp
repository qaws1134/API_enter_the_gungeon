#include "stdafx.h"
#include "RandomPosBullet.h"
#include "Bullet.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "BoomBullet.h"
CRandomPosBullet::CRandomPosBullet() : m_dwTime(GetTickCount()),m_iBreakTime(0), m_fInitY(0)
{
}


CRandomPosBullet::~CRandomPosBullet()
{
	Release();
}

void CRandomPosBullet::Initialize()
{
	//포신위치 90도로 고정


	m_iFrameSize = 200;

	m_tFrame.iStartX = 0;
	m_tFrame.iStateY = 0;

	m_tInfo.iCX = m_iFrameSize-100;
	m_tInfo.iCY = m_iFrameSize;
	m_eRenderID = RENDERID::EFFECT;


	m_eCurState = (CObj::STATE)UP;
	m_iBreakTime = 3000;

}

int CRandomPosBullet::Update()
{
	if (m_bDead)
	{
		if (m_eCurState == (CObj::STATE)DOWN)
		{

			m_tPosin.x = (LONG)m_tInfo.fX;
			m_tPosin.y = (LONG)m_tInfo.fY;
			CObj* TargetEffect = CreateBullet<CBoomBullet>(L"M_RandomPosEffect", 0, 1, 0.f);
			TargetEffect->Set_CurState((CObj::STATE)CBoomBullet::STATE::BOOM);
			CObjMgr::Get_Instance()->Add_Object(TargetEffect, OBJID::M_EFFECTATTACK);
		}

		return OBJ_DEAD;
	}

	State_Change();
	if (m_eCurState == (CObj::STATE)UP)
	{
		m_fSpeed *= 1.1f;
		m_tInfo.fY -= sinf(m_fAngle*PI / 180)*m_fSpeed;

		if (m_dwTime + m_iBreakTime < GetTickCount())
		{
			m_bDead = true;
		}

	}
	else
	{ 
		m_fSpeed *= 1.05f;
		if (m_tInfo.fY-m_fInitY >500)
			m_bDead = true;

		m_tInfo.fY += sinf(m_fAngle*PI / 180)*m_fSpeed;
	}

	Update_Frame();
	Update_Rect();



	return OBJ_NOEVENT;
}


void CRandomPosBullet::Late_Update()
{
}

void CRandomPosBullet::Render(HDC _DC)
{
	Update_Rect();
	//Update_ColRect();
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	//int ioffsetX = 0;
	//if (m_bRightRev)
	//	ioffsetX = -30;
	//else
	//	ioffsetX = 17;

	hMemDC = CBmpMgr::Get_Instance()->Find_Bmp(m_pFrameKey);

	GdiTransparentBlt(_DC
		, m_tRect.left + iScrollX , m_tRect.top - 100 + iScrollY
		, m_tInfo.iCX, m_tInfo.iCY
		, hMemDC
		, m_tFrame.iStartX* (m_iFrameSize - 100), m_tFrame.iStateY*m_iFrameSize
		, m_iFrameSize-100, m_iFrameSize
		, RGB(255, 0, 255));


	DrawColRect(_DC);
}
void CRandomPosBullet::Update_Frame()
{
	if (m_tFrame.dwTime + m_tFrame.dwDelay < GetTickCount())
	{
		++m_tFrame.iStartX;

		if (m_tFrame.iStartX >= m_tFrame.iEndX)
			m_tFrame.iStartX -=2;

		m_tFrame.dwTime = GetTickCount();
	}
}

void CRandomPosBullet::Release()
{
}

void CRandomPosBullet::DrawColRect(HDC _DC)
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


void CRandomPosBullet::State_Change()
{

	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case UP:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 8;
			m_tFrame.iStateY = UP;
			m_tFrame.dwDelay = 100;
			m_tFrame.dwTime = GetTickCount();
			if (m_fSpeed<0)
				m_fSpeed *= -1;
			m_fAngle = 90;
			break;
		case DOWN:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 5;
			m_tFrame.iStateY = DOWN;
			m_tFrame.dwDelay = 100;
			m_tFrame.dwTime = GetTickCount();
			m_fSpeed *= -1;
			m_fAngle = -90;
			m_fInitY = m_tInfo.fY;
			break;
		default:
			break;
		}
		m_ePreState = m_eCurState;
	}
}

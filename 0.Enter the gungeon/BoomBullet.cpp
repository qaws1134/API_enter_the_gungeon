#include "stdafx.h"
#include "BoomBullet.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "RandomPosBullet.h"
#include "ObjMgr.h"
#include "SoundMgr.h"
CBoomBullet::CBoomBullet() : m_bSound(false)
{
}


CBoomBullet::~CBoomBullet()
{
	Release();
}


void CBoomBullet::Initialize()
{

	m_iFrameSize = 300;
	m_tInfo.iCX = m_iFrameSize;
	m_tInfo.iCY = m_iFrameSize;

	m_eRenderID = RENDERID::EFFECT;
	

	//dwTime = GetTickCount();
	m_eCurState = (CObj::STATE)TARGET;
	m_tFrame.dwTime = GetTickCount();

}

int CBoomBullet::Update()
{
	if (m_bDead)
	{
		if (m_eCurState == BOOM)
		{
		}

		return OBJ_DEAD;
	}

	if (m_eCurState == BOOM)
	{
		if (!m_bSound)
		{
		
			CSoundMgr::Get_Instance()->PlaySound(L"Boom_Bullet.mp3", CSoundMgr::BOOM_BULLET);
			m_bSound = true;
		}
	}
	State_Change();
	Update_Frame();
	Update_Rect();
	Update_ColRect();
	return OBJ_NOEVENT;
}

void CBoomBullet::Late_Update()
{


}

void CBoomBullet::Render(HDC _DC)
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

void CBoomBullet::Release()
{
}

void CBoomBullet::Update_Frame()
{
	if (m_tFrame.dwTime + m_tFrame.dwDelay < GetTickCount())
	{
		++m_tFrame.iStartX;

		if (m_eCurState == TARGET)
		{
			if (m_tFrame.iStartX == m_tFrame.iEndX - 4)
			{

				CObj* Rocket = CreateBullet<CRandomPosBullet>(L"M_RandomPosBullet", 0, 0, 5.f);
				Rocket->Set_Pos(m_tInfo.fX, m_tInfo.fY - 500);
				Rocket->Set_CurState((CObj::STATE)CRandomPosBullet::STATE::DOWN);
				CObjMgr::Get_Instance()->Add_Object(Rocket, OBJID::EFFECT);
			}
		}
	
		if (m_tFrame.iStartX >= m_tFrame.iEndX)
		{
			m_tFrame.iStartX = m_tFrame.iEndX-1;
			Set_Dead();
		}
		m_tFrame.dwTime = GetTickCount();
	}
}

void CBoomBullet::State_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case BOOM:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 8;
			m_tFrame.iStateY = BOOM;
			m_tFrame.dwDelay = 50;
			m_tColInfo.iCX = m_iFrameSize- 100;
			m_tColInfo.iCY = m_iFrameSize- 100;
			m_tFrame.dwTime = GetTickCount();
			break;
		case TARGET:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 8;
			m_tFrame.iStateY = TARGET;
			m_tFrame.dwDelay = 150;
			m_tFrame.dwTime = GetTickCount();
			break;
		default:
			break;
		}
		m_ePreState = m_eCurState;
	}
}

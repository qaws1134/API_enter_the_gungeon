#include "stdafx.h"
#include "Monster.h"
#include "ObjMgr.h"
#include "BmpMgr.h"
#include "Bullet.h"
#include "ScrollMgr.h"
CMonster::CMonster()
	: m_iAtkDis(0), m_iAttDelay(0), dwAttTime(GetTickCount())
	,  m_iPatternDelay(0), dwPatternTime(GetTickCount())
	,  m_dwStopTime(GetTickCount()), m_pWeapon(nullptr)
	, m_dwHitTime(GetTickCount()), m_iHitTme(300), m_bRend(false)
	, m_bStartInit(false)
{
}


CMonster::~CMonster()
{

}
int CMonster::Update()
{
	if (!m_bSummon)
		return OBJ_NOTSUMMON;

	if (m_bDead)
		return OBJ_DEAD;

	if (!m_bStartInit)
	{
		Load_Init();
		m_bStartInit = true;
	}
	if (!m_bDeadStart)
	{
		Check_Angle();
		Monster_AngleState();
		AiState();
		Update_Rect();
		Update_ColRect();
		SelectFrame();
		State_Change();
		Update_Frame();
	}
	else 
	{
		m_eCurState = CObj::DEAD;
		SelectFrame();
		State_Change();
		Update_Frame();
	}
		

	return OBJ_NOEVENT;
}

void CMonster::Late_Update()
{
	m_tColInfo.fX = (m_tInfo.fX) + (float)(CScrollMgr::Get_Instance()->Get_ScrollX());
	m_tColInfo.fY = (m_tInfo.fY) + (float)(CScrollMgr::Get_Instance()->Get_ScrollY());
}

void CMonster::Render(HDC _DC)
{
	if (!m_bSummon)
		return;
	if (m_bRend)
		return;
	Update_Rect();
	Update_ColRect();
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	hMemDC = CBmpMgr::Get_Instance()->Find_Bmp(m_pFrameKey);
	hResetDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Reset");
	hPlgDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Plg");

	if ( m_bRightRev)
	{
		hStretchDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Stretch");

		StretchBlt(hStretchDC
			, 0, 0
			, m_iFrameSize, m_iFrameSize
			, hMemDC
			, m_tFrame.iStartX * m_iFrameSize + m_iFrameSize, m_tFrame.iStateY * m_iFrameSize
			, -m_iFrameSize, m_iFrameSize
			, SRCCOPY);

		GdiTransparentBlt(_DC
			, m_tRect.left + iScrollX, m_tRect.top + iScrollY
			, m_tInfo.iCX, m_tInfo.iCY
			, hStretchDC
			, 0, 0
			, m_iFrameSize, m_iFrameSize
			, RGB(255, 0, 255));
	}
	else
	{
		GdiTransparentBlt(_DC
			, m_tRect.left + iScrollX, m_tRect.top + iScrollY
			, m_tInfo.iCX, m_tInfo.iCY
			, hMemDC
			, m_tFrame.iStartX * m_iFrameSize, m_tFrame.iStateY * m_iFrameSize
			, m_iFrameSize, m_iFrameSize
			, RGB(255, 0, 255));
	}
	BitBlt(hStretchDC, 0, 0, m_iFrameSize, m_iFrameSize, hResetDC, 0, 0, SRCCOPY);
	BitBlt(hPlgDC, 0, 0, m_iFrameSize, m_iFrameSize, hResetDC, 0, 0, SRCCOPY);

	DrawColRect(_DC);
	
}


bool CMonster::Follow()
{
	m_pTarget = CObjMgr::Get_Instance()->Get_Player();
	if (!m_pTarget)
		return false;

	float fX = m_pTarget->Get_Info().fX - m_tInfo.fX;
	float fY = m_pTarget->Get_Info().fY - m_tInfo.fY;
	float fDia = sqrtf(fX * fX + fY * fY);
	float fDis = (float)(((m_pTarget->Get_Info().iCX + m_tInfo.iCX) >> 1) + m_iAtkDis);

	float	fRad = acosf(fX / fDia);

	m_fAngle = fRad * 180.f / PI;

	if (m_tInfo.fY < m_pTarget->Get_Info().fY)
		m_fAngle *= -1.f;


	m_tPosin.x = (LONG)(m_tInfo.fX + cosf(m_fAngle*PI / 180.f)*m_fPosinDis);
	m_tPosin.y = (LONG)(m_tInfo.fY - sinf(m_fAngle*PI / 180.f)*m_fPosinDis);

	if (fDia <= fDis)
	{
		return true;
	}
	
	return false;
}


void CMonster::AiState()
{
	if (Follow())
	{
		if (m_dwHitTime + m_iHitTme < GetTickCount())
		{
			m_eCurState = CObj::IDLE;
		}
	}
	else
		Move();

	Hit();

	Attack();
	
}

void CMonster::Hit()
{
	if (m_tStat.iHp != m_iCurHp)
	{
		m_eCurState = CObj::HIT;
		m_iCurHp = m_tStat.iHp;
	}
}

void CMonster::Check_Angle()
{
	m_pTarget = CObjMgr::Get_Instance()->Get_Player();
	if (!m_pTarget)
		return;

	float fX = m_pTarget->Get_Info().fX - m_tInfo.fX;
	float fY = m_pTarget->Get_Info().fY - m_tInfo.fY;
	float fDia = sqrtf(fX * fX + fY * fY);
	float fDis = (float)(((m_pTarget->Get_Info().iCX + m_tInfo.iCX) >> 1) + m_iAtkDis);

	float	fRad = acosf(fX / fDia);

	m_fAngle = fRad * 180.f / PI;

	if (m_tInfo.fY < m_pTarget->Get_Info().fY)
		m_fAngle *= -1.f;

}


void CMonster::Move()
{
	m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * m_fSpeed;
	m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * m_fSpeed;
	m_eCurState = CObj::WALK;
}


void CMonster::Update_Frame()
{
	if (m_bDeadStart)
	{
		if (m_tFrame.dwTime + m_tFrame.dwDelay < GetTickCount())
		{
			++m_tFrame.iStartX;

			if (m_tFrame.iStartX == m_tFrame.iEndX)
			{
				--m_tFrame.iStartX;
				if (m_dwStopTime + 800 < GetTickCount())
				{
					m_bDead = true;
				}
			}
			m_tFrame.dwTime = GetTickCount();
		}
	}
	else
	{
		if (m_tFrame.dwTime + m_tFrame.dwDelay < GetTickCount())
		{
			++m_tFrame.iStartX;
			if (m_tFrame.iStartX >= m_tFrame.iEndX)
				m_tFrame.iStartX = 0;
			m_tFrame.dwTime = GetTickCount();
		}
	}
}

void CMonster::Monster_AngleState()
{
	if (m_fAngle < 0)
	{
		if (m_fAngle > -90.f)
			m_eAngleState = STATE::DOWN_RIGHT;
		else if (m_fAngle > -180.f)
			m_eAngleState = STATE::DOWN_LEFT;
	}
	else
	{
		if (m_fAngle < 90.f)
			m_eAngleState = STATE::UP_RIGHT;
		else if (m_fAngle < 180.f)
			m_eAngleState = STATE::UP_LEFT;
	}
	if (m_eAngleState == STATE::DOWN_RIGHT
		|| m_eAngleState == STATE::UP_RIGHT)
		m_bRightRev = true;

	if (m_eAngleState == STATE::DOWN_LEFT
		|| m_eAngleState == STATE::UP_LEFT)
		m_bRightRev = false;
}



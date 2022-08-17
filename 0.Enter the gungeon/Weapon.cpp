#include "stdafx.h"
#include "BmpMgr.h"
#include "Weapon.h"
#include "Player.h"
#include "KeyMgr.h"
#include "ScrollMgr.h"
CWeapon::CWeapon()
	:m_iReloadTime(0), dwTime(GetTickCount()), m_iMaxReload(0), m_iReload(0)
	, m_iShotDelay(0), m_iMaxBullet(0), m_bRender(false), m_bReloadOn(false)
	, m_bAttackEnd(false), m_bReloadStart(false), m_iInitMaxBullet(0)
	
{
	ZeroMemory(m_tPos, sizeof(m_tPos));
}


CWeapon::~CWeapon()
{
}


int CWeapon::Update()
{
	if (m_bDead)
		return OBJ_DEAD;
	
	
	if (m_pTarget)
	{
		m_fAngle = m_pTarget->Get_Angle();

		m_tInfo.fX = (float)m_pTarget->Get_Posin().x;
		m_tInfo.fY = (float)m_pTarget->Get_Posin().y;

		Weapon_AngleState();

		State_Change();
		Update_Frame();

		Weapon_Delay();
		Update_Rect();

	}
	return OBJ_NOEVENT;
}

void CWeapon::Late_Update()
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

}

void CWeapon::Render(HDC _DC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	if (m_pTarget)
	{
		//플레이어 무기 랜더
		if (m_pTarget->Get_ObjID() == OBJID::PLAYER)
		{
			if (!static_cast<CPlayer*>(m_pTarget)->Get_Jump())
			{
				hPlgDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Plg");
				hResetDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Reset");

				int ioffsetX = 0;

				if (m_bRightRev)
				{

					ioffsetX = 5;
					hStretchDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Stretch");

					StretchBlt(hStretchDC
						, 0, 0
						, m_iFrameSize, m_iFrameSize
						, hMemDC
						, m_tFrame.iStartX * m_iFrameSize, m_tFrame.iStateY * m_iFrameSize + m_iFrameSize
						, m_iFrameSize, -m_iFrameSize
						, SRCCOPY);

					PlgBlt(hPlgDC, m_tPos
						, hStretchDC
						, 0, 0
						, m_iFrameSize, m_iFrameSize
						, NULL, NULL, NULL);

				}
				else {
					ioffsetX = -5;
					PlgBlt(hPlgDC, m_tPos
						, hMemDC
						, m_tFrame.iStartX * m_iFrameSize, m_tFrame.iStateY * m_iFrameSize
						, m_iFrameSize, m_iFrameSize
						, NULL, NULL, NULL);
				}

				GdiTransparentBlt(_DC
					, m_tRect.left + ioffsetX + iScrollX, m_tRect.top + 10 + iScrollY
					, m_tInfo.iCX, m_tInfo.iCY
					, hPlgDC
					, 0, 0
					, m_iFrameSize, m_iFrameSize
					, RGB(255, 0, 255));

				BitBlt(hPlgDC, 0, 0, m_iFrameSize, m_iFrameSize, hResetDC, 0, 0, SRCCOPY);
				BitBlt(hStretchDC, 0, 0, m_iFrameSize, m_iFrameSize, hResetDC, 0, 0, SRCCOPY);
			}
		}
		//몬스터 무기 랜더
		if (m_pTarget->Get_ObjID() == OBJID::MONSTER)
		{
			hPlgDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Plg");
			hResetDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Reset");

			int ioffsetX = 0;

			if (m_bRightRev)
			{
				ioffsetX = 5;
				hStretchDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Stretch");

				StretchBlt(hStretchDC
					, 0, 0
					, m_iFrameSize, m_iFrameSize
					, hMemDC
					, m_tFrame.iStartX * m_iFrameSize, m_tFrame.iStateY * m_iFrameSize + m_iFrameSize
					, m_iFrameSize, -m_iFrameSize
					, SRCCOPY);

				PlgBlt(hPlgDC, m_tPos
					, hStretchDC
					, 0, 0
					, m_iFrameSize, m_iFrameSize
					, NULL, NULL, NULL);

			}
			else {
				ioffsetX = -5;
				PlgBlt(hPlgDC, m_tPos
					, hMemDC
					, m_tFrame.iStartX * m_iFrameSize, m_tFrame.iStateY * m_iFrameSize
					, m_iFrameSize, m_iFrameSize
					, NULL, NULL, NULL);
			}

			GdiTransparentBlt(_DC
				, m_tRect.left + ioffsetX + iScrollX, m_tRect.top + 10 + iScrollY
				, m_tInfo.iCX, m_tInfo.iCY
				, hPlgDC
				, 0, 0
				, m_iFrameSize, m_iFrameSize
				, RGB(255, 0, 255));

			BitBlt(hPlgDC, 0, 0, m_iFrameSize, m_iFrameSize, hResetDC, 0, 0, SRCCOPY);
			BitBlt(hStretchDC, 0, 0, m_iFrameSize, m_iFrameSize, hResetDC, 0, 0, SRCCOPY);
		}
		
	}
}

void CWeapon::Release()
{
}


void CWeapon::Use_Bullet()
{
	Sound_Att();
	m_iReload -= 1;
	m_iMaxBullet-=1;
	dwTime = GetTickCount();
	m_eCurState = (CObj::STATE)WEAPONSTATE::ATTACK;
	
	m_tFrame.iStartX = 0;
}



void CWeapon::Update_Frame()
{
	if (m_tFrame.dwTime + m_tFrame.dwDelay < GetTickCount())
	{
		if (m_eCurState == WEAPONSTATE::ATTACK)
		{
			++m_tFrame.iStartX;
			if (m_tFrame.iStartX >= m_tFrame.iEndX)
			{
				m_tFrame.iStartX = m_tFrame.iEndX - 1;
				m_eCurState = (CObj::STATE)WEAPONSTATE::IDLE;
			}
			m_tFrame.dwTime = GetTickCount();
		}
		if (m_eCurState == WEAPONSTATE::RELOAD)
		{
			++m_tFrame.iStartX;
			if (m_tFrame.iStartX >= m_tFrame.iEndX)
			{
				m_tFrame.iStartX = m_tFrame.iEndX - 1;
			}
			m_tFrame.dwTime = GetTickCount();
		}

	}
}

void CWeapon::Get_WeaponUI(HDC _DC)
{
	if (m_pTarget)
	{
		GdiTransparentBlt(_DC
			, 1050, 680
			, m_iFrameSize, m_iFrameSize
			, hMemDC
			, m_tFrame.iStartX * m_iFrameSize, m_tFrame.iStateY * m_iFrameSize
			, m_iFrameSize, m_iFrameSize
			, RGB(255, 0, 255));
	}
}

void CWeapon::Weapon_AngleState()
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

bool CWeapon::Weapon_Delay()
{

	if (m_bReloadOn)
	{
		if (!m_bReloadStart) {
			Sound_Reload();
			dwTime = GetTickCount();
			m_bReloadStart = true;
		}
		Reload();
		return false;
	}

	//총알 장탄수
	if (m_iMaxBullet > 0 ) 
	{
		//샷 딜레이
		if (dwTime + m_iShotDelay < GetTickCount())
			return true;
	}



	return false;
}

void CWeapon::Reload()
{
	if (m_iReload != m_iMaxBullet)
	{
		m_eCurState = (CObj::STATE)WEAPONSTATE::RELOAD;
		if (dwTime + m_iReloadTime < GetTickCount())
		{
			m_iReload = m_iMaxReload;
			m_eCurState = (CObj::STATE)WEAPONSTATE::IDLE;
			m_bReloadOn = false;
			m_bReloadStart = false;
		}
	}
}


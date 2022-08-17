#include "stdafx.h"
#include "Way5ShotGun.h"
#include "BmpMgr.h"
#include "SoundMgr.h"
CWay5ShotGun::CWay5ShotGun()
{
}


CWay5ShotGun::~CWay5ShotGun()
{
}

void CWay5ShotGun::Initialize()
{
	m_iFrameSize = 96;
	m_tInfo.iCX = m_iFrameSize;
	m_tInfo.iCY = m_iFrameSize;

	m_eRenderID = RENDERID::OBJECT;


	m_iMaxReload = 6;
	m_iReload = m_iMaxReload;
	m_iReloadTime = 2000;
	m_iShotDelay = 500;
	m_iMaxBullet = 60;
	m_iInitMaxBullet = m_iMaxBullet;
	m_eCurState = (CObj::STATE)WEAPONSTATE::IDLE;
	m_bRightRev = true;

	hMemDC = CBmpMgr::Get_Instance()->Find_Bmp(m_pFrameKey);
	hStretchDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Stretch");
	hPlgDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Plg");
	hResetDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Reset");
}

void CWay5ShotGun::Update_Frame()
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
		if (m_eCurState == WEAPONSTATE::M_ATTACK)
		{
			++m_tFrame.iStartX;
			if (m_tFrame.iStartX == m_tFrame.iEndX - 2)
				m_bAttackEnd = true;
			if (m_tFrame.iStartX >= m_tFrame.iEndX)
			{
				Sound_Att();
				m_tFrame.iStartX = m_tFrame.iEndX - 1;
				m_eCurState = (CObj::STATE)WEAPONSTATE::IDLE;
				
			}
			m_tFrame.dwTime = GetTickCount();
		}
	}
}


void CWay5ShotGun::State_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case WEAPONSTATE::ATTACK:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 3;
			m_tFrame.iStateY = WEAPONSTATE::ATTACK;
			m_tFrame.dwDelay = 50;
			m_tFrame.dwTime = GetTickCount();
			break;
		case WEAPONSTATE::IDLE:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 1;
			m_tFrame.iStateY = WEAPONSTATE::IDLE;
			m_tFrame.dwDelay = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		case WEAPONSTATE::RELOAD:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 2;
			m_tFrame.iStateY = WEAPONSTATE::RELOAD;
			m_tFrame.dwDelay = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		case WEAPONSTATE::M_ATTACK:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 6;
			m_tFrame.iStateY = WEAPONSTATE::M_ATTACK;
			m_tFrame.dwDelay = 50;
			m_tFrame.dwTime = GetTickCount();
			break;

		}
		m_ePreState = m_eCurState;
	}
}

void CWay5ShotGun::Sound_Att()
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::SHOTGUN_ATT);
	CSoundMgr::Get_Instance()->PlaySound(L"ShotGun_Shot.mp3", CSoundMgr::SHOTGUN_ATT);
}

void CWay5ShotGun::Sound_Reload()
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::SHOTGUN_RELOAD);
	CSoundMgr::Get_Instance()->PlaySound(L"ShotGun_Reload.mp3", CSoundMgr::SHOTGUN_RELOAD);
}

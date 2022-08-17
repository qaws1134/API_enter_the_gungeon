#include "stdafx.h"
#include "OldGun.h"
#include "BmpMgr.h"
#include "SoundMgr.h"
COldGun::COldGun()
{
}


COldGun::~COldGun()
{
}

void COldGun::Initialize()
{

	m_iFrameSize = 96;
	m_tInfo.iCX = m_iFrameSize;
	m_tInfo.iCY = m_iFrameSize;

	m_eRenderID = RENDERID::OBJECT;


	m_iMaxReload	= 6;
	m_iReload		= m_iMaxReload;
	m_iReloadTime	= 1000;
	m_iShotDelay	= 300;
	m_iMaxBullet	= 999999;
	m_iInitMaxBullet = m_iMaxBullet;
	m_eCurState		= (CObj::STATE)WEAPONSTATE::IDLE;
	m_bRightRev		= true;

	hMemDC		= CBmpMgr::Get_Instance()->Find_Bmp(m_pFrameKey);
	hStretchDC  = CBmpMgr::Get_Instance()->Find_Bmp(L"Stretch");
	hPlgDC		= CBmpMgr::Get_Instance()->Find_Bmp(L"Plg");
	hResetDC	= CBmpMgr::Get_Instance()->Find_Bmp(L"Reset");

}



void COldGun::State_Change()
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
			m_tFrame.iEndX = 3;
			m_tFrame.iStateY = WEAPONSTATE::RELOAD;
			m_tFrame.dwDelay = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}


void COldGun::Update_Frame()
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
				m_tFrame.iStartX = m_tFrame.iEndX - 2;
			}
		}

	}
}

void COldGun::Sound_Att()
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::OLDGUN_ATT);
	CSoundMgr::Get_Instance()->PlaySound(L"OldGun_Shot.mp3", CSoundMgr::OLDGUN_ATT);
}

void COldGun::Sound_Reload()
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::OLDGUN_RELOAD);
	CSoundMgr::Get_Instance()->PlaySound(L"OldGun_Reload.mp3", CSoundMgr::OLDGUN_RELOAD);
}

#include "stdafx.h"
#include "GunDeadGun.h"
#include "BmpMgr.h"
#include "SoundMgr.h"
CGunDeadGun::CGunDeadGun()
{
}


CGunDeadGun::~CGunDeadGun()
{
}

void CGunDeadGun::Initialize()
{

	m_iFrameSize = 96;
	m_tInfo.iCX = m_iFrameSize;
	m_tInfo.iCY = m_iFrameSize;

	m_eRenderID = RENDERID::OBJECT;


	m_iMaxReload = 999;
	m_iReload = m_iMaxReload;
	//m_iReloadTime = 1000;
	//m_iShotDelay = 100;
	m_iMaxBullet = 999999;
	m_eCurState = (CObj::STATE)WEAPONSTATE::IDLE;
	m_bRightRev = true;

	hMemDC = CBmpMgr::Get_Instance()->Find_Bmp(m_pFrameKey);
	hStretchDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Stretch");
	hPlgDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Plg");
	hResetDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Reset");
}

void CGunDeadGun::Update_Frame()
{
	if (m_tFrame.dwTime + m_tFrame.dwDelay < GetTickCount())
	{
		if (m_eCurState == WEAPONSTATE::ATTACK)
		{
			++m_tFrame.iStartX;
			if(m_tFrame.iStartX == m_tFrame.iEndX-3)
				m_bAttackEnd = true;
			if (m_tFrame.iStartX >= m_tFrame.iEndX)
			{
				m_tFrame.iStartX = m_tFrame.iEndX - 1;
				m_eCurState = (CObj::STATE)WEAPONSTATE::IDLE;
				Sound_Att();
			}
			m_tFrame.dwTime = GetTickCount();
		}
	}
}




void CGunDeadGun::State_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case WEAPONSTATE::ATTACK:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 7;
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
		}
		m_ePreState = m_eCurState;
	}
}

void CGunDeadGun::Sound_Att()
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::GUNDEADGUN_ATT);
	CSoundMgr::Get_Instance()->PlaySound(L"GunDeadGun_Shot.mp3", CSoundMgr::GUNDEADGUN_ATT);
}

void CGunDeadGun::Sound_Reload()
{
}

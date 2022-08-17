#include "stdafx.h"
#include "CrossBow.h"
#include "BmpMgr.h"
#include "SoundMgr.h"
CCrossBow::CCrossBow() :m_bArrow(true)
{
}


CCrossBow::~CCrossBow()
{
}

void CCrossBow::Initialize()
{
	m_iFrameSize = 96;
	m_tInfo.iCX = m_iFrameSize;
	m_tInfo.iCY = m_iFrameSize;

	m_eRenderID = RENDERID::OBJECT;


	m_iMaxReload = 1;
	m_iReload = m_iMaxReload;
	m_iReloadTime = 1500;
	m_iShotDelay = 0;

	m_iMaxBullet = 80;
	m_iInitMaxBullet = m_iMaxBullet;
	m_eCurState = (CObj::STATE)WEAPONSTATE::IDLE;
	m_bRightRev = true;

	hMemDC = CBmpMgr::Get_Instance()->Find_Bmp(m_pFrameKey);

}

void CCrossBow::State_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case WEAPONSTATE::ATTACK:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 5;
			m_tFrame.iStateY = WEAPONSTATE::ATTACK;
			m_tFrame.dwDelay = 50;
			m_tFrame.dwTime = GetTickCount();
			break;
		case WEAPONSTATE::IDLE:
			if(m_bArrow)
				m_tFrame.iStartX = 0;
			else
				m_tFrame.iStartX = 1;
			m_tFrame.iEndX = 2;
			m_tFrame.iStateY = WEAPONSTATE::IDLE;
			m_tFrame.dwDelay = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		case WEAPONSTATE::RELOAD:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 3;
			m_tFrame.iStateY = WEAPONSTATE::RELOAD;
			m_tFrame.dwDelay = 100;
			m_tFrame.dwTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}


void CCrossBow::Update_Frame()
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
				m_bArrow = false;
			}
			m_tFrame.dwTime = GetTickCount();
		}

		if (m_eCurState == WEAPONSTATE::RELOAD)
		{
			++m_tFrame.iStartX;

			if (m_tFrame.iStartX >= m_tFrame.iEndX)
			{
				m_tFrame.iStartX = m_tFrame.iEndX - 1;
				m_bArrow = true;
			
			}
			m_tFrame.dwTime = GetTickCount();
		}

	}
}

void CCrossBow::Sound_Att()
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::CROSSBOW_ATT);
	CSoundMgr::Get_Instance()->PlaySound(L"CrossBow_Shot.mp3", CSoundMgr::CROSSBOW_ATT);
}

void CCrossBow::Sound_Reload()
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::CROSSBOW_RELOAD);
	CSoundMgr::Get_Instance()->PlaySound(L"CrossBow_Reload.mp3", CSoundMgr::CROSSBOW_RELOAD);
}

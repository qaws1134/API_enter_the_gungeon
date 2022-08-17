#include "stdafx.h"
#include "Mage.h"
#include "ObjMgr.h"
#include "Bullet.h"
#include "BmpMgr.h"
#include "Way5ShotGun.h"
#include "MageBullet.h"
#include "SoundMgr.h"

CMage::CMage()
	:Up_Teleport(false), m_ePattern(END), m_ePrePattern(END), m_bAtt(true)
	, m_bRangeCheck(false), m_iPatternDis(0), m_bTeleport(false)

{
}

CMage::~CMage()
{
	Release();
}

void CMage::Initialize()
{
	m_iAtkDis = 1000;
	m_iTelDis = 200;
	m_fSpeed = 1.f;
	m_iFrameSize = 150;
	m_tInfo.iCX = m_iFrameSize;
	m_tInfo.iCY = m_iFrameSize;
	m_fPosinDis = 50.f;
	m_iAttDelay = 5000;

	m_tStat.iMaxHp = 10;
	m_tStat.iHp = m_tStat.iMaxHp;
	m_tStat.iAtt = 1;
	m_iCurHp = m_tStat.iMaxHp;

	m_eCurState = CObj::WALK;
	m_pFrameKey = L"Mage_Down_Left";
	m_eRenderID = RENDERID::OBJECT;

	m_tColInfo.fX = m_tInfo.fX;
	m_tColInfo.fY = m_tInfo.fY;
	m_tColInfo.iCX = 50;
	m_tColInfo.iCY = 50;
	dwPatternTime = GetTickCount();
	dwAttTime = GetTickCount();
}




void CMage::Release()
{

}

void CMage::Attack()
{
	if (dwAttTime + m_iAttDelay < GetTickCount())
	{
		CSoundMgr::Get_Instance()->PlaySound(L"Mage_Att.mp3", CSoundMgr::MAGE_ATT);
		CObjMgr::Get_Instance()->Add_Object(CreateBullet <CMageBullet> (m_tInfo.fX,m_tInfo.fY-10.f,m_fAngle), OBJID::EFFECT);
		m_eCurState = (CObj::STATE)PATTERN::ATT;
		dwAttTime = GetTickCount();
	}
}
void CMage::Teleport()
{
	m_pTarget = CObjMgr::Get_Instance()->Get_Player();
	if (!m_pTarget)
		return;

	float fX = m_pTarget->Get_Info().fX - m_tInfo.fX;
	float fY = m_pTarget->Get_Info().fY - m_tInfo.fY;
	float fDia = sqrtf(fX * fX + fY * fY);
	float fDis = 2.f;
	float	fRad = acosf(fX / fDia);

	m_fAngle = fRad * 180.f / PI;

	if (m_tInfo.fY < m_pTarget->Get_Info().fY)
		m_fAngle *= -1.f;

	if (m_bTeleport)
	{
		CSoundMgr::Get_Instance()->PlaySound(L"Mage_Teleport.mp3", CSoundMgr::MAGE_TELEPORT);
		m_bRend = true;
		m_tInfo.fX = (float)(m_tInfo.fX + cosf(m_fAngle*PI / 180.f)*-fDis);
		m_tInfo.fY = (float)(m_tInfo.fY - sinf(m_fAngle*PI / 180.f)*-fDis);
	}

	m_eCurState = (CObj::STATE)PATTERN::TELEPORT;

}
void CMage::Update_Frame()
{
	if (m_tFrame.dwTime + m_tFrame.dwDelay < GetTickCount())
	{
		if (m_bDeadStart)
		{
			if (m_tFrame.dwTime + m_tFrame.dwDelay < GetTickCount())
			{
				++m_tFrame.iStartX;

				if (m_tFrame.iStartX == 1)
				{
					CSoundMgr::Get_Instance()->PlaySound(L"Mage_Dead.mp3", CSoundMgr::MAGE_DEAD);
				}
				if (m_tFrame.iStartX >= m_tFrame.iEndX)
				{
					--m_tFrame.iStartX;
					if (m_dwStopTime + 1500 < GetTickCount())
					{
					
						m_bDead = true;
					}
				}
				m_tFrame.dwTime = GetTickCount();
			}
		}
		else
		{
			++m_tFrame.iStartX;
			if (m_tFrame.iStartX >= m_tFrame.iEndX)
			{
				m_tFrame.iStartX = m_tFrame.iEndX - 1;
				m_ePrePattern = m_ePattern;
			}
			m_tFrame.dwTime = GetTickCount();	
		}
	}

}
bool CMage::RangeCheck(int _iRange)
{
	m_pTarget = CObjMgr::Get_Instance()->Get_Player();
	if (!m_pTarget)
		return false;

	float fX = m_pTarget->Get_Info().fX - m_tInfo.fX;
	float fY = m_pTarget->Get_Info().fY - m_tInfo.fY;
	float fDia = sqrtf(fX * fX + fY * fY);
	float fDis = (float)(((m_pTarget->Get_Info().iCX + m_tInfo.iCX) >> 1) + _iRange);

	float	fRad = acosf(fX / fDia);

	m_fAngle = fRad * 180.f / PI;

	if (m_tInfo.fY < m_pTarget->Get_Info().fY)
		m_fAngle *= -1.f;


	if (fDia <= fDis)
	{
		return true;
	}

	return false;
}
void CMage::Load_Init()
{
}
void CMage::AiState()
{
	switch (m_ePrePattern)
	{
	case ATT:
		m_eCurState = (CObj::STATE)PATTERN::IDLE;
		if (dwPatternTime + m_iPatternDelay < GetTickCount())
		{
			m_bRangeCheck = false;
			dwPatternTime = GetTickCount();
		}
		break;
	case TELEPORT:
		m_bTeleport = true;
		m_eCurState = (CObj::STATE)PATTERN::IDLE;
		if (dwPatternTime + m_iPatternDelay < GetTickCount())
		{
			m_bRangeCheck = false;
			m_bTeleport = false;
			m_bRend = false;
			dwPatternTime = GetTickCount();
		}
		break;
	default:
		break;
	}
	m_ePrePattern = END;

	
	if (!m_bRangeCheck)
	{
		if (RangeCheck(m_iTelDis))
		{
			m_iPatternDis = m_iTelDis;
			m_ePattern = TELEPORT;
			m_iAttDelay = 5000;
			m_iPatternDelay = 3500;
			m_bRangeCheck = true;
		}
		else if (RangeCheck(m_iAtkDis))
		{
			m_iPatternDis = m_iAtkDis;
			m_ePattern = ATT;
			m_iAttDelay = 5000;
			m_iPatternDelay = 3500;
			m_bRangeCheck = true;
			m_bRender = true;
			dwPatternTime = GetTickCount();
		}		
	}
	else
	{
		if (m_iPatternDis == m_iAtkDis)
		{
			Attack();
		}
		else
		{
			Teleport();
		}
	}
	
}

//0 IDLE, 1 ATT,2 TELEPORT, 3 DEAD 
void CMage::State_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case CObj::WALK:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 1;
			m_tFrame.iStateY = CObj::WALK;
			m_tFrame.dwDelay = 300;
			m_tFrame.dwTime = GetTickCount();
			break;
		case CObj::IDLE:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 6;
			m_tFrame.iStateY = CObj::IDLE;
			m_tFrame.dwDelay = 200;
			m_tFrame.dwTime = GetTickCount();
			break;
		case TELEPORT:
			if (Up_Teleport)
			{
				m_tFrame.iStartX = 0;
				m_tFrame.iEndX = 3;
			}
			else 
			{
				m_tFrame.iStartX = 0;
				m_tFrame.iEndX = 6;
			}
			m_tFrame.iStateY = CObj::JUMP;
			m_tFrame.dwDelay = 150;
			m_tFrame.dwTime = GetTickCount();
			break;
		case CObj::DEAD:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 4;
			m_tFrame.iStateY = DEAD;
			m_tFrame.dwDelay = 80;
			m_tFrame.dwTime = GetTickCount();
			m_dwStopTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}




void CMage::SelectFrame()
{
	if (m_eAngleState == STATE::DOWN_LEFT || m_eAngleState == STATE::DOWN_RIGHT)
	{
		m_pFrameKey = L"Mage_Down_Left";
		Up_Teleport = false;
	}
	else
	{
		m_pFrameKey = L"Mage_Up_Left";
		Up_Teleport = true;
	}

}

#include "stdafx.h"
#include "BlueGunDead.h"
#include "ObjMgr.h"
#include "Bullet.h"
#include "BmpMgr.h"
#include "Way5ShotGun.h"
#include "SoundMgr.h"
CBlueGunDead::CBlueGunDead() : m_bAtt(true)
{
}


CBlueGunDead::~CBlueGunDead()
{
	Release();
}

void CBlueGunDead::Initialize()
{
	m_iAtkDis = 300;
	m_fSpeed = 1.f;
	m_iFrameSize = 93;
	m_tInfo.iCX = m_iFrameSize;
	m_tInfo.iCY = m_iFrameSize;
	m_fPosinDis = 50.f;
	m_iAttDelay = 4000+ rand() % 1000;
	m_iPatternDelay = 500;

	m_iAttCount = 2;

	m_tStat.iMaxHp = 10;
	m_tStat.iHp = m_tStat.iMaxHp;
	m_tStat.iAtt = 1;
	m_iCurHp = m_tStat.iMaxHp;

	m_eCurState = CObj::IDLE;
	m_pFrameKey = L"BlueGunDead_Down_Left";
	m_eRenderID = RENDERID::OBJECT;

	m_tColInfo.fX = m_tInfo.fX;
	m_tColInfo.fY = m_tInfo.fY;
	m_tColInfo.iCX = 40;
	m_tColInfo.iCY = 60;
	dwPatternTime = GetTickCount();

}




void CBlueGunDead::Release()
{
	
	if(rand()%2 == 0)
		CreateXWayBullet<CBullet>(360.f, 6, 1, 4.f, L"M_Normal", OBJID::M_BULLET);
}

void CBlueGunDead::Attack()
{
	if (m_bAtt)
	{
		if (dwPatternTime + m_iPatternDelay< GetTickCount())
		{	
			static_cast<CWay5ShotGun*>(m_CurWeapon)->Set_WeaponState(CWeapon::WEAPONSTATE::M_ATTACK);
			dwPatternTime = GetTickCount();
		}
		if (m_iAttCount <= 0)
			m_bAtt = false;	
	}
	if (static_cast<CWay5ShotGun*>(m_CurWeapon)->Get_AttackEnd())
	{
		CreateXWayBullet<CBullet>(30.f, 5, 1, 4.f, L"M_Normal", OBJID::M_BULLET);
		m_iAttCount--;
		static_cast<CWay5ShotGun*>(m_CurWeapon)->Set_AttackEnd();
	}
	if (dwAttTime + m_iAttDelay < GetTickCount())
	{
		m_iAttCount = 2;
		m_bAtt = true;
		dwAttTime = GetTickCount();
	}
}

void CBlueGunDead::State_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case CObj::WALK:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 6;
			m_tFrame.iStateY = WALK;
			m_tFrame.dwDelay = 300;
			m_tFrame.dwTime = GetTickCount();
			break;
		case CObj::IDLE:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 1;
			m_tFrame.iStateY = CObj::IDLE;
			m_tFrame.dwDelay = 300;
			m_tFrame.dwTime = GetTickCount();
			break;
		case CObj::DEAD:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 6;
			m_tFrame.iStateY = DEAD;
			m_tFrame.dwDelay = 80;
			m_tFrame.dwTime = GetTickCount();
			m_CurWeapon->Set_Dead();
			m_dwStopTime = GetTickCount();
			CSoundMgr::Get_Instance()->PlaySound(L"BlueGunDead_Dead.mp3", CSoundMgr::BLUEGUNDEAD_DEAD);
			break;
		case CObj::HIT:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 1;
			m_tFrame.iStateY = HIT;
			m_tFrame.dwDelay = 300;
			m_tFrame.dwTime = GetTickCount();
			m_dwHitTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}

void CBlueGunDead::Load_Init()
{
	m_CurWeapon = CAbstractFactory<CWay5ShotGun>::Create(WEAPONID::WAY5SHOTGUN, L"Way5ShotGun");

	m_CurWeapon->Set_Target(this);
	CObjMgr::Get_Instance()->Add_Object(m_CurWeapon, OBJID::WEAPON);
}


void CBlueGunDead::SelectFrame()
{

	if (m_eAngleState == STATE::DOWN_LEFT || m_eAngleState == STATE::DOWN_RIGHT)
		m_pFrameKey = L"BlueGunDead_Down_Left";
	else
		m_pFrameKey = L"BlueGunDead_Up_Left";

}

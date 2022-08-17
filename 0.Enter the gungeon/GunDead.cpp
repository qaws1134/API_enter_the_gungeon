#include "stdafx.h"
#include "GunDead.h"
#include "ObjMgr.h"
#include "Bullet.h"
#include "BmpMgr.h"
#include "GunDeadGun.h"
CGunDead::CGunDead()
{
}


CGunDead::~CGunDead()
{
	Release();
}

void CGunDead::Initialize()
{
	m_iAtkDis = 300;
	m_fSpeed = 1.f;

	m_iFrameSize = 96;
	m_tInfo.iCX = m_iFrameSize;
	m_tInfo.iCY = m_iFrameSize;
	m_fPosinDis = 50.f;
	m_iAttDelay = 3000+rand()%1000;
	m_iPatternDelay = 3000;

	m_tStat.iMaxHp = 6;
	m_tStat.iHp = m_tStat.iMaxHp;
	m_tStat.iAtt = 1;
	m_iCurHp = m_tStat.iMaxHp;


	m_eCurState = CObj::IDLE;
	m_pFrameKey = L"GunDead_Down_Left";
	m_eRenderID = RENDERID::OBJECT;

	m_tColInfo.fX = m_tInfo.fX;
	m_tColInfo.fY = m_tInfo.fY;
	m_tColInfo.iCX = 40;
	m_tColInfo.iCY = 50;
}
void CGunDead::Load_Init()
{
	m_CurWeapon = CAbstractFactory<CGunDeadGun>::Create(WEAPONID::GUNDEADGUN, L"GunDeadGun");
	m_CurWeapon->Set_Target(this);
	CObjMgr::Get_Instance()->Add_Object(m_CurWeapon, OBJID::WEAPON);
}

void CGunDead::Release()
{

}

void CGunDead:: Attack()
{
	if (dwAttTime + m_iAttDelay < GetTickCount())
	{
		static_cast<CGunDeadGun*>(m_CurWeapon)->Set_WeaponState(CWeapon::WEAPONSTATE::ATTACK);
		dwAttTime = GetTickCount();
	}
	if (static_cast<CGunDeadGun*>(m_CurWeapon)->Get_AttackEnd())
	{
		CObjMgr::Get_Instance()->Add_Object(CreateBullet<CBullet>(L"M_Normal", 10, 1, 5.f), OBJID::M_BULLET);
		static_cast<CGunDeadGun*>(m_CurWeapon)->Set_AttackEnd();
	}
}


void CGunDead::State_Change()
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
			m_tFrame.iEndX = 5;
			m_tFrame.iStateY = DEAD;
			m_tFrame.dwDelay = 80;
			m_tFrame.dwTime = GetTickCount();
			m_CurWeapon->Set_Dead();
			m_dwStopTime = GetTickCount();
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

void CGunDead::SelectFrame()
{
	if (m_eAngleState == STATE::DOWN_LEFT || m_eAngleState == STATE::DOWN_RIGHT)
		m_pFrameKey = L"GunDead_Down_Left";
	else
		m_pFrameKey = L"GunDead_Up_Left";
}

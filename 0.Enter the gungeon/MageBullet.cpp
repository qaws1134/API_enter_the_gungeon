#include "stdafx.h"
#include "MageBullet.h"
#include "ObjMgr.h"
#include "ShieldBullet.h"
CMageBullet::CMageBullet():m_dwCreateTime(GetTickCount()), m_iCreateDelay(300), m_iBulletCount(10)
{
	ZeroMemory(&m_tCenterPos, sizeof(m_tCenterPos));
}


CMageBullet::~CMageBullet()
{
	Release();
}

void CMageBullet::Initialize()
{
	m_tInfo.iCX = 30;
	m_tInfo.iCY = 30;
	m_fSpeed = 30.f;

	m_fCenterSpeed = 5.f;

	m_eRenderID = RENDERID::OBJECT;
}

int CMageBullet::Update()
{
	if (m_bDead)
		return OBJ_DEAD;


	if (m_iBulletCount > 0)
	{
		if (m_dwCreateTime + m_iCreateDelay < GetTickCount())
		{
			CObjMgr::Get_Instance()->
				Add_Object(CAbstractFactory<CShieldBullet>::Create(static_cast<CObj*>(this), L"M_BossBullet"), OBJID::M_BULLET);
			m_iBulletCount--;
			m_dwCreateTime = GetTickCount();
		}
	}
	else
	{
		m_tInfo.fX += cosf(m_fAngle * PI / 180.f) * m_fCenterSpeed;
		m_tInfo.fY -= sinf(m_fAngle * PI / 180.f) * m_fCenterSpeed;
	}

	Update_Rect();
	return OBJ_NOEVENT;
}

void CMageBullet::Late_Update()
{
}

void CMageBullet::Render(HDC _DC)
{
}

void CMageBullet::Release()
{
}

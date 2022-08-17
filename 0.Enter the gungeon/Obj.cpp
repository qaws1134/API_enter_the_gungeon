#include "stdafx.h"
#include "Obj.h"
#include "Bullet.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "TileMgr.h"
CObj::CObj()
	: m_fSpeed(0.f), m_bDead(false), m_fAngle(0.f)
	, m_pTarget(nullptr), m_fDis(0.f), m_fPosinDis(0.f)
	, m_eWeapon(WEAPONID::END), m_bSuper(false), m_eRenderID(RENDERID::END)
	, m_ePreState(END), m_eCurState(END), m_bRightRev(true), m_iFrameSize(0)
	, m_CurWeapon(nullptr), hMemDC(NULL)
	, hPlgDC(NULL), hResetDC(NULL), hStretchDC(NULL)
	, m_bColRect(false), m_eID(OBJID::END), m_iRoomNum(0)
	, m_bSummon(false), m_iSuperTime(1000), m_dwSuperTime(GetTickCount())
	, m_bDeadStart(false), m_iMonsterID(0), m_bInterection(false)
	
{
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
	ZeroMemory(&m_tRect, sizeof(m_tRect));

	ZeroMemory(&m_tPosin, sizeof(m_tPosin));

	ZeroMemory(&m_tStat, sizeof(m_tStat));

	ZeroMemory(&m_tColInfo, sizeof(m_tColInfo));
	ZeroMemory(&m_tColRect, sizeof(m_tColRect));
}			   


CObj::~CObj()
{

}

void CObj::Random_Angle(int _fAdd)
{
	if (0 == _fAdd)
		return;
	float i = 1.f;
	if (0 == rand() % 2)
		i *= -1.f;
	m_fAngle += (float)(rand() % _fAdd )*  i;
}

list<CObj*> CObj::ColCheck(int _idx)
{
	list<CObj*> _listColCheck;
	_listColCheck.emplace_back(CTileMgr::Get_Instance()->Get_Tile(_idx - 1));
	_listColCheck.emplace_back(CTileMgr::Get_Instance()->Get_Tile(_idx + 1));
	_listColCheck.emplace_back(CTileMgr::Get_Instance()->Get_Tile(_idx - TILEX));
	_listColCheck.emplace_back(CTileMgr::Get_Instance()->Get_Tile(_idx + TILEX));

	return _listColCheck;
}

void CObj::Update_Frame()
{
	if (m_tFrame.dwTime + m_tFrame.dwDelay < GetTickCount())
	{
		++m_tFrame.iStartX;

		if (m_tFrame.iStartX >= m_tFrame.iEndX)
			m_tFrame.iStartX = 0;

		m_tFrame.dwTime = GetTickCount();
	}
}

void CObj::DrawColRect(HDC _DC)
{
	if (m_bColRect)
	{
		HPEN hNewPen = CreatePen(PS_SOLID, 2, 0x00ff0000);
		float fX = (m_tInfo.fX) - (m_tColInfo.iCX >> 1) + (float)(CScrollMgr::Get_Instance()->Get_ScrollX());
		float fY = (m_tInfo.fY) - (m_tColInfo.iCX >> 1) + (float)(CScrollMgr::Get_Instance()->Get_ScrollY());

		MoveToEx(_DC, (int)fX, (int)fY, false);

		LineTo(_DC, (int)fX + m_tColInfo.iCX, (int)fY);

		LineTo(_DC, (int)fX + m_tColInfo.iCX, (int)fY + m_tColInfo.iCY);
		LineTo(_DC, (int)fX, (int)fY + m_tColInfo.iCY);
		LineTo(_DC, (int)fX, (int)fY);


		MoveToEx(_DC, (int)fX, (int)fY, false);
		LineTo(_DC, (int)fX + m_tColInfo.iCX, (int)fY + m_tColInfo.iCY);


		MoveToEx(_DC, (int)fX, (int)fY, false);

		MoveToEx(_DC, (int)fX + m_tColInfo.iCX, (int)fY, false);
		LineTo(_DC, (int)fX, (int)fY + m_tColInfo.iCY);
		DeleteObject(SelectObject(_DC, hNewPen));
	}
}

void CObj::Update_ColRect()
{
	m_tColRect.left = (LONG)(m_tColInfo.fX - (m_tColInfo.iCX >> 1));
	m_tColRect.top = (LONG)(m_tColInfo.fY - (m_tColInfo.iCY >> 1));
	m_tColRect.right = (LONG)(m_tColInfo.fX + (m_tColInfo.iCX >> 1));
	m_tColRect.bottom = (LONG)(m_tColInfo.fY + (m_tColInfo.iCY >> 1));
}

void CObj::Update_Rect()
{
	m_tRect.left = (LONG)(m_tInfo.fX - (m_tInfo.iCX >> 1));
	m_tRect.top = (LONG)(m_tInfo.fY - (m_tInfo.iCY >> 1));
	m_tRect.right = (LONG)(m_tInfo.fX + (m_tInfo.iCX >> 1));
	m_tRect.bottom = (LONG)(m_tInfo.fY + (m_tInfo.iCY >> 1));
}


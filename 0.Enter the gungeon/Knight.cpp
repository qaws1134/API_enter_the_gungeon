#include "stdafx.h"
#include "Knight.h"
#include "ObjMgr.h"
#include "Bullet.h"
#include "BmpMgr.h"
#include "Bullet.h"
#include "SoundMgr.h"
CKnight::CKnight()
	:m_dwKnightBullet(GetTickCount())
	, m_iKnightBullet(100), m_iKnightPattern(0), m_bLoop(false), m_bAttEnd(false), m_bKnightPattern(false)
	, m_iFrame(0)
{
}


CKnight::~CKnight()
{
	Release();
}

void CKnight::Initialize()
{
	m_iAtkDis = 600;
	m_fSpeed = 1.f;

	m_iFrameSize = 225;
	m_tInfo.iCX = m_iFrameSize;
	m_tInfo.iCY = m_iFrameSize;
	m_fPosinDis = 50.f;
	m_iAttDelay = 5000;
	m_iPatternDelay = 4000;


	m_tStat.iMaxHp = 10;
	m_tStat.iHp = m_tStat.iMaxHp;
	m_tStat.iAtt = 1;
	m_iCurHp = m_tStat.iMaxHp;

	m_eCurState = CObj::IDLE;
	m_pFrameKey = L"Knight_Down";
	m_eRenderID = RENDERID::OBJECT;

	m_tColInfo.fX = m_tInfo.fX+30;
	m_tColInfo.fY = m_tInfo.fY;
	m_tColInfo.iCX = 40;
	m_tColInfo.iCY = 80;

}




void CKnight::Release()
{
	
}

void CKnight::Attack()
{

	if (!m_bAttEnd)
	{
		m_iKnightPattern = 0;
		m_dwKnightBullet = GetTickCount();
		m_eCurState = CObj::IDLE;
	}
	if(m_bAttEnd)
		CreateKnightBullet(5.f, OBJID::M_BULLET);

	//if (dwAttTime + m_iAttDelay < GetTickCount())
	//{
	//	dwAttTime = GetTickCount();
	//}

}
void CKnight::Update_Frame()
{
	if (m_bDeadStart)
	{
		if (m_tFrame.dwTime + m_tFrame.dwDelay < GetTickCount())
		{
			++m_tFrame.iStartX;

			if (m_tFrame.iStartX == m_tFrame.iEndX)
			{
				--m_tFrame.iStartX;
				if (m_dwStopTime + 800 < GetTickCount())
				{
					m_bDead = true;
				}
			}
			m_tFrame.dwTime = GetTickCount();
		}
	}
	else
	{
		if (m_bLoop)
		{
			if (m_tFrame.dwTime + m_tFrame.dwDelay < GetTickCount())
			{
				++m_tFrame.iStartX;
				if (m_tFrame.iStartX >= m_tFrame.iEndX)
					m_tFrame.iStartX = 0;
				m_tFrame.dwTime = GetTickCount();
			}
		}
		else
		{
			if (m_tFrame.dwTime + m_tFrame.dwDelay < GetTickCount())
			{
				++m_tFrame.iStartX;
				if (m_tFrame.iStartX >= m_tFrame.iEndX)
				{
					m_tFrame.iStartX = m_tFrame.iEndX - 1;
					m_bAttEnd = true;
				}

				m_tFrame.dwTime = GetTickCount();
			}
		}

	}
}
void CKnight::AiState()
{
	if (Follow())
	{
		if (m_dwHitTime + m_iHitTme < GetTickCount())
		{
			//m_eCurState = CObj::IDLE;
		}
		
		if (!m_bPattern)
		{
			//공격중이아니면 카운트 시작 

			if (dwPatternTime + m_iPatternDelay < GetTickCount())
			{
				m_bPattern = true;
				m_bAttEnd = false;
				dwPatternTime = GetTickCount();
			}
			Move();
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::KNIGHT_WALK);
			CSoundMgr::Get_Instance()->PlaySound(L"Knight_Walk.mp3", CSoundMgr::KNIGHT_WALK);
			
		}
		if(m_bPattern)
			Attack();
	}

	Hit();


}
void CKnight::Load_Init()
{
}
void CKnight::State_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case CObj::WALK:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 4;
			m_tFrame.iStateY = WALK;
			m_tFrame.dwDelay = 300;
			m_tFrame.dwTime = GetTickCount();
			m_bLoop = true;
			break;
		case CObj::IDLE:
			if (m_iFrame ==1)
			{
				m_tFrame.iStartX = 0;
				m_tFrame.iEndX = 7;
				m_tFrame.dwDelay = 100;
			}
			else if (m_iFrame==2)
			{
				m_tFrame.iStartX = 0;
				m_tFrame.iEndX = 4;
				m_tFrame.dwDelay = 200;
			}
			else if (m_iFrame==3)
			{
				m_tFrame.iStartX = 0;
				m_tFrame.iEndX = 5;
				m_tFrame.dwDelay = 190;
			}

			m_tFrame.iStateY = CObj::IDLE;
			m_tFrame.dwTime = GetTickCount();
			m_bLoop = false;
			break;
		case CObj::DEAD:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 4;
			m_tFrame.iStateY = DEAD;
			m_tFrame.dwDelay = 60;
			m_tFrame.dwTime = GetTickCount();
			m_dwStopTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
	}
}


void CKnight::SelectFrame()
{


}


void CKnight::CreateKnightBullet( float _fSpeed, OBJID::ID _eID)
{

	if (m_bKnightPattern)
	{
		if (0 == m_iKnightPattern)
		{
			float fOffSet = 24.f;
			float fMinAngle = m_fAngle - (70);
			for (int i = 0; i < 3; i++)
			{
				CObjMgr::Get_Instance()->Add_Object(CreateBullet<CBullet>(fMinAngle, L"M_BossBullet", 1, _fSpeed), _eID);
				fMinAngle += (float)((140 / 3));
			}

		}
		else if (1 == m_iKnightPattern)
		{
			float fOffSet = 24.f;

			float fMinAngle = m_fAngle - (70 - 24);
			//fMinAngle -= fOffSet;
			for (int i = 0; i < 3; i++)
			{
				CObjMgr::Get_Instance()->Add_Object(CreateBullet<CBullet>(fMinAngle, L"M_BossBullet", 1, _fSpeed), _eID);
				fMinAngle += (float)(48);
			}
		}
		else if (2 == m_iKnightPattern)
		{
			float fMinAngle = m_fAngle - (70 + 24);
			for (int i = 0; i < 3; i++)
			{
				CObjMgr::Get_Instance()->Add_Object(CreateBullet<CBullet>(fMinAngle, L"M_BossBullet", 1, _fSpeed), _eID);
				fMinAngle += (float)((140 / 3));
			}
		}
		else if (3 == m_iKnightPattern)
		{
			float fMinAngle = m_fAngle - (70);
			for (int i = 0; i < 20; i++)
			{
				fMinAngle += (float)((140 / 20));
				CObjMgr::Get_Instance()->Add_Object(CreateBullet<CBullet>(fMinAngle, L"M_BossBullet", 1, _fSpeed), _eID);
			}
		}
		else
		{
			m_bPattern = false;
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::KNIGHT_ATT);
			CSoundMgr::Get_Instance()->PlaySound(L"Knight_Att.mp3", CSoundMgr::KNIGHT_ATT);
		}
		m_bKnightPattern = false;
	}
	if (m_dwKnightBullet + m_iKnightBullet < GetTickCount())
	{
		m_iKnightPattern++;
		m_bKnightPattern = true;
		m_dwKnightBullet = GetTickCount();
	}


}

void CKnight::Monster_AngleState()
{
	if (!m_bPattern)
	{
		if (m_fAngle < 0)
		{
			if (m_fAngle > -45.f)
			{
				m_eAngleState = STATE::RIGHT;
				m_pFrameKey = L"Knight_Down_Left";
				m_iFrame = 1;
			}
			else if (m_fAngle > -135.f)
			{
				m_eAngleState = STATE::DOWN;
				m_pFrameKey = L"Knight_Down";
				m_iFrame = 2;
			}
			else if (m_fAngle > -180.f)
			{
				m_eAngleState = STATE::LEFT;
				m_pFrameKey = L"Knight_Down_Left";
				m_iFrame = 1;
			}

		}
		else
		{
			if (m_fAngle < 45.f)
			{
				m_eAngleState = STATE::RIGHT;
				m_pFrameKey = L"Knight_Down_Left";
				m_iFrame = 1;
			}
			else if (m_fAngle < 90.f)
			{
				m_eAngleState = STATE::UP_RIGHT;
				m_pFrameKey = L"Knight_Up";
				m_iFrame = 3;
			}
			else if (m_fAngle < 135.f)
			{
				m_eAngleState = STATE::UP_LEFT;
				m_pFrameKey = L"Knight_Up";
				m_iFrame =3;
			}
			else if (m_fAngle < 180.f)
			{
				m_eAngleState = STATE::LEFT;
				m_pFrameKey = L"Knight_Down_Left";
				m_iFrame = 1;
			}
		}
		if (m_eAngleState == STATE::DOWN_RIGHT
			|| m_eAngleState == STATE::RIGHT
			|| m_eAngleState == STATE::UP_RIGHT)
			m_bRightRev = true;

		if (m_eAngleState == STATE::DOWN_LEFT
			|| m_eAngleState == STATE::LEFT
			|| m_eAngleState == STATE::UP_LEFT
			|| m_eAngleState == STATE::DOWN)
			m_bRightRev = false;
	}

}
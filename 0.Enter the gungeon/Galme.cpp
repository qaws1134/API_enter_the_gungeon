#include "stdafx.h"
#include "Galme.h"
#include "ObjMgr.h"
#include "Bullet.h"
#include "BmpMgr.h"
#include "ChargeEffect.h"
#include "BreakBullet.h"
#include "RandomPosBullet.h"
#include "BoomBullet.h"
#include "SoundMgr.h"
CGalme::CGalme()
	: m_bCurPattern(false)
	, m_fMeleeDis(0.f), m_fRangeDis(0.f)
	, m_iPrePattern(0), m_iCurPattern(0)
	, m_fMiddleDis(0.f), m_bLoop(false)
	, m_bJump(false), m_bAttEnd(true), m_eAngleState(ANGLE_IDLE)
	, m_bEffect(false), m_bPrePattern(false)
	, m_iAttState(0), m_iNowState(0), m_iEffectDelay(0), m_dwEffectTime(GetTickCount())
	, m_fPatternDis(0.f), m_bRangeCheck(false)
	, m_fRandomAngle(0.f), m_iJumpPattern(0)
	, m_iRocketRandNum(0), m_bRocketOn(false)
	, m_iRandomDisX(0), m_iRandomDisY(0)
	, m_iReverse(1), m_fRandomSpeed(0.f)
{

}


CGalme::~CGalme()
{
	Release();
}

void CGalme::Initialize()
{
	m_iAtkDis = 100;
	m_fRangeDis = 1200.f;
	m_fMiddleDis = 450.f;
	m_fMeleeDis = 0.f;
	m_fSpeed = 1.f;

	m_iFrameSize = 300;

	m_tInfo.iCX = m_iFrameSize;
	m_tInfo.iCY = m_iFrameSize;

	m_fPosinDis = 110.f;
	m_iAttDelay = 200;
	m_iPatternDelay = 3000;

	m_tStat.iMaxHp = 10;
	m_tStat.iHp = m_tStat.iMaxHp;
	m_tStat.iAtt = 1;
	m_iCurHp = m_tStat.iMaxHp;

	m_eCurState = CObj::IDLE;
	m_pFrameKey = L"Galmea_Down";
	m_eRenderID = RENDERID::OBJECT;

	m_tColInfo.fX = m_tInfo.fX;
	m_tColInfo.fY = m_tInfo.fY;
	m_tColInfo.iCX = 100;
	m_tColInfo.iCY = 100;
}

void CGalme::Release()
{
}

void CGalme::State_Change()
{
	if (m_bDeadStart)
	{
		m_eCurState = CObj::DEAD;
		m_bCurPattern = true;

	}
	if ((m_ePreState != m_eCurState)
		|| (m_bPrePattern != m_bCurPattern))
	{
		switch (m_eCurState)
		{
		case 0:
			if (m_bCurPattern)
			{
				m_tFrame.iStartX = 0;
				m_tFrame.iEndX = 7;
			}
			else
			{
				m_tFrame.iStartX = 0;
				m_tFrame.iEndX = 4;
			}
			m_tFrame.iStateY = WALK;
			m_tFrame.dwDelay = 150;
			m_tFrame.dwTime = GetTickCount();
			break;
		case 1:
			if (m_bCurPattern)
			{
				m_tFrame.iStartX = 0;
				m_tFrame.iEndX = 5;
				m_tFrame.dwDelay = 150;
			}
			else 
			{
				m_tFrame.iStartX = 0;
				m_tFrame.iEndX = 1;
				m_tFrame.dwDelay = 300;
			}
			m_tFrame.iStateY = IDLE;
			m_tFrame.dwTime = GetTickCount();
			break;
		case 2:
			if (m_bCurPattern)
			{
				m_tFrame.iStartX = 0;
				m_tFrame.iEndX = 6;
			}
			else
			{
				m_tFrame.iStartX = 0;
				m_tFrame.iEndX = 2;
			}
			m_tFrame.iStateY = JUMP;
			m_tFrame.dwDelay = 100;
			m_tFrame.dwTime = GetTickCount();
			break;
		case 3:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 9;
			m_tFrame.iStateY = DEAD;
			m_tFrame.dwDelay = 300;
			m_tFrame.dwTime = GetTickCount();
			m_dwStopTime = GetTickCount();
			break;
		case 4:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 5;
			m_tFrame.iStateY = ROCKET;
			m_tFrame.dwDelay = 250;
			m_tFrame.dwTime = GetTickCount();
			m_dwStopTime = GetTickCount();
			break;
		case 6:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 7;
			m_tFrame.iStateY = JUMP_DOWN2;
			m_tFrame.dwDelay = 50;
			m_tFrame.dwTime = GetTickCount();
			m_dwStopTime = GetTickCount();
			break;
		}
		m_ePreState = m_eCurState;
		m_bPrePattern = m_bCurPattern;
	}
	
}

void CGalme::Attack()
{
}



void CGalme::SelectFrame()
{
	//���� ���ϻ��¸� ������Ű�� ���� ���·� �� 
	if (m_bCurPattern)
		m_pFrameKey = L"Galmea_Pattern";
}


void CGalme::Monster_AngleState()
{
	if (m_fAngle < 0)
	{
		if (m_fAngle > -22.5f)
		{
			m_eAngleState = STATE::RIGHT;
			m_pFrameKey = L"Galmea_Left";
		}
		else if (m_fAngle > -67.5f)
		{
			m_eAngleState = STATE::DOWN_RIGHT;
			m_pFrameKey = L"Galmea_Down_Left";
		}
		else if (m_fAngle > -112.5f)
		{
			m_eAngleState = STATE::DOWN;
			m_pFrameKey = L"Galmea_Down";
		}
		else if (m_fAngle > -157.5f)
		{
			m_eAngleState = STATE::DOWN_LEFT;
			m_pFrameKey = L"Galmea_Down_Left";
		}
		else if (m_fAngle > -180.5f)
		{
			m_eAngleState = STATE::LEFT;
			m_pFrameKey = L"Galmea_Left";
		}

	}
	else
	{
		if (m_fAngle < 22.5f)
		{
			m_eAngleState = STATE::RIGHT;
			m_pFrameKey = L"Galmea_Left";
		}
		else if (m_fAngle < 67.5f)
		{
			m_eAngleState = STATE::UP_RIGHT;
			m_pFrameKey = L"Galmea_Up_Left";
		}
		else if (m_fAngle < 112.5f)
		{
			m_eAngleState = STATE::UP;
			m_pFrameKey = L"Galmea_Up";
		}
		else if (m_fAngle < 157.5f)
		{
			m_eAngleState = STATE::UP_LEFT;
			m_pFrameKey = L"Galmea_Up_Left";
		}
		else if (m_fAngle < 180.f)
		{
			m_eAngleState = STATE::LEFT;
			m_pFrameKey = L"Galmea_Left";
		}
	}
	if (m_eAngleState == STATE::DOWN_RIGHT
		|| m_eAngleState == STATE::UP_RIGHT
		|| m_eAngleState == STATE::RIGHT)
		m_bRightRev = true;

	if (m_eAngleState == STATE::DOWN_LEFT
		|| m_eAngleState == STATE::UP_LEFT
		|| m_eAngleState == STATE::LEFT)
		m_bRightRev = false;
}

void CGalme::Attack(int _iPattern)
{
	if (0 == _iPattern)
	{
		m_iAttDelay = 200;
		m_iEffectDelay = 2000;

		Move();
		
		//����Ʈ�� ���۵Ǹ� 1�ʵ��� ��Ʋ�� ����
		//
		if (!m_bEffect)
		{
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::GALMEA_GLODING);
			CSoundMgr::Get_Instance()->PlaySound(L"Galmea_GLoding.mp3", CSoundMgr::GALMEA_GLODING);

			//����Ʈ ���� ���
			m_bEffect = true;
		}
		//����Ʈ�� ���� �� ����
		if (m_dwEffectTime + m_iEffectDelay > GetTickCount())
		{
			dwAttTime = GetTickCount();
		}
		//����Ʈ �� ������

		if (m_dwEffectTime + m_iEffectDelay < GetTickCount())
		{

			if (dwAttTime + m_iAttDelay < GetTickCount())
			{
				CObjMgr::Get_Instance()->Add_Object(CreateBullet<CBullet>(L"M_BossBullet", 30, 1, 4.f), OBJID::M_BULLET);
				dwAttTime = GetTickCount();
				CSoundMgr::Get_Instance()->StopSound(CSoundMgr::GALMEA_BULLET);
				CSoundMgr::Get_Instance()->PlaySound(L"Galmea_Bullet.mp3", CSoundMgr::GALMEA_BULLET);
			}
			
		}
		
		
	}
	else if (1 == _iPattern)
	{
		m_eCurState = CObj::IDLE;
		m_iAttDelay = 1000;
		m_iEffectDelay = 800;
		
		if (!m_bEffect)
		{
			CObj* Effect = CreateBullet<CChargeEffect>((float)m_tPosin.x, (float)m_tPosin.y);
			Effect->Set_Target(this);
			CObjMgr::Get_Instance()->Add_Object(Effect, OBJID::EFFECT);
			m_dwEffectTime = GetTickCount();
			m_bEffect = true;

		}


		if (m_dwEffectTime + m_iEffectDelay > GetTickCount())
		{
			dwAttTime = GetTickCount();
			CSoundMgr::Get_Instance()->PlaySound(L"Galmea_Charge.mp3", CSoundMgr::GALMEA_CHARGE);
		}

		//��ä�� �Ѿ�
		//�ѹ� �� ��ä�� �Ѿ��� �����ų� ��Ʋ�������� �ٲ�

		if (dwAttTime + m_iAttDelay < GetTickCount())
		{
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::GALMEA_SHOTGUN);
			CSoundMgr::Get_Instance()->PlaySound(L"Galmea_ShotGun.mp3", CSoundMgr::GALMEA_SHOTGUN);

			CreateXWayBullet<CBullet>(90.f, 10, 1, 4.f, L"M_BossBullet", OBJID::M_BULLET);
			//���� �� �ٽ� ������ �����ϰų� 0�� �������� ������
			m_iCurPattern = rand() % 2;

			//�ٽ� �߻��ϰų� ��Ʋ���� ��
			if (1 != m_iCurPattern)
				m_bEffect = false;

			dwAttTime = GetTickCount();
		}
		
	
	}
	else if (2 == _iPattern)
	{
		m_eCurState = CObj::IDLE;
		m_iAttDelay = 1000;
		m_iEffectDelay = 800;
		//ū �Ѿ� �� ������ ���� �Ѿ�
		if (!m_bEffect)
		{
			CObj* Effect = CreateBullet<CChargeEffect>((float)m_tPosin.x, (float)m_tPosin.y);
			Effect->Set_Target(this);
			CObjMgr::Get_Instance()->Add_Object(Effect, OBJID::EFFECT);
			m_dwEffectTime = GetTickCount();
			m_bEffect = true;
		}
		if (m_dwEffectTime + m_iEffectDelay > GetTickCount())
		{
			dwAttTime = GetTickCount();
		}
		if (dwAttTime + m_iAttDelay < GetTickCount())
		{
			//�� ������Ʈ�� �װų� ���� �ð��� ������ 360�� �ҷ� ����
			CObjMgr::Get_Instance()->Add_Object(CreateBullet<CBreakBullet>(L"M_BigBullet", 0, 1, 4.f), OBJID::M_BULLET);
			m_iCurPattern = rand() % 2;
			dwAttTime = GetTickCount();
		}
	}


}

void CGalme::Update_Frame()
{
	if (m_tFrame.dwTime + m_tFrame.dwDelay < GetTickCount())
	{
		if (m_bDeadStart)
		{
			if (m_tFrame.dwTime + m_tFrame.dwDelay < GetTickCount())
			{
				++m_tFrame.iStartX;

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
			if (m_bLoop)
			{
				++m_tFrame.iStartX;
				if (m_tFrame.iStartX >= m_tFrame.iEndX)
				{
					m_tFrame.iStartX = 0;
					m_iNowState |= m_iAttState;
				}
			}
			else
			{

				++m_tFrame.iStartX;
				if (m_tFrame.iStartX >= m_tFrame.iEndX)
				{
					m_tFrame.iStartX = m_tFrame.iEndX - 1;

					m_iNowState |= m_iAttState;
				}
			}
			m_tFrame.dwTime = GetTickCount();
		}
	}
		
}


void CGalme::AiState()
{

	switch (m_iNowState)
	{
	case 1:
		//�������� ����
		//�ݺ���a
		m_eCurState = (CObj::STATE)GALMEA_STATE::IDLE;	
		m_bCurPattern = false;
		if (dwPatternTime + m_iPatternDelay < GetTickCount())
		{
			m_bRangeCheck = false;
		}
		break;
	case 2:
		//����
		m_eCurState = (CObj::STATE)GALMEA_PATTERN::JUMP_DOWN;
		m_iAttState = 4;
		m_tColInfo.iCX = 10;
		m_tColInfo.iCY = 10;
		m_iPatternDelay = 9999;
		break;
	case 4:
		m_eCurState = (CObj::STATE)GALMEA_PATTERN::JUMP_DOWN2;
		m_iAttState = 32;
		m_iPatternDelay = 1000;
		dwPatternTime = GetTickCount();
		//���� �ٿ�
		break;
	case 8:
		//����
		m_iRocketRandNum--;
		m_iNowState = 0;
		m_bRocketOn = false;
		m_tFrame.iStartX = 0;
		m_fRandomAngle = (float)(rand() % 60);
		CSoundMgr::Get_Instance()->StopSound(CSoundMgr::GALMEA_ROCKET);
		CSoundMgr::Get_Instance()->PlaySound(L"Galmea_Rocket.mp3", CSoundMgr::GALMEA_ROCKET);
		if (rand() % 2 == 0)
			m_iReverse *= -1;
		m_iRandomDisX = (rand() % 200)*m_iReverse;
		m_iRandomDisY = (rand() % 200)*m_iReverse;
		if (0 == m_iRocketRandNum)
		{
			m_bRangeCheck = false;
			m_bCurPattern = false;
			m_eCurState = (CObj::STATE)GALMEA_STATE::IDLE;
		}
		break;

	case 16:
		//��Ʋ����
		//���� ���� �� ������
		if (dwPatternTime + m_iPatternDelay < GetTickCount())
		{
			m_iPrePattern = m_iCurPattern;
			m_bRangeCheck = false;
		}
		break;
	case 32:
		//���� �ٿ�2
		m_bCurPattern = false;
		m_eCurState = (CObj::STATE)GALMEA_STATE::IDLE;
	
		m_tColInfo.iCX = 100;
		m_tColInfo.iCY = 100;
		if (dwPatternTime + m_iPatternDelay < GetTickCount())
		{
			m_bRangeCheck = false;
		}

		break;
	default:
		break;
	}
	m_iNowState = 0;

	//������ �������� ����üũ

	if (!m_bRangeCheck)
	{
		if (RangeCheck(m_fMeleeDis))
		{
			m_fPatternDis = m_fMeleeDis;
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::GALMEA_MELEE);
			CSoundMgr::Get_Instance()->PlaySound(L"Galmea_Melee.mp3", CSoundMgr::GALMEA_MELEE);
			m_eCurState = (CObj::STATE)GALMEA_PATTERN::MELEE_ATTACK;
			m_bCurPattern = true;
			m_bLoop = false;
			m_bRangeCheck = true;
			m_iAttState = 1;
			m_iPatternDelay = 1000;
		}
		else if (RangeCheck(m_fMiddleDis))
		{
			m_fPatternDis = m_fMiddleDis;

			dwPatternTime = GetTickCount();
			m_iPatternDelay = 6000;
			m_iAttState = 16;
			m_bEffect = false;
			m_iCurPattern = rand() % 3;
			m_bCurPattern = false;
			m_bLoop = true;
			m_bRangeCheck = true;
		}
		else if (RangeCheck(m_fRangeDis))
		{
			m_fPatternDis = m_fRangeDis;
			m_iCurPattern = rand() % 2;

			//����
			if (m_iCurPattern == 0)
			{
				m_iAttState = 8;
				m_eCurState = (CObj::STATE)GALMEA_PATTERN::ROCKET;
				m_fRandomAngle = (float)(rand() % 60);
				m_iRandomDisX = rand() % 20;
				m_iRandomDisX = rand() % 20;
				m_iRocketRandNum = (rand() % 5) + 3;	//3������ 8�� ����
				CSoundMgr::Get_Instance()->StopSound(CSoundMgr::GALMEA_ROCKET);
				CSoundMgr::Get_Instance()->PlaySound(L"Galmea_Rocket.mp3", CSoundMgr::GALMEA_ROCKET);
			}
			else
			{
				//����
				m_iAttState = 2;
				CSoundMgr::Get_Instance()->StopSound(CSoundMgr::GALMEA_JUMP);
				CSoundMgr::Get_Instance()->PlaySound(L"Galmea_Jump.mp3", CSoundMgr::GALMEA_JUMP);

				m_eCurState = (CObj::STATE)GALMEA_PATTERN::JUMP;
				m_fRandomAngle = (float)(rand() % 360);
				m_iJumpPattern = rand() % 3;
				m_fRandomSpeed = (float)(rand() % 10) + 10;
				m_fPlayerX = (m_pTarget->Get_Info().fX);
				m_fPlayerY = (m_pTarget->Get_Info().fY) ;

			}
			m_bCurPattern = true;
			m_bRangeCheck = true;
			m_bLoop = false;
		}
		else
			Move();
		dwPatternTime = GetTickCount();
	}
	else
	{
		//���� ����
		TargetCheck();
		if (m_fMiddleDis == m_fPatternDis)
		{
			Attack(m_iCurPattern);
		}
		else if (m_fRangeDis == m_fPatternDis)
		{
			if (0 == m_iCurPattern)
			{
				Rocket();
			}
			else
			{
				Jump();
			}
		}
	}
}


void CGalme::Jump()
{
	//���� �ٿ�
	if (4 == m_iAttState)
	{
		float fX = m_fPlayerX - m_tInfo.fX;
		float fY = m_fPlayerY - m_tInfo.fY;
		float fDia = sqrtf(fX * fX + fY * fY);
		float fRad = acosf(fX / fDia);
		m_fAngle = fRad * 180.f / PI;
		if (m_tInfo.fY < m_fPlayerY)
			m_fAngle *= -1.f;

		if(!(m_tInfo.fX >m_fPlayerX-20.f && m_tInfo.fX<m_fPlayerX + 20.f))
			m_tInfo.fX += cosf(m_fAngle  * PI / 180.f) * (m_fSpeed + m_fRandomSpeed);
		if (!(m_tInfo.fY >m_fPlayerY - 20.f && m_tInfo.fY<m_fPlayerY + 20.f))
			m_tInfo.fY -= sinf(m_fAngle  * PI / 180.f) * (m_fSpeed + m_fRandomSpeed);
	}
}


void CGalme::Rocket()
{
	if (!m_bRocketOn)
	{
		//��������Ʈ
		CObj* Rocket = CreateBullet<CRandomPosBullet>(L"M_RandomPosBullet", 0, 0, 0.1f);
		Rocket->Set_Pos(m_tInfo.fX, m_tInfo.fY);
		CObjMgr::Get_Instance()->Add_Object(Rocket, OBJID::EFFECT);

		//Ÿ�� ����Ʈ

		CObj* TargetEffect = CreateBullet<CBoomBullet>(L"M_RandomPosEffect", 0, 0, 0.f);
		if (!m_pTarget)
			return;
		TargetEffect->Set_Pos(m_pTarget->Get_Info().fX + (float)m_iRandomDisX, m_pTarget->Get_Info().fY+ (float)m_iRandomDisX);
		CObjMgr::Get_Instance()->Add_Object(TargetEffect, OBJID::EFFECT);


		m_bRocketOn = true;
	}
}

void CGalme::Load_Init()
{
}







void CGalme::TargetCheck()
{
	m_pTarget = CObjMgr::Get_Instance()->Get_Player();
	if (!m_pTarget)
		return;
	float fX = m_pTarget->Get_Info().fX - m_tInfo.fX;
	float fY = m_pTarget->Get_Info().fY - m_tInfo.fY;
	float fDia = sqrtf(fX * fX + fY * fY);
	float fDis = (float)((m_pTarget->Get_Info().iCX + m_tInfo.iCX) >> 1) ;


	float	fRad = acosf(fX / fDia);

	m_fAngle = fRad * 180.f / PI;

	if (m_tInfo.fY < m_pTarget->Get_Info().fY)
		m_fAngle *= -1.f;

	m_tPosin.x = (LONG)(m_tInfo.fX + cosf(m_fAngle*PI / 180.f)*m_fPosinDis);
	m_tPosin.y = (LONG)(m_tInfo.fY - sinf(m_fAngle*PI / 180.f)*m_fPosinDis);

}




	//if (RangeCheck(m_fRangeDis))
	//{

	//	if (dwPatternTime + m_iPatternDelay < GetTickCount())
	//	{
	//		m_iCurPattern = rand() % 2;
	//		dwPatternTime = GetTickCount();
	//		m_bEffect = false;
	//		m_iPrePattern = m_iCurPattern;
	//	}
	//	if (0 == m_iCurPattern)
	//	{
	//		m_eCurState = (CObj::STATE)GALMEA_PATTERN::JUMP;
	//		m_bCurPattern = true;
	//		m_bLoop = false;
	//		m_iAttState = 1;	//�������� ����
	//		m_bAttEnd = false;
	//	}
	//	else
	//	{
	//		m_eCurState = (CObj::STATE)GALMEA_PATTERN::ROCKET;
	//		m_bCurPattern = true;
	//		m_bLoop = false;
	//		m_iAttState = 1;	//�������� ����
	//		m_bAttEnd = false;
	//	}
	//}

	
/*	else
		Move();*/



	//if (RangeCheck(m_fRangeDis))
	//{
	//		
	//	if (dwAttTime + m_iPatternDelay < GetTickCount())
	//	{
	//		m_iCurPattern = rand() % 2;
	//	}
	//	if (0 == m_iCurPattern)
	//	{
	//		m_eCurState = (CObj::STATE)GALMEA_PATTERN::JUMP;
	//		m_bPattern = true;
	//		m_bLoop = false;
	//		m_bJump = true;
	//		//Jump();
	//		m_iCurPattern = 1;
	//		dwAttTime = GetTickCount();
	//	}
	//	else
	//	{
	//		m_eCurState = (CObj::STATE)GALMEA_PATTERN::ROCKET;
	//		m_bPattern = true;
	//		m_bLoop = true;
	//		//Rocket();
	//	}
		
	//}

	//if (Follow())
	//{
	//	m_eCurState = CObj::IDLE;
	//}
	//else
	//{
	//	
	//}
	//

	//Attack();



bool CGalme::RangeCheck(float _fRange)
{
	m_pTarget = CObjMgr::Get_Instance()->Get_Player();
	if (!m_pTarget)
		return false;
	float fX = m_pTarget->Get_Info().fX - m_tInfo.fX;
	float fY = m_pTarget->Get_Info().fY - m_tInfo.fY;
	float fDia = sqrtf(fX * fX + fY * fY);
	float fDis = (float)((m_pTarget->Get_Info().iCX + m_tInfo.iCX) >> 1) + _fRange;


	float	fRad = acosf(fX / fDia);

	m_fAngle = fRad * 180.f / PI;

	if (m_tInfo.fY < m_pTarget->Get_Info().fY)
		m_fAngle *= -1.f;

	int offsetX = 0;
	int offsetY = 0;

	m_tPosin.x = (LONG)(m_tInfo.fX + cosf(m_fAngle*PI / 180.f)*m_fPosinDis);
	m_tPosin.y = (LONG)(m_tInfo.fY - sinf(m_fAngle*PI / 180.f)*m_fPosinDis);



	//�������� �� ����Ÿ���� ��� �ش�
	//if(!m_bAttEnd)
	//	dwPatternTime = GetTickCount();

	if (fDia <= fDis)
	{
		return true;
	}

	return false;
}


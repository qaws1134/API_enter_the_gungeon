#include "stdafx.h"
#include "Player.h"
#include "KeyMgr.h"
#include "ObjMgr.h"
#include "Bullet.h"
#include "BlankBullet.h"
#include "Weapon.h"
#include "BmpMgr.h"
#include "ScrollMgr.h"
#include "SoundMgr.h"

CPlayer::CPlayer()
	: m_bJump(false),m_eAngleState(IDLE)
	,m_fJumpPower(0.f),m_fJumpStart(0.f)
	, m_dwJumpStopTime(GetTickCount()), m_iJumpEnd(0)
	,m_bMove(false)
{
	ZeroMemory(&m_tMouse, sizeof(m_tMouse));
	m_vecWeapon.reserve(10);
}


CPlayer::~CPlayer()
{
	Release();
}


void CPlayer::Initialize()
{

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Down.bmp", L"Player_Down");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Down_Left.bmp", L"Player_Down_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Up_Left.bmp", L"Player_Up_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Player/Player_Up.bmp", L"Player_Up");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stretch.bmp", L"Stretch");
	m_tInfo.fX = 9000;
	m_tInfo.fY = 5650;
	m_tInfo.iCX = 96;
	m_tInfo.iCY = 96;

	m_fPosinDis = 35.f;
	m_fInitSpeed = 5.f;
	
	m_fJumpPower = 3.f;

	m_tColInfo.fX = m_tInfo.fX;
	m_tColInfo.fY = m_tInfo.fY;
	m_tColInfo.iCX = 50;
	m_tColInfo.iCY = 50;

	//무기 획득
	m_vecWeapon.emplace_back(static_cast<CWeapon*>(CObjMgr::Get_Instance()->Get_Weapon(WEAPONID::OLDGUN)));

	m_vecWeapon.emplace_back(static_cast<CWeapon*>(CObjMgr::Get_Instance()->Get_Weapon(WEAPONID::CROSSBOW)));

	m_vecWeapon.emplace_back(static_cast<CWeapon*>(CObjMgr::Get_Instance()->Get_Weapon(WEAPONID::WAY5SHOTGUN)));


	m_tStat.iMaxHp = 6;
	m_tStat.iHp = m_tStat.iMaxHp;
	m_tStat.iAtt = 1;
	m_tStat.iGold = 0;
	m_tStat.iBlank = 2;
	m_tStat.iKey = 2;

	m_eWeapon = WEAPONID::OLDGUN;
	m_eCurState = CObj::STATE::IDLE;
	m_pFrameKey = L"Player_Down";
	m_eRenderID = RENDERID::OBJECT;
	

	//m_vecWeapon[0]->Set_Target(this);

	m_CurWeapon = m_vecWeapon[0];
	m_CurWeapon->Set_Target(this);

}

int CPlayer::Update()
{
	//if (m_bDead)
	//	return OBJ_DEAD;
	MousePos_Check();
	Key_Check();

	Player_AngleState();

	State_Change();
	Update_Frame();
	Update_Rect();
	Update_ColRect();

	Keybord_OffSet();
	Mouse_OffSet();
	return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
	m_bSuper = m_bJump;
	SuperTime();
	m_tColInfo.fX = (m_tInfo.fX) + (float)(CScrollMgr::Get_Instance()->Get_ScrollX());
	m_tColInfo.fY = (m_tInfo.fY) + (float)(CScrollMgr::Get_Instance()->Get_ScrollY());
}

void CPlayer::Render(HDC _DC)
{
	Update_Rect();
	Update_ColRect();
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	 hMemDC = CBmpMgr::Get_Instance()->Find_Bmp(m_pFrameKey);
	 hResetDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Reset");
	 hPlgDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Plg");

	if ((((m_eState == UP_RIGHT||m_eState == DOWN_RIGHT||m_eState== RIGHT)&&m_bJump)
		||(m_eAngleState == UP_RIGHT|| m_eAngleState == DOWN_RIGHT)) && m_bRightRev)
	{
		 hStretchDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Stretch");

		StretchBlt(hStretchDC
			, 0, 0
			, 96, 96
			, hMemDC
			, m_tFrame.iStartX * 96 + 96, m_tFrame.iStateY * 96
			, -96, 96
			, SRCCOPY);

		GdiTransparentBlt(_DC
			, m_tRect.left+ iScrollX, m_tRect.top+ iScrollY
			, m_tInfo.iCX, m_tInfo.iCY
			, hStretchDC
			, 0,0
			, 96, 96
			, RGB(255, 0, 255));
	}
	else
	{
		GdiTransparentBlt(_DC
			, m_tRect.left + iScrollX, m_tRect.top + iScrollY
			, m_tInfo.iCX, m_tInfo.iCY
			, hMemDC
			, m_tFrame.iStartX * 96, m_tFrame.iStateY * 96
			, 96, 96
			, RGB(255, 0, 255));
	}

	BitBlt(hPlgDC, 0, 0, 300, 300, hResetDC, 0, 0, SRCCOPY);

	DrawColRect(_DC);
}

void CPlayer::Release()
{
}


void CPlayer::Key_Check()
{
	
	//이동
	if (!m_bJump)
	{
		if (CKeyMgr::Get_Instance()->Key_Press('A'))
		{
			if (CKeyMgr::Get_Instance()->Key_Press('W'))		
				m_eState = STATE::UP_LEFT;
			else if (CKeyMgr::Get_Instance()->Key_Press('S'))
				m_eState = STATE::DOWN_LEFT;
			else
				m_eState = STATE::LEFT;
			CSoundMgr::Get_Instance()->PlaySound(L"Player_Walk.mp3", CSoundMgr::PLAYER_WALK);
		}
		else if (CKeyMgr::Get_Instance()->Key_Press('D'))
		{
			if (CKeyMgr::Get_Instance()->Key_Press('W'))
				m_eState = STATE::UP_RIGHT;
			else if (CKeyMgr::Get_Instance()->Key_Press('S'))
				m_eState = STATE::DOWN_RIGHT;
			else
				m_eState = STATE::RIGHT;

			CSoundMgr::Get_Instance()->PlaySound(L"Player_Walk.mp3", CSoundMgr::PLAYER_WALK);
		}
		else if (CKeyMgr::Get_Instance()->Key_Press('W'))
		{
			m_eState = STATE::UP;
			CSoundMgr::Get_Instance()->PlaySound(L"Player_Walk.mp3", CSoundMgr::PLAYER_WALK);
		}
		else if (CKeyMgr::Get_Instance()->Key_Press('S'))
		{
			m_eState = STATE::DOWN;

			CSoundMgr::Get_Instance()->PlaySound(L"Player_Walk.mp3", CSoundMgr::PLAYER_WALK);
		}
		else
		{
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::PLAYER_WALK);
			m_eState = STATE::IDLE;
			m_eCurState = CObj::STATE::IDLE;
		}

		if (m_eState != STATE::IDLE)
		{
			m_fSpeed = m_fInitSpeed;
			m_eCurState = CObj::STATE::WALK;
		}
		Move();
	}


	//==============공포탄====================
	if (CKeyMgr::Get_Instance()->Key_Down('Q'))
	{
		if (m_tStat.iBlank != 0)
		{
			m_tStat.iBlank--;
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::PLAYER_BLANK);
			CSoundMgr::Get_Instance()->PlaySound(L"Player_Blank.mp3", CSoundMgr::PLAYER_BLANK);
			CObjMgr::Get_Instance()->Add_Object(CreateBullet<CBlankBullet>(m_tInfo.fX, m_tInfo.fY), OBJID::DEL_BULLET);
		}
	}
	//==============점프====================	
	Jump();

	//==============공격====================	
	
	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		if (0 >= m_CurWeapon->Get_Reload() )
			m_CurWeapon->Set_ReloadOn(true);

		Bullet_Shot();
	}
	//==============장전====================	
	if (CKeyMgr::Get_Instance()->Key_Down('R'))
	{
		m_CurWeapon->Set_ReloadOn(true);
	}
	//==============무기 변경====================	
	if (CKeyMgr::Get_Instance()->Key_Down(VK_ONE))
	{
		Select_Weapon(0);
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_TWO))
	{
		Select_Weapon(1);
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_THREE))
	{
		Select_Weapon(2);
	}
	//==============상호 작용====================	
	if (CKeyMgr::Get_Instance()->Key_Down('E'))
	{
		//오브젝트와 상호작용
		m_bInterection = true;
	}


	//치트
	if (CKeyMgr::Get_Instance()->Key_Down(VK_NUMPAD0))
	{
		m_tStat.iBlank = 2;
	}
	if (CKeyMgr::Get_Instance()->Key_Down(VK_NUMPAD1))
	{
		//오브젝트와 상호작용
		m_tStat.iHp = 6;
	}
}

void CPlayer::MousePos_Check()
{

	float fX =  m_tMouse.x - (m_tInfo.fX);
	float fY =  m_tMouse.y - (m_tInfo.fY);

	float fDia = sqrtf(fX*fX + fY*fY);
	float fRad = acosf(fX / fDia);

	m_fAngle = fRad* 180.f/PI;


if ( m_tInfo.fY < m_tMouse.y)
		m_fAngle *= -1.f;

	m_tPosin.x = (LONG)(m_tInfo.fX + cosf(m_fAngle*PI / 180.f)*m_fPosinDis);
	m_tPosin.y = (LONG)(m_tInfo.fY - sinf(m_fAngle*PI / 180.f)*m_fPosinDis);
}


#define Angle_DR_Min -60.f
#define Angle_D -120.f
#define Angle_DL_Min -180.f
#define Angle_DL_Max 30.f
#define Angle_UR_Max 60.f
#define Angle_U 120.f
#define Angle_UL_Min 150.f
#define Angle_UL_Max 180.f


void CPlayer::Player_AngleState()
{
	if (!m_bJump)
	{
		if (m_fAngle < 0)
		{
			if (m_fAngle > Angle_DR_Min)
			{
				m_eAngleState = STATE::DOWN_RIGHT;
				m_pFrameKey = L"Player_Down_Left";
			}
			else if (m_fAngle > Angle_D)
			{
				m_eAngleState = STATE::DOWN;
				m_pFrameKey = L"Player_Down";
			}
			else if (m_fAngle > Angle_DL_Min)
			{
				m_eAngleState = STATE::DOWN_LEFT;
				m_pFrameKey = L"Player_Down_Left";
			}
		}
		else 
		{
			if (m_fAngle < 30.f)
			{
				m_eAngleState = STATE::DOWN_RIGHT;
				m_pFrameKey = L"Player_Down_Left";
			}
			else if (m_fAngle < 60.f)
			{
				m_eAngleState = STATE::UP_RIGHT;
				m_pFrameKey = L"Player_Up_Left";
			}


			else if (m_fAngle < 120.f)
			{
				m_eAngleState = STATE::UP;
				m_pFrameKey = L"Player_Up";
			}
			else if (m_fAngle < 150.f)
			{
				m_eAngleState = STATE::UP_LEFT;
				m_pFrameKey = L"Player_Up_Left";
			}
			else if (m_fAngle < 180.f)
			{
				m_eAngleState = STATE::DOWN_LEFT;
				m_pFrameKey = L"Player_Down_Left";
			}
		}
		if (m_eAngleState == STATE::DOWN_RIGHT
			|| m_eAngleState == STATE::UP_RIGHT)
			m_bRightRev = true;

		if (m_eAngleState == STATE::DOWN_LEFT
			|| m_eAngleState == STATE::UP_LEFT)
			m_bRightRev = false;
	}

}

void CPlayer::Jump()
{
	if (m_bJump)
	{
		//해당 방향 키값  
		//해당 방향 m_estate
		Move();
		m_fSpeed -= 0.15f;
		if (m_fSpeed < 0.f)
		{
			m_bJump = false;
			m_fSpeed = m_fJumpStart;
			m_eCurState = CObj::STATE::IDLE;
		}
	}

	if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
	{
		if (!m_bJump)
		{
			m_bJump = true;
			m_fJumpStart = m_fSpeed;
			m_fSpeed += m_fJumpPower;
			if(m_eCurState != CObj::STATE::IDLE)
				m_eCurState = CObj::STATE::JUMP;
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::PLAYER_WALK);
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::PLAYER_JUMP);
			CSoundMgr::Get_Instance()->PlaySound(L"Player_Jump.mp3", CSoundMgr::PLAYER_JUMP);
			switch (m_eState)
			{
			case CPlayer::UP:
				m_pFrameKey = L"Player_Up";
				m_iJumpEnd = 10;
				break;
			case CPlayer::UP_LEFT:
				m_pFrameKey = L"Player_Up_Left";
				m_iJumpEnd = 8;
				break;
			case CPlayer::LEFT:
				m_pFrameKey = L"Player_Down_Left";
				m_iJumpEnd = 9;
				break;
			case CPlayer::DOWN_LEFT:
				m_pFrameKey = L"Player_Down_Left";
				m_iJumpEnd = 9;
				break;
			case CPlayer::DOWN:
				m_pFrameKey = L"Player_Down";
				m_iJumpEnd = 9;
				break;
			case CPlayer::DOWN_RIGHT:
				m_pFrameKey = L"Player_Down_Left";
				m_iJumpEnd = 9;
				break;
			case CPlayer::RIGHT:
				m_pFrameKey = L"Player_Down_Left";
				m_iJumpEnd = 9;
				break;
			case CPlayer::UP_RIGHT:
				m_pFrameKey = L"Player_Up_Left";
				m_iJumpEnd = 8;
				break;
			}
		}
	}
}

#define CrossOffset 2.f

void CPlayer::Move()
{
	switch (m_eState)
	{
	case CPlayer::UP:
		m_tInfo.fY -= m_fSpeed;
		break;
	case CPlayer::UP_LEFT:
		m_tInfo.fX -= m_fSpeed / sqrtf(CrossOffset);
		m_tInfo.fY -= m_fSpeed / sqrtf(CrossOffset);
		m_bRightRev = false;
		break;
	case CPlayer::IDLE:
		m_fSpeed = 0.f;
		break;

	}

}


void CPlayer::Bullet_Shot()
{
	if (!m_bJump)
	{
		if (m_CurWeapon->Weapon_Delay())
		{
			if (WEAPONID::OLDGUN == m_eWeapon)
			{
				m_CurWeapon->Use_Bullet();
				CObjMgr::Get_Instance()->Add_Object(CreateBullet<CBullet>(L"Normal", 10, 2, 5.f), OBJID::P_BULLET);
				return;
			}
			if (WEAPONID::CROSSBOW == m_eWeapon)
			{
				m_CurWeapon->Use_Bullet();
				CObjMgr::Get_Instance()->Add_Object(CreateBullet<CBullet>(L"BowBullet", 5, 6, 10.f), OBJID::P_BULLET);
				return;
			}
			if (WEAPONID::WAY5SHOTGUN == m_eWeapon)
			{
				m_CurWeapon->Use_Bullet();
				CreateXWayBullet<CBullet>(90.f, 5.f, 2, 4.f, L"Normal", OBJID::P_BULLET);
				return;
			}
		}
	}
}

void CPlayer::State_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case CObj::WALK:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 6;
			m_tFrame.iStateY = WALK;
			m_tFrame.dwDelay = 100;
			m_tFrame.dwTime = GetTickCount();
			break;
		case CObj::IDLE:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 3;
			m_tFrame.iStateY = CObj::STATE::IDLE;
			m_tFrame.dwDelay = 300;
			m_tFrame.dwTime = GetTickCount();
			break;
		case CObj::JUMP:
			m_tFrame.iStartX = 0;
			m_tFrame.iEndX = 9;
			m_tFrame.iStateY = JUMP;
			m_tFrame.dwDelay = 80;
			m_tFrame.dwTime = GetTickCount();
			m_dwJumpStopTime = GetTickCount();
			break;
		case CObj::HIT:
			break;
		case CObj::DEAD:
			break;
		case CObj::END:
			break;
		default:
			break;
		}
		m_ePreState = m_eCurState;
	}

}

void CPlayer::Weapon_Check()
{
	auto iter = m_vecWeapon.begin();
	for (; iter != m_vecWeapon.end();)
	{
		if ((*iter)->Get_Target()) 
			(*iter)->Set_Target(nullptr);
		
		iter++;
	}
}


void CPlayer::Update_Frame()
{

	if (m_bJump)
	{
		if (m_tFrame.dwTime + m_tFrame.dwDelay < GetTickCount())
		{
			++m_tFrame.iStartX;

			if (m_tFrame.iStartX == m_iJumpEnd)
			{
				--m_tFrame.iStartX;
			}
			m_tFrame.dwTime = GetTickCount();
		}
	}
	else
	{
		if (m_tFrame.dwTime + m_tFrame.dwDelay < GetTickCount())
		{
			++m_tFrame.iStartX;
			if (m_tFrame.iStartX >= m_tFrame.iEndX)
				m_tFrame.iStartX = 0;
			m_tFrame.dwTime = GetTickCount();
		}
	}
}

void CPlayer::Select_Weapon(int _iKeynum)
{
	m_CurWeapon = m_vecWeapon[_iKeynum];
	m_CurWeapon->Get_WeaponID();
	m_eWeapon = m_CurWeapon->Get_WeaponID();
	Weapon_Check();
	m_CurWeapon->Set_Target(this);
}



void CPlayer::Keybord_OffSet()
{
	int iOffSetX = WINCX >> 1;
	int iOffSetY = WINCY >> 1;
	float iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();

	if (iOffSetX < (m_tInfo.fX + iScrollX)) 
	{
		CScrollMgr::Get_Instance()->Set_ScrollX(iOffSetX - (m_tInfo.fX + iScrollX));
	}
	if (iOffSetX > (m_tInfo.fX + iScrollX))
	{
		CScrollMgr::Get_Instance()->Set_ScrollX(iOffSetX - (m_tInfo.fX + iScrollX));
	}
	if (iOffSetY < (m_tInfo.fY + iScrollY)) 
	{
		CScrollMgr::Get_Instance()->Set_ScrollY(iOffSetY - (m_tInfo.fY + iScrollY));
	}
	if (iOffSetY > (m_tInfo.fY + iScrollY))
	{
		CScrollMgr::Get_Instance()->Set_ScrollY(iOffSetY - (m_tInfo.fY + iScrollY));
	}
}

void CPlayer::Mouse_OffSet()
{
	int iOffSetX =  (WINCX>>1);
	int iOffSetY = (WINCY >> 1);
	float iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX();
	float iScrollY = CScrollMgr::Get_Instance()->Get_ScrollY();
	
	GetCursorPos(&m_tMouse);
	ScreenToClient(g_hWnd, &m_tMouse);

	m_tMouse.x -= (LONG)iScrollX;
	m_tMouse.y -= (LONG)iScrollY;

	if (iOffSetX > (m_tMouse.x + iScrollX)) {
		CScrollMgr::Get_Instance()->Set_ScrollX(((float)((iOffSetX - (m_tMouse.x + (int)iScrollX))>>1)));
	}
	if (iOffSetX <(m_tMouse.x + iScrollX)) {
		CScrollMgr::Get_Instance()->Set_ScrollX((float)((iOffSetX - (m_tMouse.x + (int)iScrollX))>>1));
	}
	if (iOffSetY > (m_tMouse.y + iScrollY))
	{
		CScrollMgr::Get_Instance()->Set_ScrollY((float)((iOffSetY - (m_tMouse.y + (int)iScrollY))>>1));
	}
	if (iOffSetY < (m_tMouse.y + iScrollY))
	{
		CScrollMgr::Get_Instance()->Set_ScrollY((float)((iOffSetY - (m_tMouse.y + (int)iScrollY))>>1));
	}

}
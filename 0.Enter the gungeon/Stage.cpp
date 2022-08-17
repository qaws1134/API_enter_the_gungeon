#include "stdafx.h"
#include "Stage.h"
#include "ObjMgr.h"
#include "ScrollMgr.h"
#include "BmpMgr.h"
#include "TileMgr.h"
#include "KeyMgr.h"

#include "Player.h"

#include "Weapon.h"
#include "OldGun.h"
#include "CrossBow.h"
#include "Way5ShotGun.h"
#include "GunDeadGun.h"

#include "GunDead.h"
#include "RedGunDead.h"
#include "BlueGunDead.h"
#include "Galme.h"
#include "Mage.h"
#include "Knight.h"


#include "SoundMgr.h"


CStage::CStage()
	: m_pFrameKey(L""), m_iFrameSIze(0), m_pUIWeapon(nullptr), m_szNowBullet(L"")
	, m_bStart(false)


{
	ZeroMemory(&m_tPlayerStat, sizeof(m_tPlayerStat));
	ZeroMemory(&FrameState, sizeof(FrameState));
}

CStage::~CStage()
{
	Release();
}

void CStage::Initialize()
{


	CSoundMgr::Get_Instance()->PlayBGM(L"StageBmg.mp3");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Stretch.bmp", L"Stretch");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Plg.bmp", L"Plg");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Reset.bmp", L"Reset");


	//========================몬스터============================== 

	//건데드
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/GunDead/GunDead_Up_Left.bmp", L"GunDead_Up_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/GunDead/GunDead_Down_Left.bmp", L"GunDead_Down_Left");
	
	//레드건데드
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/RedGunDead/RedGunDead_Up_Left.bmp", L"RedGunDead_Up_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/RedGunDead/RedGunDead_Down_Left.bmp", L"RedGunDead_Down_Left");

	//블루건데드
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/BlueGunDead/BlueGunDead_Up_Left.bmp", L"BlueGunDead_Up_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/BlueGunDead/BlueGunDead_Down_Left.bmp", L"BlueGunDead_Down_Left");

	//마법사
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Mage/Mage_Down_Left.bmp", L"Mage_Down_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Mage/Mage_Up_Left.bmp", L"Mage_Up_Left");

	//기사
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Knight/Knight_Down.bmp", L"Knight_Down");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Knight/Knight_Up.bmp", L"Knight_Up");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Knight/Knight_Down_Left.bmp", L"Knight_Down_Left");

	//총탄박쥐
	


	//새
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Bird/Bird.bmp", L"Bird");

	//책
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Book/Book.bmp", L"Book");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/BulletBat/BulletBat.bmp", L"BulletBat");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/BulletBat/ShotBat.bmp", L"ShotBat");

	//핀헤드
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/PinHead/PinHead_Down.bmp", L"PinHead_Down");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/PinHead/PinHead_Up.bmp", L"PinHead_Up");


	//갈매기관총
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Boss_Galmea/Boss_Left.bmp", L"Galmea_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Boss_Galmea/Boss_Down_Left.bmp", L"Galmea_Down_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Boss_Galmea/Boss_Up_Left.bmp", L"Galmea_Up_Left");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Boss_Galmea/Boss_Up.bmp", L"Galmea_Up");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Boss_Galmea/Boss_Down.bmp", L"Galmea_Down");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Monster/Boss_Galmea/Boss_Pattern.bmp", L"Galmea_Pattern");


	//========================무기==============================
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Weapon/OldGun/OldGun.bmp", L"OldGun");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Weapon/CrossBow/CrossBow.bmp", L"CrossBow");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Weapon/Way5ShotGun/Way5ShotGun.bmp", L"Way5ShotGun");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Weapon/GunDeadGun/GunDeadGun.bmp", L"GunDeadGun");

	//========================총알==============================
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/Normal.bmp", L"Normal");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/CrossBow.bmp", L"BowBullet");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/M_Normal.bmp", L"M_Normal");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/BlankShot.bmp", L"BlankShot");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/M_BigBullet.bmp", L"M_BigBullet");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/M_BossBullet.bmp", L"M_BossBullet");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/M_RandomPosBullet.bmp", L"M_RandomPosBullet");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Bullet/M_RandomPosEffect.bmp", L"M_RandomPosEffect");

	//========================필드오브젝트==============================
	
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Object/FieldItem.bmp", L"FieldItem");



	//========================맵==============================
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Tile/Tile.bmp", L"Tile");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Map/Map.bmp", L"Stage1");



	//========================UI==============================
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/UI.bmp", L"PlayerUI");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/UI/WeaponBox.bmp", L"WeaponBox");

	CObjMgr::Get_Instance()->Load_Monster();
	//플레이어 무기
	CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<COldGun>::Create(WEAPONID::OLDGUN,L"OldGun"), OBJID::WEAPON);
	CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CCrossBow>::Create(WEAPONID::CROSSBOW, L"CrossBow"), OBJID::WEAPON);
	CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CWay5ShotGun>::Create(WEAPONID::WAY5SHOTGUN, L"Way5ShotGun"), OBJID::WEAPON);
	

	
	CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CPlayer>::Create(OBJID::PLAYER), OBJID::PLAYER);

	//CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CGunDead>::Create(8000.f, 5600.f, OBJID::MONSTER,1), OBJID::MONSTER);
	//CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CRedGunDead>::Create(8000.f, 5800.f, OBJID::MONSTER,1), OBJID::MONSTER);
	CTileMgr::Get_Instance()->Load_Tile();
	m_pFrameKey = L"PlayerUI";
	m_iFrameSIze = 50;
}

void CStage::Update()
{



	if (CKeyMgr::Get_Instance()->Key_Down('O'))
	{
		CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CGalme>::Create(8000.f, 5400.f, OBJID::MONSTER, 1), OBJID::MONSTER);
		//CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CGunDead>::Create(8000.f, 5400.f, OBJID::MONSTER, 1), OBJID::MONSTER);
		//CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CMage>::Create(8000.f, 5600.f, OBJID::MONSTER, 1), OBJID::MONSTER);*/
		//CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CKnight>::Create(8000.f, 5600.f, OBJID::MONSTER, 1), OBJID::MONSTER);
		//CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CBlueGunDead>::Create(8000.f, 5600.f, OBJID::MONSTER,1), OBJID::MONSTER);
		//CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CRedGunDead>::Create(8000.f, 5800.f, OBJID::MONSTER,1), OBJID::MONSTER);

	}
	CObjMgr::Get_Instance()->Update();
	if (CObjMgr::Get_Instance()->Get_Player())
	{
		m_tPlayerStat = CObjMgr::Get_Instance()->Get_Player()->Get_Stat();
		if (static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_CurWeapon())
		{
			m_pUIWeapon = static_cast<CPlayer*>(CObjMgr::Get_Instance()->Get_Player())->Get_CurWeapon();
			if(m_pUIWeapon->Get_MaxBullet() < 2000)
				swprintf_s(m_szNowBullet, L"%d / %d", m_pUIWeapon->Get_MaxBullet(), m_pUIWeapon->Get_InitMaxBullet());
			else
				swprintf_s(m_szNowBullet, L"∞");
		}
	}
}

void CStage::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	CScrollMgr::Get_Instance()->Scroll_Lock();
}

void CStage::Render(HDC _DC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Stage1");
	HDC hWeaponBox = CBmpMgr::Get_Instance()->Find_Bmp(L"WeaponBox");
	CTileMgr::Get_Instance()->Render(_DC);
	BitBlt(_DC, 0, 0, WINCX, WINCY, hMemDC, -iScrollX, -iScrollY, SRCCOPY);

	CObjMgr::Get_Instance()->Render(_DC);

	Player_HP(_DC);
	Palyer_Blank(_DC);

	TextOut(_DC, 1090, 670,m_szNowBullet,lstrlen(m_szNowBullet));

	GdiTransparentBlt(_DC
		, 1050, 690
		, 110, 80
		, hWeaponBox
		, 0,0
		, 110, 80
		, RGB(255, 0, 255));

	if(m_pUIWeapon)
		m_pUIWeapon->Get_WeaponUI(_DC);
}

void CStage::Release()
{

}


void CStage::UI_Render(HDC _DC, int X, int Y, float FrameX, float FrameY)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Bmp(L"PlayerUI");
	GdiTransparentBlt(_DC
		,X,Y
		, m_iFrameSIze, m_iFrameSIze
		, hMemDC
		, m_iFrameSIze *(int)FrameX, m_iFrameSIze *(int)FrameY
		, m_iFrameSIze, m_iFrameSIze
		, RGB(255, 0, 255));
}


void CStage::Player_HP(HDC _DC)
{
	switch (m_tPlayerStat.iHp)
	{
	case 1:
		UI_Render(_DC, 10 , 10, 1, 0);
		UI_Render(_DC, 60 , 10, 2, 0);
		UI_Render(_DC, 110, 10, 2, 0);
		break;
	case 2:
		UI_Render(_DC, 10 , 10,  0, 0);
		UI_Render(_DC, 60 , 10,  2, 0);
		UI_Render(_DC, 110, 10,  2, 0);
		break;
	case 3:
		UI_Render(_DC, 10 , 10, 0, 0);
		UI_Render(_DC, 60 , 10, 1, 0);
		UI_Render(_DC, 110, 10, 2, 0);
		break;
	case 4:
		UI_Render(_DC, 10 , 10, 0, 0);
		UI_Render(_DC, 60 , 10, 0, 0);
		UI_Render(_DC, 110, 10, 2, 0);
		break;
	case 5:
		UI_Render(_DC, 10 , 10, 0, 0);
		UI_Render(_DC, 60 , 10, 0, 0);
		UI_Render(_DC, 110, 10, 1, 0);
		break;
	case 6:
		UI_Render(_DC, 10, 10 , 0, 0);
		UI_Render(_DC, 60, 10 , 0, 0);
		UI_Render(_DC, 110, 10, 0, 0);
		break;
	}
}


void CStage::Palyer_Blank(HDC _DC)
{
	switch (m_tPlayerStat.iBlank)
	{
	case 0:
		break;
	case 1:
		UI_Render(_DC, 10, 60, 0, 2);
		break;
	case 2:
		UI_Render(_DC, 10, 60, 0, 2);
		UI_Render(_DC, 60, 60, 0, 2);
		break;
	case 3:
		UI_Render(_DC, 10, 60, 0, 2);
		UI_Render(_DC, 60, 60, 0, 2);
		UI_Render(_DC, 110, 60, 0, 2);
		break;
	}
}

void CStage::Load_Monster(int _iRoom, float fX, float fY, int _Monster)
{
	switch (_Monster)
	{
		case 0:
			CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CGunDead>::Create(fX, fY, OBJID::MONSTER, _iRoom), OBJID::MONSTER);
			break;
		case 1:
			CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CRedGunDead>::Create(fX, fY, OBJID::MONSTER, _iRoom), OBJID::MONSTER);
			break;
		case 2:
			CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CBlueGunDead>::Create(fX, fY, OBJID::MONSTER, _iRoom), OBJID::MONSTER);
			break;
		case 3:
			CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CMage>::Create(fX, fY, OBJID::MONSTER, _iRoom), OBJID::MONSTER);
			break;
		case 4:
			CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CKnight>::Create(fX, fY, OBJID::MONSTER, _iRoom), OBJID::MONSTER);
			break;
		case 5:
			CObjMgr::Get_Instance()->Add_Object(CAbstractFactory<CGalme>::Create(fX, fY, OBJID::MONSTER, _iRoom), OBJID::MONSTER);
			break;
	}

}

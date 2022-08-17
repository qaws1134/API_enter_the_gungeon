#pragma once
#ifndef __WEAPON_H__
#define __WEAPON_H__

//√— ¿ÃπÃ¡ˆ √‚∑¬ -> ¡÷∫Ø¿ª µ’µ’ ∂∞¥Ÿ¥‘
//≈∫æ‡ ∞¸∏Æ
//
#include "Obj.h"
class CWeapon :
	public CObj
{
public :
	enum WEAPONSTATE {ATTACK,IDLE,RELOAD, M_ATTACK,END};
public:
	CWeapon();
	virtual ~CWeapon();

	// CObj¿ª(∏¶) ≈Î«ÿ ªÛº”µ 
	virtual void Initialize() = 0;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

public:
	void Reload();
	void Use_Bullet();
	bool Weapon_Delay(); 
	void Weapon_AngleState();

	virtual void Sound_Att() = 0;
	virtual void Sound_Reload() = 0;

	virtual void State_Change() = 0;
	virtual void Update_Frame();
public :
	int Get_InitMaxBullet() { return m_iInitMaxBullet; }
	int Get_MaxBullet() { return m_iMaxBullet; }
	int Get_Reload() { return m_iReload; }	
	bool Get_AttackEnd() { return m_bAttackEnd; }
public :
	void Set_MaxBullet(int _iMaxBullet) { m_iMaxBullet += _iMaxBullet; }
	void Set_ReloadOn(bool _Reload) { m_bReloadOn = _Reload; }
	void Set_WeaponState(WEAPONSTATE _eState) { m_eCurState = (CObj::STATE)_eState; }
	void Set_AttackEnd() { m_bAttackEnd = false; }

	void Get_WeaponUI(HDC _DC);
public :
protected:

	int m_iReload;
	int m_iMaxReload;
	int m_iMaxBullet;
	int m_iInitMaxBullet;
	DWORD dwTime;
	int m_iReloadTime;
	int m_iShotDelay;
	
	bool m_bReloadStart;
	bool m_bRender;
	bool m_bAttackEnd;
	bool m_bReloadOn;



};


#endif // !__WEAPON_H__

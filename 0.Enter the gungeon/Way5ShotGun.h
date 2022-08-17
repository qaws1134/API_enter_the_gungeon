#pragma once
#ifndef __WAY5SHOTGUN_H__
#define __WAY5SHOTGUN_H__

#include "Weapon.h"
class CWay5ShotGun :
	public CWeapon
{
public:
	CWay5ShotGun();
	virtual ~CWay5ShotGun();

	// CWeapon을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update_Frame() override;

	// CWeapon을(를) 통해 상속됨
	virtual void State_Change() override;

	// CWeapon을(를) 통해 상속됨
	virtual void Sound_Att() override;
	virtual void Sound_Reload() override;
};


#endif // !__WAY5SHOTGUN_H__

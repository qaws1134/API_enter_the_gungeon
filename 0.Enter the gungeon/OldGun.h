#pragma once
#ifndef __OLDGUN_H__
#define __OLDGUN_H__

#include "Weapon.h"
class COldGun :
	public CWeapon
{
public:
	COldGun();
	virtual ~COldGun();

	virtual void Initialize() override;
	virtual void State_Change() override;
	virtual void Update_Frame()override;

	// CWeapon을(를) 통해 상속됨
	virtual void Sound_Att() override;
	virtual void Sound_Reload() override;
};


#endif // !__OLDGUN_H__

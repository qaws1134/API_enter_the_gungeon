#pragma once
#include "Weapon.h"
class CGunDeadGun :
	public CWeapon
{
public:
	CGunDeadGun();
	virtual ~CGunDeadGun();

	// CWeapon을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update_Frame() override;

	// CWeapon을(를) 통해 상속됨
	virtual void State_Change() override;

	// CWeapon을(를) 통해 상속됨
	virtual void Sound_Att() override;
	virtual void Sound_Reload() override;
};


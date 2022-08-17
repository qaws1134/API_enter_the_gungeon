#pragma once
#ifndef __CROSSBOW_H__
#define __CROSSBOW_H__


#include "Weapon.h"
class CCrossBow :
	public CWeapon
{
public:
	CCrossBow();
	virtual ~CCrossBow();

	virtual void Initialize() override;
	virtual void State_Change() override;
	virtual void Update_Frame();

private:
	bool m_bArrow;

	// CWeapon을(를) 통해 상속됨
	virtual void Sound_Att() override;
	virtual void Sound_Reload() override;
};


#endif // !__CROSSBOW_H__

#pragma once
#include "Weapon.h"
class CGunDeadGun :
	public CWeapon
{
public:
	CGunDeadGun();
	virtual ~CGunDeadGun();

	// CWeapon��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update_Frame() override;

	// CWeapon��(��) ���� ��ӵ�
	virtual void State_Change() override;

	// CWeapon��(��) ���� ��ӵ�
	virtual void Sound_Att() override;
	virtual void Sound_Reload() override;
};


#pragma once
#ifndef __REDGUNDEAD_H__
#define __REDGUNDEAD_H__

#include "Monster.h"
class CRedGunDead :
	public CMonster
{
public:
	CRedGunDead();
	virtual ~CRedGunDead();
public :
	virtual void Initialize() override;

	virtual void Release() override;
	virtual void SelectFrame() override;
	virtual void Load_Init() override;

public:
	void Attack();
	void State_Change();


	// CMonster을(를) 통해 상속됨

	// CMonster을(를) 통해 상속됨
};


#endif // !__REDGUNDEAD_H__

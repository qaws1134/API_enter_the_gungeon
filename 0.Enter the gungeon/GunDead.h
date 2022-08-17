#pragma once
#ifndef __GUNDEAD_H__
#define __GUNDEAD_H__

#include "Monster.h"
class CGunDead :
	public CMonster
{

public:
	CGunDead();
	virtual ~CGunDead();
public :
	virtual void Initialize() override;
	virtual void Release() override;
	virtual void SelectFrame();
public :
	void Attack();
	void State_Change();



	// CMonster을(를) 통해 상속됨
	virtual void Load_Init() override;

};


#endif // !__GUNDEAD_H__

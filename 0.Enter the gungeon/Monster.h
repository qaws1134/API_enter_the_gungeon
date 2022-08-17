#pragma once

#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "Obj.h"
class CWeapon;
class CMonster : public CObj
{
public :
	enum STATE { IDLE, UP, UP_LEFT, LEFT, DOWN_LEFT, DOWN, DOWN_RIGHT, RIGHT, UP_RIGHT };

public:
	CMonster();
	virtual ~CMonster();
	virtual int Update();
	virtual void Late_Update();
	virtual void Render(HDC _DC);

public :
	virtual bool Follow();
	virtual void Move();
	virtual void Update_Frame() override;
	virtual void Monster_AngleState();
	virtual void State_Change() = 0;
	virtual void Attack()= 0;
	virtual void AiState();
	virtual void Hit();
	virtual void Check_Angle();
	virtual void Load_Init() = 0;

protected:
	virtual void SelectFrame() = 0;
protected:
	DWORD dwAttTime;
	int m_iAttDelay;
	int m_iAtkDis;
	int m_iCurHp;
	DWORD dwPatternTime;
	int m_iPatternDelay;

	float m_fBulletAngle;

	DWORD m_dwStopTime;

	STATE m_eAngleState;
	bool m_bRend; 
	CWeapon* m_pWeapon;
	DWORD m_dwHitTime;
	int	m_iHitTme;
	bool m_bStartInit;
};


#endif // !__MONSTER_H__

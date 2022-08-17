#pragma once
#ifndef __BLUEGUNDEAD_H__
#define __BLUEGUNDEAD_H__

#include "Monster.h"
class CBlueGunDead :
	public CMonster
{
public:
	CBlueGunDead();
	virtual ~CBlueGunDead();
public:
	virtual void Initialize() override;

	virtual void Release() override;
	virtual void SelectFrame() override;

public:
	void Attack();
	void State_Change();
	virtual void Load_Init() override;

	// CMonster��(��) ���� ��ӵ�
private:
	int m_iAttCount;
	bool m_bAtt;

	// CMonster��(��) ���� ��ӵ�
};


#endif // !__REDGUNDEAD_H__

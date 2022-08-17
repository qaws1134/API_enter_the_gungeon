#pragma once
#ifndef __MAGE_H__
#define __MAGE_H__

#include "Monster.h"
class CMage :
	public CMonster
{
public :
	enum PATTERN {IDLE,ATT,TELEPORT,END};

public:
	CMage();
	virtual ~CMage();
public:
	virtual void Initialize() override;

	virtual void Release() override;
	virtual void SelectFrame() override;

public:
	void Attack();
	void Teleport();
	void State_Change();
	virtual void AiState();
	virtual void Update_Frame();
	virtual bool RangeCheck(int _iRange);
	virtual void Load_Init() override;

private:
	int m_iAttCount;
	int m_iTelDis;
	int m_iPatternDis;
	bool m_bAtt;
	bool Up_Teleport;
	bool m_bTeleport;
	bool m_bRangeCheck;
	bool m_bRender;
	PATTERN m_ePattern;
	PATTERN m_ePrePattern;

	// CMonster을(를) 통해 상속됨
};


#endif // !__REDGUNDEAD_H__

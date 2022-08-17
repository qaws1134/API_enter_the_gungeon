#pragma once
#ifndef __KNIGHT_H__
#define __KNIGHT_H__
#include "Monster.h"
class CKnight :
	public CMonster
{
public:
	CKnight();
	virtual ~CKnight();
public:
	virtual void Initialize() override;

	virtual void Release() override;
	virtual void SelectFrame() override;

public:
	void Attack();
	void State_Change();
	void CreateKnightBullet(float _fSpeed, OBJID::ID _eID);
	virtual void Update_Frame();
	virtual void Monster_AngleState();
	virtual void AiState();
	virtual void Load_Init() override;

private:
	DWORD m_dwKnightBullet;
	int m_iKnightBullet;
	int m_iKnightPattern;
	bool m_bKnightPattern;
	bool m_bPattern;
	bool m_bAttEnd;
	bool m_bLoop;

	int m_iFrame = 0;

	// CMonster을(를) 통해 상속됨
	// CMonster을(를) 통해 상속됨
};


#endif // !__KNIGHT_H__

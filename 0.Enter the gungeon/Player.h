#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__


#include "Obj.h"
class CWeapon;
class CPlayer :public CObj
{
public :
	enum STATE {IDLE,UP,UP_LEFT,LEFT, DOWN_LEFT,DOWN,DOWN_RIGHT,RIGHT,UP_RIGHT,END};
public:
	CPlayer();
	virtual ~CPlayer();

public :
	void Key_Check();
	void MousePos_Check();
	void Player_AngleState();
	void Jump();
	void Move();
	void Bullet_Shot();
	void State_Change();
	void Weapon_Check();
	virtual void Update_Frame();
	void Select_Weapon(int _iKeynum);
	void Keybord_OffSet();
	void Mouse_OffSet();


public :
	bool& Get_Jump() { return m_bJump; }
	CWeapon* Get_CurWeapon() { return m_CurWeapon; }
public :
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
private:
	//점프
	bool m_bJump;
	bool m_bMove;
	float m_fJumpPower;
	float m_fJumpStart;
	DWORD m_dwJumpStopTime;
	int m_iJumpEnd;

	//상태
	STATE m_eAngleState;
	STATE m_eState;

	float m_fInitSpeed;

	vector<CWeapon*> m_vecWeapon;
	CWeapon* m_CurWeapon;
};


#endif // !__PLAYER_H__

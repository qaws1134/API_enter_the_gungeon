#pragma once
#ifndef __RANDOMPOSBULLET_H__
#define __RANDOMPOSBULLET_H__

#include "Obj.h"
class CRandomPosBullet :
	public CObj
{
public :
	enum STATE{ UP,DOWN,END };
public:
	CRandomPosBullet();
	virtual ~CRandomPosBullet();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

	virtual void DrawColRect(HDC _DC);
	virtual void Update_Frame();
	void State_Change();
private:
	DWORD m_dwTime;
	int m_iBreakTime;
	float m_fInitY;
};


#endif // !__RANDOMPOSBULLET_H__

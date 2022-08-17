#pragma once
#ifndef __CHARGEEFFECT_H__
#define __CHARGEEFFECT_H__

#include "Obj.h"
class CChargeEffect :
	public CObj
{
public:
	CChargeEffect();
	virtual ~CChargeEffect();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

	virtual void Update_Frame();
	virtual void Bullet_AngleState();
};


#endif // !__CHARGEEFFECT_H__

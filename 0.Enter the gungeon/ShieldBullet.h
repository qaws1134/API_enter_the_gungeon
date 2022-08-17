#pragma once
#ifndef __SHIELD_H__
#define __SHIELD_H__

#include "Obj.h"
class CShieldBullet :
	public CObj
{
public:
	CShieldBullet();
	virtual ~CShieldBullet();




	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;

	virtual int Update() override;

	virtual void Late_Update() override;

	virtual void Render(HDC _DC) override;

	virtual void Release() override;
	virtual void DrawColRect(HDC _DC);
};


#endif // !__SHIELD_H__

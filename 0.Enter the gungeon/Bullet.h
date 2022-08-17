#pragma once
#ifndef __BULLET_H__
#define __BULLET_H__

#include "Obj.h"
class CBullet :
	public CObj
{
public:
	CBullet();
	virtual ~CBullet();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

public :
	virtual void DrawColRect(HDC _DC);

public :
	void Bullet_AngleState();
	
};


#endif // !__BULLET_H__

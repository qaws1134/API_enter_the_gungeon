#pragma once
#ifndef __BLANKBULLET_H__
#define __BLANKBULLET_H__

#include "Obj.h"
class CBlankBullet :
	public CObj
{
public:
	CBlankBullet();
	virtual ~CBlankBullet();
public:
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;
	
public :
	virtual void Update_Frame() override;

private:
	DWORD dwTime;



};
#endif // !__BLANKBULLET_H__

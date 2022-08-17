#pragma once
#ifndef __BREAKBULLET_H__
#define __BREAKBULLET_H__

#include "Obj.h"

class CBreakBullet :
	public CObj
{
public:
	CBreakBullet();
	virtual ~CBreakBullet();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

	void DrawColRect(HDC _DC);

private:
	DWORD m_dwTime;
	int m_iBreakTime;
	

	
};


#endif // !__BREAKBULLET_H__

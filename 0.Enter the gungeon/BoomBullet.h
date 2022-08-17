#pragma once
#ifndef __BOOMBULLET_H__
#define __BOOMBULLET_H__

#include "Obj.h"
class CBoomBullet :
	public CObj
{
public:
	enum STATE{BOOM,TARGET,END};
public:
	CBoomBullet();
	virtual ~CBoomBullet();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

	virtual void Update_Frame();
	void State_Change();
private:
	bool m_bSound;
};


#endif // !__BOOMBULLET_H__

#pragma once
#ifndef __MAGEBULLET_H__
#define __MAGEBULLET_H__

#include "Obj.h"
class CMageBullet :
	public CObj
{
public:
	CMageBullet();
	virtual ~CMageBullet();

public :

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

private:

	DWORD m_dwCreateTime;
	int m_iCreateDelay;

	POINT	m_tCenterPos;
	float	m_fCenterAngle;
	float	m_fCenterSpeed;

	bool	m_bStart;
	int m_iBulletCount;
};


#endif // !__MAGEBULLET_H__

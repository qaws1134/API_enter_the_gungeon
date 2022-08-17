#pragma once
#ifndef __FIELDITEM_H__
#define __FIELDITEM_H__
#include "Obj.h"
class CFieldItem :
	public CObj
{
public :
	enum STATE { GOLD ,HEALTH,H_HEALTH,ARMO,KEY};
public:
	CFieldItem();
	virtual ~CFieldItem();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

public :
	void Follow() ;
	virtual void InitState();


private:
	bool m_bFollow;
};


#endif // !__FIELDITEM_H__

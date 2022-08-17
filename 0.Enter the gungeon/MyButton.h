#pragma once

#ifndef __BUTTON_H__
#define __BUTTON_H__


#include "Obj.h"
class CMyButton : public CObj
{
public:
	CMyButton();
	virtual ~CMyButton();

public:
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

	bool m_bButtonOn;
};


#endif // !__BUTTON_H__

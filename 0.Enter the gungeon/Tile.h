#pragma once
#ifndef __TILE_H__
#define __TILE_H__

#include "Obj.h"
class CTile :public CObj
{
public:
	CTile();
	virtual ~CTile();

public:
	void Initialize();
	void Render(HDC _DC);
	void Release();
	virtual int Update() override;
	virtual void Late_Update() override;


	virtual void DrawColRect(HDC _DC);
public:
	void Set_Edit() { m_bEdit = true; }

private:
	bool m_bEdit;


};



#endif // !__TILE_H__

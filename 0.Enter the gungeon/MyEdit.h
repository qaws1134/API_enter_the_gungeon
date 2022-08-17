#pragma once
#ifndef __MYEDIT_H__
#define __MYEDIT_H__

#include "Scene.h"

class CTile;
class CMyEdit :public CScene
{
public:
	CMyEdit();
	virtual ~CMyEdit();

	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

	CObj* Create_Tile(float _x, float _y, POINT _pt);


	//방번호 // 위치값// 몬스터 번호값

private:
	vector<CObj*> m_vecTileEdit;
	list<CObj*> m_listMonster;
	float m_fMonsterX;
	float m_fMonsterY;
	int m_iMonsterNum;


	POINT m_ptDrawID;

	POINT m_tPos1;
	POINT m_tPos2;
	TCHAR Monster[30];

	int m_iRoomNum;

	int m_iTileX;
	int m_iTileY;

	int m_iScreenCX;
	int m_iScreenCY;
	bool m_bColTile;
	bool m_bScrollOn;
	bool KeyOn;

	bool m_bMonsterEdit;
		
	bool m_bMonster;
};


#endif // !__MYEDIT_H__

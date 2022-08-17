#pragma once

#ifndef __STAGE_H__
#define __STAGE_H__


#include "Scene.h"
class CWeapon;
class CStage : public CScene
{
public:
	CStage();
	virtual ~CStage();

public:
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC _DC) override;
	virtual void Release() override;

public :
	void UI_Render(HDC _DC, int X, int Y,float FrameX, float FrameY);
	void Player_HP(HDC _DC);
	void Palyer_Blank(HDC _DC);
	void Load_Monster(int _iRoom, float fX, float fY, int _Monster);
	
	//get으로 끼고있는 무기를 가저옴->
	//weapon에서 함수를하나 dc 
	//무기의 dc를 가져와서 여기다가 랜더링



private:
	TCHAR* m_pFrameKey;
	STAT m_tPlayerStat;
	POINT FrameState;
	CWeapon* m_pUIWeapon;
	int m_iFrameSIze;
	bool m_bStart;

	TCHAR m_szNowBullet[50];

	
};


#endif // !__STAGE_H__

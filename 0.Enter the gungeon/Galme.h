#pragma once
#ifndef __GALME_H__
#define __GALME_H__


#include "Monster.h"
class CGalme :
	public CMonster
{
public :
	enum STATE { ANGLE_IDLE,UP, UP_LEFT, LEFT, DOWN_LEFT, DOWN, DOWN_RIGHT, RIGHT, UP_RIGHT };
	enum GALMEA_PATTERN {JUMP_DOWN,MELEE_ATTACK,JUMP,DEAD,ROCKET,JUMP_DOWN2 =6,END};
	enum GALMEA_STATE {WALK,IDLE,HIT};
public:
	CGalme();
	virtual ~CGalme();

	// CMonster을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Release() override;
	virtual void State_Change() override;
	virtual void Attack() override;
	virtual void SelectFrame() override;

	virtual void Update_Frame() override;
	virtual void Monster_AngleState();
	virtual void AiState();

	void TargetCheck();

	void Attack(int _iPattern);
	bool RangeCheck(float _fRange);

	void Jump();
	void Rocket();
private:

	//==패턴 상태== 
	bool m_bLoop;		//반복 랜더링 체크
	bool m_bJump;		//점프중인지 체크
	bool m_bAttEnd;		//공격중인지 체크
	bool m_bEffect;		//이펙트가 나왔는지 체크
	bool m_bRangeCheck;  //범위체크가 되었는지

	
	//==이펙트==
	int m_iEffectDelay;
	DWORD m_dwEffectTime;
	

	//==프레임 키 변경 체크==
	bool m_bCurPattern;	//패턴 이전과 다른지 프레임키 체크
	bool m_bPrePattern;


	//==현재 패턴 상태==
	int m_iCurPattern;	//패턴 새부 상태
	int m_iPrePattern;
	
	int m_iAttState;	//현재 진행중인 패턴 상태
	int m_iNowState;	//종료후 패턴 상태 처리

	//==범위값 저장==
	float m_fMiddleDis;
	float m_fRangeDis;
	float m_fMeleeDis;
	float m_fPatternDis; //실행할 범위값 저장


	//==업데이트 프레임

	//===점프==
	int m_iJumpPattern;
	float m_fRandomAngle;
	float m_fRandomSpeed;
	float m_fPlayerX;
	float m_fPlayerY;

	//==로켓==
	int m_iRocketRandNum; //로켓 개수
	bool m_bRocketOn;
	int m_iRandomDisX;
	int m_iRandomDisY;
	int m_iReverse;

	STATE m_eAngleState;


	// CMonster을(를) 통해 상속됨
	virtual void Load_Init() override;

};


#endif // !__GALME_H__

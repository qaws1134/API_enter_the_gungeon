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

	// CMonster��(��) ���� ��ӵ�
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

	//==���� ����== 
	bool m_bLoop;		//�ݺ� ������ üũ
	bool m_bJump;		//���������� üũ
	bool m_bAttEnd;		//���������� üũ
	bool m_bEffect;		//����Ʈ�� ���Դ��� üũ
	bool m_bRangeCheck;  //����üũ�� �Ǿ�����

	
	//==����Ʈ==
	int m_iEffectDelay;
	DWORD m_dwEffectTime;
	

	//==������ Ű ���� üũ==
	bool m_bCurPattern;	//���� ������ �ٸ��� ������Ű üũ
	bool m_bPrePattern;


	//==���� ���� ����==
	int m_iCurPattern;	//���� ���� ����
	int m_iPrePattern;
	
	int m_iAttState;	//���� �������� ���� ����
	int m_iNowState;	//������ ���� ���� ó��

	//==������ ����==
	float m_fMiddleDis;
	float m_fRangeDis;
	float m_fMeleeDis;
	float m_fPatternDis; //������ ������ ����


	//==������Ʈ ������

	//===����==
	int m_iJumpPattern;
	float m_fRandomAngle;
	float m_fRandomSpeed;
	float m_fPlayerX;
	float m_fPlayerY;

	//==����==
	int m_iRocketRandNum; //���� ����
	bool m_bRocketOn;
	int m_iRandomDisX;
	int m_iRandomDisY;
	int m_iReverse;

	STATE m_eAngleState;


	// CMonster��(��) ���� ��ӵ�
	virtual void Load_Init() override;

};


#endif // !__GALME_H__

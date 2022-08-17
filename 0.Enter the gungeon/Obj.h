#pragma once

#ifndef __OBJ_H__
#define __OBJ_H__


class CObj
{
public :
	enum STATE { WALK,IDLE, JUMP, DEAD,HIT, DROP, END };
public:
	CObj();
	virtual ~CObj();

public:
	virtual void Initialize() = 0;
	virtual int Update() = 0;
	virtual void Late_Update() = 0;
	virtual void Render(HDC _DC) = 0;
	virtual void Release() = 0;


	//==========================Set========================================
public:
	void Set_Pos(float _x, float _y) { m_tInfo.fX = _x; m_tInfo.fY = _y; }
	void Set_Dead() { m_bDead = true; }
	void Set_Angle(float _fAngle) { m_fAngle = _fAngle; }
	void Set_Target(CObj* _pTarget) { m_pTarget = _pTarget; }
	void Set_FrameKey(const TCHAR* _pFrameKey) { m_pFrameKey = _pFrameKey; }
	void Set_Dmg(int _att) { m_tStat.iHp += _att;  m_dwSuperTime = GetTickCount();}

	void Set_Hp(int _hp) { if (m_tStat.iMaxHp > (m_tStat.iHp + _hp)){ m_tStat.iHp += _hp;} }

	void Set_Att(int _iAtt) { m_tStat.iAtt = _iAtt; }
	void Set_Speed(float _fSpeed) { m_fSpeed = _fSpeed; }
	void Set_WeaponID(WEAPONID::ID _eID) { m_eWeapon = _eID; }
	void Set_DrawID(POINT _ptDrawID) { m_ptDrawID = _ptDrawID; }
	void Set_ObjID(OBJID::ID _eID) { m_eID = _eID; }
	void Set_Summon(bool _bSummon) { m_bSummon = _bSummon; }
	void Set_RoomNum(int _iRoomNum) { m_iRoomNum = _iRoomNum; }
	void Set_ColState(bool _ColState) { m_bColRect = _ColState; }
	void Set_PosinDis(int _iPosin) { m_fPosinDis = (float)_iPosin; }
	void Set_PosX(float _x) { m_tInfo.fX += _x; m_tColInfo.fX += _x; }
	void Set_PosY(float _y) { m_tInfo.fY += _y; m_tColInfo.fY += _y; }
	void Set_CurState(STATE _eState) {m_eCurState = _eState;}
	void Set_DeadStart(bool _bDeadStart) { m_bDeadStart = _bDeadStart; }
	void Set_MonsterID(int _MonsterID) { m_iMonsterID = _MonsterID; }
	void Set_RenderID(RENDERID::ID _eRender) { m_eRenderID = _eRender; }



	bool Get_Interection() { return m_bInterection; }
	void Set_Interection(bool _bInterection) { m_bInterection = _bInterection; }

	//==========================Get========================================
public:
	const INFO&			Get_Info()		const { return m_tInfo; }
	const INFO&			Get_ColInfo()	const { return m_tColInfo; }
	const RECT&			Get_Rect()		const { return m_tRect; }
	const RECT&			Get_ColRect()	const { return m_tColRect; }
	const POINT&		Get_Posin()		const { return m_tPosin; }
	const CObj*			Get_Target()	const { return m_pTarget; }
	const int&			Get_Att()		const { return m_tStat.iAtt; }
	const int&			Get_Hp()		const { return m_tStat.iHp; }
	const float&		Get_Angle()		const { return m_fAngle; }
	const POINT&		Get_DrawID()	const { return m_ptDrawID;}
	const OBJID::ID&	Get_ObjID()		const { return m_eID; }
	const bool&			Get_Summon()	const { return m_bSummon; }
	const RENDERID::ID& Get_RenderID()	const { return m_eRenderID; }
	const WEAPONID::ID& Get_WeaponID()	const { return m_eWeapon; }
	const bool&			Get_ColState()	const { return m_bColRect;}
	const int&			Get_RoomNum()	const { return m_iRoomNum;}
	const bool&			Get_Dead()		const { return m_bDead; }
	const STAT&			Get_Stat()		const { return m_tStat; }
	const int&			Get_MonsterID() const { return m_iMonsterID; }
	list<CObj*> ColCheck(int _idx);
	void Random_Angle(int _fAdd);
	const bool&			SuperMode()		const { return m_bSuper; }
	void SuperTime() { if (m_dwSuperTime + m_iSuperTime > GetTickCount()) { m_bSuper = true; }}

	virtual void Update_Frame();
	//==========================ÃÑ¾Ë »ý¼º========================================
public :
	//Á÷¼± ÃÑ¾Ë
	template<typename T>
	CObj* CreateBullet(const TCHAR* _FrameKey,int _iRanAngle,int _iAtt,float _fSpeed)
	{
		return CAbstractFactory<T>::
			Create((float)m_tPosin.x, (float)m_tPosin.y, m_fAngle, _FrameKey,_iRanAngle,_iAtt,_fSpeed);
	}
	template<typename T>
	CObj* CreateBullet(const TCHAR* _FrameKey, int _iRanAngle, int _iAtt, float _fSpeed,int _iPosindis)
	{
		return CAbstractFactory<T>::
			Create((float)m_tPosin.x, (float)m_tPosin.y,m_fAngle+_iRanAngle, _FrameKey, _iRanAngle, _iAtt, _fSpeed, _iPosindis);
	}
	template<typename T>
	CObj* CreateBullet(float _x, float _y)
	{
		return CAbstractFactory<T>::Create(_x, _y);
	}
	template<typename T>
	CObj* CreateBullet(float _x, float _y,float _Angle)
	{
		return CAbstractFactory<T>::Create(_x, _y,_Angle);
	}
	//¼¦°ÇÃÑ¾Ë
	template<typename T>
	CObj* CreateBullet(float _Angle, const TCHAR* _FrameKey, int _iAtt, float _fSpeed)
	{
		return CAbstractFactory<T>::Create((float)m_tPosin.x, (float)m_tPosin.y, _Angle, _FrameKey,0,_iAtt,_fSpeed);
	}

	//break way ÃÑ¾Ë
	template<typename T>
	CObj* CreateBullet(float _Angle, const TCHAR* _FrameKey, int _iAtt, float _fSpeed,INFO _tInfo)
	{
		return CAbstractFactory<T>::Create(_tInfo.fX, _tInfo.fY, _Angle, _FrameKey, 0, _iAtt, _fSpeed);
	}

	template<typename T>
	void CreateXWayBullet(float _Angle,float _BulletNum,int _iAtt,float _fSpeed, const TCHAR *_FrameKey,OBJID::ID _eID)
	{
		//float fOffSet = (_Angle / (float)_BulletNum) / 2.f;
		float fMinAngle = m_fAngle - (_Angle / 2); //- fOffSet /*- 20.f - fOffSet*/;
		
		for (int i = 0; i < _BulletNum; i++)
		{
			fMinAngle += (float)((_Angle / _BulletNum));
			CObjMgr::Get_Instance()->Add_Object(CreateBullet<T>(fMinAngle, _FrameKey,_iAtt,_fSpeed), _eID);
		}
	}
	//breakbullet ÀÚ±âÀÚ½Å À§Ä¡¸¦ ³Ñ°ÜÁÜ
	template<typename T>
	void CreateXWayBullet(float _Angle, float _BulletNum, int _iAtt, float _fSpeed, const TCHAR *_FrameKey, OBJID::ID _eID, INFO _tInfo)
	{
		//float fOffSet = (_Angle / (float)_BulletNum) / 2.f;
		float fMinAngle = m_fAngle - (_Angle / 2); //- fOffSet /*- 20.f - fOffSet*/;

		for (int i = 0; i < _BulletNum; i++)
		{
			fMinAngle += (float)((_Angle / _BulletNum));
			CObjMgr::Get_Instance()->Add_Object(CreateBullet<T>(fMinAngle, _FrameKey, _iAtt, _fSpeed, _tInfo), _eID);
		}
	}

	template<typename T>
	void CreateBreakBullet(float _Angle, int _Time,DWORD _GetTic, int _iAtt, float _fSpeed, const TCHAR *_FrameKey, OBJID::ID _eID)
	{
		CObj* BreakBullet360 = CreateBullet<T>(L"M_BossBigBullet", 0, 1, 5.f);
		CObjMgr::Get_Instance()->Add_Object(CreateBullet<CBullet>(L"M_BossBigBullet", 0, 1, 5.f), OBJID::M_BULLET);


		CObjMgr::Get_Instance()->Add_Object(CreateBullet<T>(fMinAngle, _FrameKey, _iAtt, _fSpeed), _eID);	
	}

//==================================================================================

protected:
	void Update_Rect();

	virtual void Update_ColRect();
	virtual void DrawColRect(HDC _DC);
protected:
	INFO	m_tInfo;
	RECT	m_tRect;

	INFO	m_tColInfo;
	RECT	m_tColRect;

	CObj*	m_pTarget;

	int m_iMonsterID;
	//==========================ÇÁ·¹ÀÓ °ü¸®========================================
	FRAME	m_tFrame;
	const TCHAR*	m_pFrameKey;

	RENDERID::ID m_eRenderID;

	STATE		m_ePreState;
	STATE		m_eCurState;

	bool m_bRightRev;

	int		m_iDrawID;
	int m_iFrameSize;

	POINT m_tPos[3];

	POINT m_ptDrawID;

	bool m_bColRect;

	OBJID::ID m_eID;

	//==========================Æ÷½Å========================================
	POINT m_tPosin;
	POINT m_tMouse;
	float m_fPosinDis;
	
	WEAPONID::ID m_eWeapon;
	CObj* m_CurWeapon;

	//ÁÂÇ¥ 
	//==========================½ºÅÝ========================================
	
	DWORD m_dwSuperTime;
	int m_iSuperTime;
	STAT m_tStat;

	float	m_fSpeed;
	float	m_fAngle;
	float	m_fDis;
	bool	m_bDead;
	bool	m_bSuper;

	bool m_bSummon;

	int m_iRoomNum;
	bool m_bDeadStart;
	bool m_bInterection;

	//Render
	HDC hMemDC;
	HDC hPlgDC;
	HDC hResetDC;
	HDC hStretchDC;
};


#endif // !__OBJ_H__

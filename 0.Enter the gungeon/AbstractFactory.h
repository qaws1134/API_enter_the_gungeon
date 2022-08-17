#pragma once

#ifndef __ABSTRACTFACTORY_H__
#define __ABSTRACTFACTORY_H__

class CObj;
template <typename T>
class CAbstractFactory
{
public:
	static CObj* Create()
	{
		CObj* pObj = new T;
		pObj->Initialize();

		return pObj;
	}
	static CObj* Create(OBJID::ID _eID)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_ObjID(_eID);
		return pObj;
	}

	static CObj* Create(int m_iState)
	{
		CObj* pObj = new T;
		pObj->Set_CurState(m_iState);
		pObj->Initialize();
		return pObj;
	}

	static CObj* Create(WEAPONID::ID _eID,const TCHAR* _FrameKey)
	{
		CObj* pObj = new T;
		pObj->Set_WeaponID(_eID);
		pObj->Set_FrameKey(_FrameKey);
		pObj->Initialize();
		return pObj;
	}
	static CObj* Create(float _x, float _y)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_x, _y);

		return pObj;
	}
	//鸥老 积己
	static CObj* Create(float _x, float _y,bool _bSummon)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_x, _y);
		pObj->Set_Summon(_bSummon);

		return pObj;
	}
	static CObj* Create(float _x, float _y, OBJID::ID _eID)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_x, _y);
		pObj->Set_ObjID(_eID);
		return pObj;
	}
	static CObj* Create(float _x, float _y, OBJID::ID _eID,int _iRoomNum)
	{
		CObj* pObj = new T;
		pObj->Set_Pos(_x, _y);
		pObj->Set_ObjID(_eID);
		pObj->Set_RoomNum(_iRoomNum);
		pObj->Initialize();
		return pObj;
	}
	static CObj* Create(float _x, float _y, float _fAngle)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_x, _y);
		pObj->Set_Angle(_fAngle);

		return pObj;
	}
	static CObj* Create(float _x, float _y, float _fAngle,const TCHAR* _FrameKey)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(_x, _y);
		pObj->Set_Angle(_fAngle);
		pObj->Set_FrameKey(_FrameKey);
		return pObj;
	}
	//流急 醚舅
	static CObj* Create(float _x, float _y, float _fAngle
		, const TCHAR* _FrameKey,int _iRanAngle,int _iAtt,float _fSpeed)
	{
		
		CObj* pObj = new T;
		pObj->Set_FrameKey(_FrameKey);
		pObj->Initialize();
		pObj->Set_Pos(_x, _y);
		pObj->Set_Angle(_fAngle);
		pObj->Random_Angle(_iRanAngle);
		pObj->Set_Att(_iAtt);
		pObj->Set_Speed(_fSpeed);

		return pObj;
	}

	static CObj* Create(CObj* _pTarget)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Target(_pTarget);
		return pObj;
	}	
	static CObj* Create(CObj* _pTarget, const TCHAR* _FrameKey)
	{
		CObj* pObj = new T;
		pObj->Set_FrameKey(_FrameKey);
		pObj->Set_Target(_pTarget);
		pObj->Initialize();
		return pObj;
	}
};

#endif // !__ABSTRACTFACTORY_H__

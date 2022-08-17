#pragma once
#ifndef __OBJMGR_H__
#define __OBJMGR_H__

class CObjMgr
{
private:
	CObjMgr();
	~CObjMgr();


public :
	void Update();
	void Late_Update();
	void Render(HDC _DC);
	void Release();
	void Add_Object(CObj* _pObj, OBJID::ID m_eID) { m_listObj[m_eID].emplace_back(_pObj); }
	void Pop_Monster();

public :
	CObj* Get_Player() const { if(!m_listObj[OBJID::PLAYER].empty()) { return m_listObj[OBJID::PLAYER].front(); } return nullptr;}
	CObj* Get_Weapon(WEAPONID::ID _eID) const;


	//방번호 // 위치값// 몬스터 번호값


public:
	void Create_Monster(float fX, float fY, int RoomNum,int MonsterNum);
	void Save_Monster();
	void Load_Monster();
	void Delete_ObjID(OBJID::ID _eID);
	void Set_Edit() { m_bEdit = !m_bEdit; }
public:
	static CObjMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CObjMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}

private:
	static CObjMgr * m_pInstance;
	list<CObj*>		m_listObj[OBJID::END];
	list<CObj*>		m_listRender[RENDERID::END];
	bool m_bEdit;

};


#endif // !__OBJMGR_H__

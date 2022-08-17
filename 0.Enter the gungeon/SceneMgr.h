#pragma once

#ifndef __SCENEMGR_H__
#define __SCENEMGR_H__

class CScene;
class CSceneMgr
{
public:
	enum SCENEID { LOGO, MENU, STAGE, EDIT, END };

private:
	CSceneMgr();
	~CSceneMgr();

public:
	void Update();
	void Late_Update();
	void Render(HDC _DC);
	void Release();

public:
	void Scene_Change(SCENEID _eID);

	SCENEID Get_SceneID() { return m_ePreScene; }
public:
	static CSceneMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CSceneMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}

private:
	static CSceneMgr* m_pInstance;

	CScene*		m_pScene;

	SCENEID		m_ePreScene;
	SCENEID		m_eCurScene;
};


#endif // !__SCENEMGR_H__

#pragma once
#ifndef __KEYMGR_H__
#define __KEYMGR_H__

#define VK_MAX 0xFF

class CKeyMgr
{
private:
	CKeyMgr();
	~CKeyMgr();

public :
	static CKeyMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CKeyMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}

public :
	bool Key_Press(int _key);
	bool Key_Down(int _key);
	bool Key_Up(int _key);

private :
	bool m_bKeyState[VK_MAX];
	static CKeyMgr* m_pInstance;

};

#endif // !__KEYMGR_H__

#pragma once

#ifndef __SCROLLMGR_H__
#define __SCROLLMGR_H__


class CScrollMgr
{
private:
	CScrollMgr();
	~CScrollMgr();

public:
	void Set_ScrollX(float _x) { m_fScrollX += _x; }
	void Set_ScrollY(float _y) { m_fScrollY += _y; }


	void Set_EditScrollX(float _x) { m_EditScrollX += _x; }
	void Set_EditScrollY(float _y) { m_EditScrollY += _y; }
public:
	float Get_ScrollX() const { return m_fScrollX; }
	float Get_ScrollY() const { return m_fScrollY; }

	float Get_EditScrollX() const { return m_EditScrollX; }
	float Get_EditScrollY() const { return m_EditScrollY; }

public:
	void Scroll_Lock();

public:
	static CScrollMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CScrollMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
		SAFE_DELETE(m_pInstance);
	}

private:
	static CScrollMgr* m_pInstance;

	float	m_fScrollX;
	float	m_fScrollY;

	float m_EditScrollX;
	float m_EditScrollY;


};


#endif // !__SCROLLMGR_H__

#pragma once
#ifndef __MAINGAME_H__
#define __MAINGAME_H__

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render();
	void Release();

private:
	HDC m_hDC;
	DWORD m_dwFPSTime;
	int m_iFPS;

};



#endif // !__MAINGAME_H__

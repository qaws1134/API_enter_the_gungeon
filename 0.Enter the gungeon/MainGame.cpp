#include "stdafx.h"
#include "MainGame.h"
#include "ObjMgr.h"
#include "Player.h"
#include"KeyMgr.h"
#include "GunDead.h"
#include "RedGunDead.h"
#include "Weapon.h"
#include"BmpMgr.h"
#include "SceneMgr.h"
#include "ScrollMgr.h"
#include "TileMgr.h"
#include "SoundMgr.h"

CMainGame::CMainGame() :m_iFPS(0), m_dwFPSTime(GetTickCount())
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	CSoundMgr::Get_Instance()->Initialize();

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/BackBuffer.bmp", L"BackBuffer");

	CSceneMgr::Get_Instance()->Scene_Change(CSceneMgr::LOGO);
}

void CMainGame::Update()
{
	CSceneMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update()
{
	CSceneMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render()
{
	if (CSceneMgr::LOGO == CSceneMgr::Get_Instance()->Get_SceneID())
		return;

	HDC hBackBuffer = CBmpMgr::Get_Instance()->Find_Bmp(L"BackBuffer");


	BitBlt(hBackBuffer, 0, 0, WINCX, WINCY, hBackBuffer, 0, 0, SRCCOPY);


	CSceneMgr::Get_Instance()->Render(hBackBuffer);

	BitBlt(m_hDC, 0, 0, WINCX, WINCY, hBackBuffer, 0, 0, SRCCOPY);


	++m_iFPS;
	if (m_dwFPSTime + 1000 < GetTickCount())
	{
		TCHAR		szFPS[16] = L"";
		swprintf_s(szFPS, L"FPS: %d", m_iFPS);
		SetWindowText(g_hWnd, szFPS);

		m_iFPS = 0;
		m_dwFPSTime = GetTickCount();
	}
}

void CMainGame::Release()
{
	CKeyMgr::Destroy_Instance();
	CSceneMgr::Destroy_Instance();
	CScrollMgr::Destroy_Instance();
	CTileMgr::Destroy_Instance();
	CBmpMgr::Destroy_Instance();
	CSoundMgr::Destroy_Instance();
	CObjMgr::Destroy_Instance();
	ReleaseDC(g_hWnd, m_hDC);
}

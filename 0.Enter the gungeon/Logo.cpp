#include "stdafx.h"
#include "Logo.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"


CLogo::CLogo() 
{
}


CLogo::~CLogo()
{
	Release();
}

void CLogo::Initialize()
{
	m_hVideo = MCIWndCreate(g_hWnd, nullptr
		, WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR
		, L"../Video/Opening.wmv");
	MoveWindow(m_hVideo, 0, 0, WINCX, WINCY, FALSE);
	MCIWndPlay(m_hVideo);

}

void CLogo::Update()
{
}

void CLogo::Late_Update()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RETURN)
		|| (MCIWndGetLength(m_hVideo) <= MCIWndGetPosition(m_hVideo)))
	{
		CSceneMgr::Get_Instance()->Scene_Change(CSceneMgr::MENU);
		return;
	}
}

void CLogo::Render(HDC _DC)
{

}

void CLogo::Release()
{
	MCIWndClose(m_hVideo);
}

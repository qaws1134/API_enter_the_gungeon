#include "stdafx.h"
#include "MyButton.h"
#include "BmpMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "SoundMgr.h"

CMyButton::CMyButton() :m_bButtonOn(false)
{
}


CMyButton::~CMyButton()
{
	Release();
}

void CMyButton::Initialize()
{
	m_tInfo.iCX = 100;
	m_tInfo.iCY = 50;
	m_eRenderID = RENDERID::UI;
}

int CMyButton::Update()
{
	if (m_bDead)
		return OBJ_DEAD;

	Update_Rect();
	return OBJ_NOEVENT;
}

void CMyButton::Late_Update()
{
	POINT	pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (PtInRect(&m_tRect, pt))
	{
		if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
		{
			if (!lstrcmp(m_pFrameKey, L"Start"))
			{
				CSoundMgr::Get_Instance()->StopSound(CSoundMgr::MENUSELECT);
				CSoundMgr::Get_Instance()->PlaySound(L"MenuSelect.mp3", CSoundMgr::MENUSELECT);
				CSceneMgr::Get_Instance()->Scene_Change(CSceneMgr::STAGE);
				return;
			}
			if (!lstrcmp(m_pFrameKey, L"Edit"))
			{
				CSoundMgr::Get_Instance()->StopSound(CSoundMgr::MENUSELECT);
				CSoundMgr::Get_Instance()->PlaySound(L"MenuSelect.mp3", CSoundMgr::MENUSELECT);
				CSceneMgr::Get_Instance()->Scene_Change(CSceneMgr::EDIT);
				return;
			}
			if (!lstrcmp(m_pFrameKey, L"Exit"))
			{
				CSoundMgr::Get_Instance()->StopSound(CSoundMgr::MENUSELECT);
				CSoundMgr::Get_Instance()->PlaySound(L"MenuSelect.mp3", CSoundMgr::MENUSELECT);
				DestroyWindow(g_hWnd);
				return;
			}
		}
		if (!m_bButtonOn) {
			CSoundMgr::Get_Instance()->StopSound(CSoundMgr::MENUON);
			CSoundMgr::Get_Instance()->PlaySound(L"MenuOn.mp3", CSoundMgr::MENUON);
			m_bButtonOn = true;
		}
		m_iDrawID = 1;
	}
	else {
		m_bButtonOn = false;
		m_iDrawID = 0;
	}
}

void CMyButton::Render(HDC _DC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Bmp(m_pFrameKey);

	GdiTransparentBlt(_DC
		, m_tRect.left, m_tRect.top
		, m_tInfo.iCX, m_tInfo.iCY
		, hMemDC
		, m_iDrawID * 100, 0
		, 100, 50
		, RGB(255, 0, 255));
}

void CMyButton::Release()
{
}

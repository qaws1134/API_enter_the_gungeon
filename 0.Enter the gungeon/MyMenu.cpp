#include "stdafx.h"
#include "MyMenu.h"
#include "MyButton.h"
#include "BmpMgr.h"
#include "ObjMgr.h"
#include"SoundMgr.h"

CMyMenu::CMyMenu()
{
}


CMyMenu::~CMyMenu()
{
	Release();
}

void CMyMenu::Initialize()
{
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Start.bmp", L"Start");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Edit.bmp", L"Edit");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Button/Exit.bmp", L"Exit");

	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Menu.bmp", L"Menu");

	CObj* pObj = CAbstractFactory<CMyButton>::Create(130.f, 600.f);
	pObj->Set_FrameKey(L"Start");
	CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::UI);

	pObj = CAbstractFactory<CMyButton>::Create(130.f, 650.f);
	pObj->Set_FrameKey(L"Edit");
	CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::UI);

	pObj = CAbstractFactory<CMyButton>::Create(130.f, 700.f);
	pObj->Set_FrameKey(L"Exit");
	CObjMgr::Get_Instance()->Add_Object(pObj, OBJID::UI);

	CSoundMgr::Get_Instance()->PlayBGM(L"MainBgm.mp3");
	m_tFrame.iStartX = 0;
	m_tFrame.iStateY = 0;
	m_tFrame.dwDelay = 150;
	m_tFrame.iEndX = 8;
	m_tFrame.dwTime = GetTickCount();

}

void CMyMenu::Update()
{
	Update_Frame();
	CObjMgr::Get_Instance()->Update();
}

void CMyMenu::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CMyMenu::Render(HDC _DC)
{
	HDC hMemDC = CBmpMgr::Get_Instance()->Find_Bmp(L"Menu");

	GdiTransparentBlt(_DC
		, 0, 0
		, WINCX, WINCY
		, hMemDC
		, m_tFrame.iStartX * WINCX, m_tFrame.iStateY * WINCY
		, WINCX, WINCY
		, RGB(255, 0, 255));

	CObjMgr::Get_Instance()->Render(_DC);


}

void CMyMenu::Release()
{
	CSoundMgr::Get_Instance()->StopSound(CSoundMgr::BGM);
	CObjMgr::Get_Instance()->Delete_ObjID(OBJID::UI);
	
}

void CMyMenu::Update_Frame()
{
	if (m_tFrame.dwTime + m_tFrame.dwDelay < GetTickCount())
	{
		++m_tFrame.iStartX;
		if (m_tFrame.iStartX >= m_tFrame.iEndX)
			m_tFrame.iStartX = 0;
		m_tFrame.dwTime = GetTickCount();
	}
}

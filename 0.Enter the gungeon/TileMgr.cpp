#include "stdafx.h"
#include "TileMgr.h"
#include "ScrollMgr.h"
#include "Tile.h"
#include "Obj.h"

CTileMgr* CTileMgr::m_pInstance = nullptr;
CTileMgr::CTileMgr()
{
	m_vecTile.reserve(TILEX * TILEY);
}


CTileMgr::~CTileMgr()
{
	Release();
}


//전체 백터를 생성. 빈 공간은 nullptr
//nullptr이 아닐 때 출력.

void CTileMgr::Initialize()
{
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			float fX = (float)((TILECX >> 1) + j*TILECX);
			float fY = (float)((TILECY >> 1) + i*TILECY);

			m_vecTile.emplace_back(CAbstractFactory<CTile>::Create(fX, fY,false));
		}
	}
}

void CTileMgr::Render(HDC _DC)
{
	int iScrollX = (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	int iCullX = abs(iScrollX / TILECX)-5;
	int iCullY = abs(iScrollY / TILECY)-5;

	int iCullEndX = iCullX + (WINCX / TILECX) + 10;
	int iCullEndY = iCullY + (WINCY / TILECY) + 10;

	for (int i = iCullY; i < iCullEndY; ++i)
	{
		for (int j = iCullX; j < iCullEndX; ++j)
		{
			int iIdx = i * TILEX + j;

			if (0 > iIdx || m_vecTile.size() <= (size_t)iIdx)
				continue;
	
			m_vecTile[iIdx]->Render(_DC);
		}
	}
}

void CTileMgr::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), Safe_Delete<CObj*>);
	m_vecTile.clear();
}

CObj * CTileMgr::Get_Tile(int _iIdx)
{
	if (0>_iIdx  || m_vecTile.size() <= (size_t)_iIdx)
		return nullptr;

	return m_vecTile[_iIdx]; 
}

void CTileMgr::Picking_Tile(POINT _ptDrawID,bool _bColTile, int _iRoomNum)
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();
	
	int x = pt.x / TILECX;
	int y = pt.y / TILECY;


	int iIdx = y*TILEX + x;


	if (0 > iIdx || m_vecTile.size() <= (size_t)iIdx)
		return;

	m_vecTile[iIdx]->Set_Summon(true);
	m_vecTile[iIdx]->Set_RoomNum(_iRoomNum);
	m_vecTile[iIdx]->Set_DrawID(_ptDrawID);
	m_vecTile[iIdx]->Set_ColState(_bColTile);

	//CObj* pTile = CAbstractFactory<CTile>::Create(fX, fY,true);
	//m_vecTile.emplace_back(pTile);
	//m_vecTile[iIdx]->Set_DrawID(_ptDrawID);
}

void CTileMgr::Draw_Tile(POINT _ptRange,POINT _ptDrawID, bool _bColTile, int _iRoomNum)
{
	int iIdx = _ptRange.y*TILEX + _ptRange.x;

	if (0 > iIdx || m_vecTile.size() <= (size_t)iIdx)
		return;

	m_vecTile[iIdx]->Set_Summon(true);
	m_vecTile[iIdx]->Set_RoomNum(_iRoomNum);
	m_vecTile[iIdx]->Set_DrawID(_ptDrawID);
	m_vecTile[iIdx]->Set_ColState(_bColTile);
}


void CTileMgr::Delete_Tile()
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	pt.x -= (int)CScrollMgr::Get_Instance()->Get_ScrollX();
	pt.y -= (int)CScrollMgr::Get_Instance()->Get_ScrollY();

	int x = pt.x / TILECX;
	int y = pt.y / TILECY;

	float fX = (float)((TILECX >> 1) + x*TILECX);
	float fY = (float)((TILECY >> 1) + y*TILECY);

	int iIdx = y*TILEX + x;


	if (0 > iIdx || m_vecTile.size() <= (size_t)iIdx)
		return;

	m_vecTile[iIdx]->Set_Summon(false);


	//CObj* pTile = CAbstractFactory<CTile>::Create(fX, fY,true);
	//m_vecTile.emplace_back(pTile);
	//m_vecTile[iIdx]->Set_DrawID(_ptDrawID);
}

void CTileMgr::Save_Tile()
{
	HANDLE hFile = CreateFile(L"../Data/Tile.dat", GENERIC_WRITE
		,NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"저장 실패", L"실패", MB_OK);
		return;
	}

	DWORD dwByte = 0;

	for (auto& pTile : m_vecTile)
	{
		WriteFile(hFile, &pTile->Get_Info(), sizeof(INFO), &dwByte, NULL);
		WriteFile(hFile, &pTile->Get_DrawID(), sizeof(POINT), &dwByte, NULL);

		WriteFile(hFile, &pTile->Get_Summon(), sizeof(bool), &dwByte, NULL);
		WriteFile(hFile, &pTile->Get_ColState(), sizeof(bool), &dwByte, NULL);
		WriteFile(hFile, &pTile->Get_RoomNum(), sizeof(int), &dwByte, NULL);
	}
	CloseHandle(hFile);
	//MessageBox(g_hWnd, L"저장 성공", L"성공", MB_OK);
}

void CTileMgr::Load_Tile()
{
	HANDLE hFile = CreateFile(L"../Data/Tile.dat", GENERIC_READ
		, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"불러오기 실패!", L"실패", MB_OK);
		return;
	}

	Release();

	DWORD	dwByte = 0;
	INFO	tTemp = {};
	POINT	ptDrawID = {};
	bool	bSummon = false;
	bool	bColState = false;
	int		iRoomNum = 0;


	while (true)
	{
		ReadFile(hFile, &tTemp, sizeof(INFO), &dwByte, NULL);
		ReadFile(hFile, &ptDrawID, sizeof(POINT), &dwByte, NULL);
		ReadFile(hFile, &bSummon, sizeof(bool), &dwByte, NULL);
		ReadFile(hFile, &bColState, sizeof(bool), &dwByte, NULL);
		ReadFile(hFile, &iRoomNum, sizeof(int), &dwByte, NULL);
		if (0 == dwByte)
			break;

		CObj* pTile = CAbstractFactory<CTile>::Create(tTemp.fX, tTemp.fY, bSummon);
		pTile->Set_DrawID(ptDrawID);
		pTile->Set_RoomNum(iRoomNum);
		pTile->Set_ColState(bColState);

		m_vecTile.emplace_back(pTile);
	}

	CloseHandle(hFile);
	//MessageBox(g_hWnd, L"불러오기 성공!", L"성공", MB_OK);
}


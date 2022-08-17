#include "stdafx.h"
#include "ScrollMgr.h"

CScrollMgr* CScrollMgr::m_pInstance = nullptr;
CScrollMgr::CScrollMgr()
	: m_fScrollX(0.f),m_fScrollY(0.f)
	, m_EditScrollX(0.f), m_EditScrollY(0.f)
{
}


CScrollMgr::~CScrollMgr()
{
}


void CScrollMgr::Scroll_Lock()
{
	if (0 <m_fScrollX)
		m_fScrollX = 0.f;

	if (0 < m_fScrollY)
		m_fScrollY = 0.f;


	if ((WINCX - (TILEX * TILECX)) > m_fScrollX)
		m_fScrollX = (float)(WINCX - (TILEX*TILECX));


	if ((WINCY- (TILEY * TILECY)) > m_fScrollY)
		m_fScrollY = (float)(WINCY - (TILEY*TILECY));
}

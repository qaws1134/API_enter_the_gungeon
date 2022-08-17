#pragma once

#ifndef __MYBITMAP_H__
#define __MYBITMAP_H__

class CMyBitmap
{
public:
	CMyBitmap();
	~CMyBitmap();

public:
	void Load_Image(const TCHAR* _pFilePath);
	void Release();

public:
	HDC Get_DC() { return m_hMemDC; }

private:
	HDC		m_hMemDC;

	HBITMAP	m_hBitmap;
	HBITMAP m_hOldBmp;
};

#endif // !__MYBITMAP_H__

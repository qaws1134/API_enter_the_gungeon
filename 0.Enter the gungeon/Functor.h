#pragma once

#ifndef __FUNCTOR_H__
#define __FUNCTOR_H__

class CStrCmp
{
public:
	CStrCmp(const TCHAR* _pStrKey) : m_pStrKey(_pStrKey) {}

public:
	template <typename T>
	bool operator()(T& _Dst)
	{
		return !lstrcmp(_Dst.first, m_pStrKey);
	}

private:
	const TCHAR*	m_pStrKey;
};

#endif // !__FUNCTOR_H__

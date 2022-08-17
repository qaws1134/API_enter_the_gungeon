#pragma once

#ifndef __STRUCT_H__
#define __STRUCT_H__

typedef struct tagInfo
{
	float	fX;
	float	fY;
	int		iCX;
	int		iCY;
}INFO;

typedef struct tagLinePos
{
	tagLinePos() { ZeroMemory(this, sizeof(tagLinePos)); }
	tagLinePos(float _x, float _y) : fX(_x), fY(_y) {}

	float	fX;
	float	fY;
}LINEPOS;

typedef struct tagLineInfo
{
	tagLineInfo() { ZeroMemory(this, sizeof(tagLineInfo)); }
	tagLineInfo(LINEPOS& _tLeftPos, LINEPOS& _tRightPos)
		: tLeftPos(_tLeftPos), tRightPos(_tRightPos) {}


	LINEPOS		tLeftPos;
	LINEPOS		tRightPos;
}LINEINFO;

typedef struct tagFrame
{
	int		iStartX;
	int		iEndX;
	int		iStateY;
	DWORD	dwDelay;
	DWORD	dwTime;
}FRAME;



typedef struct tagStat
{
	int iHp;
	int iMaxHp;
	int iAtt;
	int iGold;
	int iKey;
	int iBlank;
}STAT;
#endif // !__STRUCT_H__

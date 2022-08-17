#include "stdafx.h"
#include "CollisionMgr.h"
#include "Obj.h"
#include "TileMgr.h"
#include "SoundMgr.h"
CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::Collision_Rect(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	RECT rc = {};
	for (auto& pDst : _Dst)
	{
		for (auto& pSrc : _Src)
		{
			if (IntersectRect(&rc, &pDst->Get_ColRect(), &pSrc->Get_ColRect()))
			{
				pDst->Set_Dead();
				pSrc->Set_Dead();
			}
		}
	}
}



void CCollisionMgr::Collision_RectEx(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	float fX = 0.f, fY = 0.f;
	for (auto& pDst : _Dst)
	{
		for (auto& pSrc : _Src)
		{
			if (pDst == pSrc)
				continue;
			if (Check_Rect(pDst, pSrc, &fX, &fY))
			{
				if (fX < fY)
				{
					if (pDst->Get_ColInfo().fX < pSrc->Get_ColInfo().fX)
					{
						pDst->Set_PosX(-fX);
						pSrc->Set_PosX(fX);
					}
					else
					{
						pDst->Set_PosX(fX);
						pSrc->Set_PosX(-fX);
					}
				}
				else
				{
					if (pDst->Get_ColInfo().fY < pSrc->Get_ColInfo().fY)
					{
						pDst->Set_PosY(-fY);
						pSrc->Set_PosY(fY);
					}
					else
					{
						pDst->Set_PosY(fY);
						pSrc->Set_PosY(-fY);
					}
				}
			}
		}
	}
}

//작성할것

//입구타일에 방 넘버를주며 깔음




//생성할 때 몬스터에게 방 넘버를 줌


//문 닫음. 문도 해당 방 넘버를 주고 방에 해당하는 문 닫음
//문은 플레이어를 밀어내는 타일  door 타일생성?

//벽 체크는 방 넘버가 0일때 벽이다
//방 넘버가 0이 아닌경우는 밀어내기 


//총 14개


void CCollisionMgr::Collision_Monster_Tile(list<CObj*>& _rMonster)
{
	float fX = 0.f, fY = 0.f;
	//RECT rc = {};
	for (auto& pMonster : _rMonster)
	{
		INFO colInfo = pMonster->Get_ColInfo();

		int x = (int)pMonster->Get_Info().fX / TILECX;
		int y = (int)pMonster->Get_Info().fY / TILECY;
		int iIdx = y * TILEX + x;		//현재 인덱스가 충돌체면

		//pPlayer 위치 인덱스 구해서 주변 타일을 넘겨줌
		list<CObj*> _rTile = pMonster->ColCheck(iIdx);
		for (auto& pTile : _rTile)
		{
			if (pTile)
			{
				if (!pMonster->SuperMode())
				{
					if (Check_Rect(pMonster, pTile, &fX, &fY))
					{
						if (fX < fY)
						{
							if (pMonster->Get_ColInfo().fX > pTile->Get_ColInfo().fX)
								pMonster->Set_PosX(fX);
							else
								pMonster->Set_PosX(-fX);
						}
						else
						{
							if (pMonster->Get_ColInfo().fY > pTile->Get_ColInfo().fY)
								pMonster->Set_PosY(fY);
							else
								pMonster->Set_PosY(-fY);
						}
					}
				}
			}
		}
	}
}

//플레이어랑 타일 충돌 검사
void CCollisionMgr::Collision_Player_Tile(list<CObj*>& _rPlayer, list<CObj*>& _rMonster)
{
	float fX = 0.f, fY = 0.f;
	//RECT rc = {};
	for (auto& pPlayer : _rPlayer)
	{
		if(pPlayer)
		{
			INFO colInfo = pPlayer->Get_ColInfo();

			int x = (int)pPlayer->Get_Info().fX / TILECX;
			int y = (int)pPlayer->Get_Info().fY / TILECY;

			int iIdx = y * TILEX + x;		//현재 인덱스가 충돌체면

			//pPlayer 위치 인덱스 구해서 주변 타일을 넘겨줌
			list<CObj*> _rTile = pPlayer->ColCheck(iIdx);
			for (auto& pTile : _rTile)
			{
				if (pTile)
				{
					if (Check_Rect(pPlayer, pTile, &fX, &fY))
					{
						int iRoomNum = pTile->Get_RoomNum();

						//충돌시 타일에 방넘버가 있으면  -> 0이 아니면
						if (0 != iRoomNum)
						{
							//방넘버를 대상으로 몬스터 리스트를 돌며 해당 넘버에 해당하는 몬스터 생성
							for (auto& pMonster : _rMonster)
							{
								//방넘버를 대상으로 몬스터 리스트를 돌며 해당 넘버에 해당하는 몬스터 생성
								if (iRoomNum == pMonster->Get_RoomNum())
								{
									pMonster->Set_Summon(true);
								}
							}
						}
						else
						{
							//충돌타일에 방넘버가 0이면 벽 충돌 밀어내기
							if (fX < fY)
							{
								if (pPlayer->Get_ColInfo().fX > pTile->Get_ColInfo().fX)
									pPlayer->Set_PosX(fX);
								else
									pPlayer->Set_PosX(-fX);
							}
							else
							{
								if (pPlayer->Get_ColInfo().fY > pTile->Get_ColInfo().fY)
									pPlayer->Set_PosY(fY);
								else
									pPlayer->Set_PosY(-fY);
							}
						}
					}

				}
			}
		}
	}

}


void CCollisionMgr::Collision_BlankShot(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	for (auto& pDst : _Dst)
	{
		for (auto& pSrc : _Src)
		{
			if (Check_Sphere(pDst, pSrc))
			{
				pSrc->Set_Dead();
			}
		}
	}
}

void CCollisionMgr::Collision_Tile_Bullet(list<CObj*>& _Bullet)
{
	RECT rc = {};
	for (auto& pBullet : _Bullet)
	{
		INFO colInfo = pBullet->Get_ColInfo();
		int iTileX = (int)pBullet->Get_Info().fX / TILECX;
		int iTileY = (int)pBullet->Get_Info().fY / TILECY;
		//타일의 인덱스 계산
		int iIdx = iTileY * TILEX + iTileX;
		//충돌 체크가 되어 있는 타일을 검사해 리스트에 저장
		list<CObj*> _rTile = pBullet->ColCheck(iIdx);
		for (auto& pTile : _rTile)
		{
			if (pTile)
			{
				if (IntersectRect(&rc, &pBullet->Get_ColRect(), &pTile->Get_ColRect()))
				{
					pBullet->Set_Dead();		
				}
			}
		}
	}
}

void CCollisionMgr::Collision_Obj_Bullet(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	for (auto& pDst : _Dst)
	{
		for (auto& pSrc : _Src)
		{
			if (Check_Sphere(pDst, pSrc))
			{
				if (!pDst->SuperMode())
				{
					pDst->Set_Dmg(-pSrc->Get_Att());
					if (0 >= pDst->Get_Hp())
						pDst->Set_DeadStart(true);
					pSrc->Set_Dead();
				}
			}
		}
	}
}

void CCollisionMgr::Collision_Obj_EffetBullet(list<CObj*>& _Dst, list<CObj*>& _Src)
{
	for (auto& pDst : _Dst)
	{
		for (auto& pSrc : _Src)
		{
			if (Check_Sphere(pDst, pSrc))
			{
				if (!pSrc->SuperMode())
				{
					pSrc->Set_Dmg(-pDst->Get_Att());
					if (0 >= pSrc->Get_Hp())
						pSrc->Set_Dead();
				}
			}
		}
	}
}

bool CCollisionMgr::Check_Sphere(CObj* _Dst, CObj * _Src)
{
	float fX = abs(_Dst->Get_ColInfo().fX - _Src->Get_ColInfo().fX);
	float fY = abs(_Dst->Get_ColInfo().fY - _Src->Get_ColInfo().fY);
	float fDia = sqrtf(fX * fX + fY * fY);

	float fDis = (float)((_Dst->Get_ColInfo().iCX + _Src->Get_ColInfo().iCX) >> 1);

	if (fDia <= fDis)
		return true;

	return false;

}

bool CCollisionMgr::Check_Rect(CObj* _Dst, CObj* _Src, float* _x, float* _y)
{

	float fX = abs(_Dst->Get_ColInfo().fX - _Src->Get_ColInfo().fX);
	float fY = abs(_Dst->Get_ColInfo().fY - _Src->Get_ColInfo().fY);

	float fDisX = (float)((_Dst->Get_ColInfo().iCX + _Src->Get_ColInfo().iCX) >> 1);
	float fDisY = (float)((_Dst->Get_ColInfo().iCY + _Src->Get_ColInfo().iCY) >> 1);

	if (fX < fDisX && fY < fDisY)
	{
		*_x = fDisX - fX;
		*_y = fDisY - fY;
		return true;
	}
	return false;
}

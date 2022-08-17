#pragma once
#ifndef __COLLOSIONMGR_H__
#define __COLLOSIONMGR_H__

class CObj;
class CCollisionMgr
{
public :
	CCollisionMgr();
	~CCollisionMgr();

public :
	static void Collision_Rect(list<CObj*>& _Dst, list<CObj*>& _Src);

	static void Collision_RectEx(list<CObj*>& _Dst, list<CObj*>& _Src);

	static void Collision_Obj_EffetBullet(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_BlankShot(list<CObj*>& _Dst, list<CObj*>& _Src);
	static void Collision_Obj_Bullet(list<CObj*>& _Dst, list<CObj*>& _Src);


	static void Collision_Monster_Tile(list<CObj*>& _rMonster);
	static void Collision_Player_Tile(list<CObj*>& _rPlayer, list<CObj*>& _rMonster);
	static void Collision_Tile_Bullet(list<CObj*>& _Bullet);
	
	
	
	static bool Check_Sphere(CObj* _Dst, CObj* _Src);
	static bool Check_Rect(CObj* _Dst, CObj* _Src, float* _x, float* _y);


};


#endif // !__COLLOSIONMGR_H__

#pragma once
#ifndef __TILEMGR_H__
#define __TILEMGR_H__

class CObj;
class CTileMgr
{
private:
	CTileMgr();
	~CTileMgr();

public:
	void Initialize();
	void Render(HDC _DC);
	void Release();

public :
	CObj* Get_Tile(int _iIdx);

public:
	void Picking_Tile(POINT _ptDrawID, bool _bColTile,int _iRoomNum);
	void Draw_Tile(POINT _ptRange,POINT _ptDrawID, bool _bColTile, int _iRoomNum);
	void Delete_Tile();
	void Save_Tile();
	void Load_Tile();

	//CObj* Create_Tile(float _x,float _y);
public :
	static CTileMgr* Get_Instance()
	{
		if (!m_pInstance)
			m_pInstance = new CTileMgr;
		return m_pInstance;
	}
	static void Destroy_Instance()
	{
	
		SAFE_DELETE(m_pInstance);
	}

private:
	static CTileMgr* m_pInstance;
	vector<CObj*>		m_vecTile;
};


#endif // !__TILEMGR_H__

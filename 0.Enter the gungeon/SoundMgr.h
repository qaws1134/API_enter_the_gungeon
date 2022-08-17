#pragma once
class CSoundMgr
{
public:
	static CSoundMgr* Get_Instance()
	{
		if (nullptr == m_pInstance)
			m_pInstance = new CSoundMgr; 

		return m_pInstance; 
	}
	static void Destroy_Instance()
	{
		if (m_pInstance)
		{
			delete m_pInstance; 
			m_pInstance = nullptr; 
		}
	}
public:
	enum CHANNELID
	{
		BGM,
		PLAYER,
		PLAYER_WALK,
		PLAYER_JUMP,
		PLAYER_BLANK,


		OLDGUN_ATT,
		OLDGUN_RELOAD,
	
		CROSSBOW_ATT,
		CROSSBOW_RELOAD,

		SHOTGUN_ATT,
		SHOTGUN_RELOAD,

		GUNDEADGUN_ATT,
		BULLET_TILE_REMOVE,
		BOOM_BULLET,


		GALMEA_CHARGE, 
		GALMEA_SHOTGUN, 
		GALMEA_GLOOP, 
		GALMEA_BULLET, 
		GALMEA_MELEE,
		GALMEA_ROCKET,
		GALMEA_GLODING,
		GALMEA_JUMP,

		KNIGHT_ATT,
		KNIGHT_WALK,

		MAGE_ATT,
		MAGE_DEAD,
		MAGE_TELEPORT,

		BLUEGUNDEAD_DEAD,
		REDGUNDEAD_DEAD,
		MONSTER, 
		MONSTER_WALK,
		MONSTER_ATT,
		EFFECT,

		MENUON,
		MENUSELECT, 
		UI, 
		
		MAXCHANNEL
	};
private:
	CSoundMgr();
	~CSoundMgr();

public:
	void Initialize(); 

	void Release(); 
public:
	void PlaySound(TCHAR* pSoundKey, CHANNELID eID);
	void PlayBGM(TCHAR* pSoundKey);
	void StopSound(CHANNELID eID);
	void StopAll();

private:
	void LoadSoundFile(); 

private:
	static CSoundMgr* m_pInstance; 
	// 사운드 리소스 정보를 갖는 객체 
	map<TCHAR*, FMOD_SOUND*> m_mapSound; 
	// FMOD_CHANNEL : 재생하고 있는 사운드를 관리할 객체 
	FMOD_CHANNEL* m_pChannelArr[MAXCHANNEL]; 
	// 사운드 ,채널 객체 및 장치를 관리하는 객체 
	FMOD_SYSTEM* m_pSystem; 

};


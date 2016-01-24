#pragma once

#include "Sprite.h"
#include <vector>
<<<<<<< HEAD

class CGameMap
{
public:
	CGameMap();
	~CGameMap();

	HRESULT init();
	void release();

	void setSpriteBatch(CKT::CSpriteBatch* batch) { m_pSpriteBatch = batch; }
	
	HRESULT draw();
	HRESULT move(float fTime);

	void addElement(CKT::CSprite* elem);

private:
	CKT::CSpriteBatch* m_pSpriteBatch = NULL;
	std::vector<CKT::CSprite> m_iElementList;

	int m_iMaxTilesX = 0, m_iMaxTilesY = 0;
	int m_iCurTileX = 0, m_iCurTileY = 0;

};

=======
#include "Version.h"
#include "MapTile.h"
#include "TerrainData.h"
#include "RessourceData.h"
#include "Terrain.h"
#include "Keyboard.h"
#include "Mouse.h"

namespace CKT
{
	class CGameMap
	{
	public:
		CGameMap();
		~CGameMap();

		CKT_RESULT init(STRING mapInfFile);
		void release();

		void setSpriteBatch(CKT::CSpriteBatch* batch) { m_pSpriteBatch = batch; }

		CKT_RESULT createMap();

		CKT_RESULT move(float fTime);
		CKT_RESULT draw();

		void addElement(CKT::CSprite* elem);

		void setController(CKeyboard* keyboard, CMouse* mouse);

		float& offsetX() { return m_fOffX; }
		float& offsetY() { return m_fOffY; }
		float& Scale() { return m_fScale; }

	public:
		struct SMapHeader
		{
			CHAR Identifier[4];	// should be "TMAP"
			BYTE VersionGameMajor;
			BYTE VersionGameMinor;
			BYTE VersionMapMajor;
			BYTE VersionMapMinor;
			WORD Width;
			WORD Height;
			DWORD Reserved;
		};

	private:
		static const CHAR IDENTIFIER[4];

		CVersion m_GameVersion;
		CVersion m_MapVersion;

		bool m_bUseKeyboard = false;
		CKeyboard* m_pKeyboard = NULL;
		bool m_bUseMouse = false;
		CMouse* m_pMouse = NULL;

		CKT::CSpriteBatch* m_pSpriteBatch = NULL;
		std::vector<CKT::CSprite> m_iElementList;

		TEX_ID m_CursorTextureID = 0;

		int m_iMaxTilesX = 0, m_iMaxTilesY = 0;
		int m_iCurTileX = 0, m_iCurTileY = 0;
		float m_fOffX = 0.0f, m_fOffY = 0.0f, m_fScale = 1.0f;

		std::vector<CTerrainData> m_TerrainData;
		std::vector<CRessourceData> m_RessourceData;
		std::vector<STRING> m_RegionNames;
		std::vector<STRING> m_WarzoneNames;

		std::vector<CTerrain*> m_TerrainMap;

		int m_iTileCount = 0;
		CMapTile* m_pMapData = NULL;
		
		CKT_RESULT loadTerrain(CFileReader& reader);
		CKT_RESULT loadRessource(CFileReader& reader);
		CKT_RESULT loadRegionNames(CFileReader& reader);
		CKT_RESULT loadWarzoneNames(CFileReader& reader);
		CKT_RESULT loadHeader(CFileReader& reader);
		CKT_RESULT loadMapData(CFileReader& reader);

		static void SelectionChanged(CTerrain& curTerrain);
	};
}
>>>>>>> origin/master

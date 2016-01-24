#include "GameMap.h"

<<<<<<< HEAD
=======
#include "FileReader.h"
#include "IndexFileReader.h"
#include "FileHeaderReader.h"

#include "DXFont.h"

#include <fstream>

using namespace CKT;

const CHAR CGameMap::IDENTIFIER[4] = { 'T','M','A','P' };
>>>>>>> origin/master

CGameMap::CGameMap()
{
}


CGameMap::~CGameMap()
{
}
<<<<<<< HEAD
=======

CKT_RESULT CKT::CGameMap::init(STRING mapInfFile)
{
	CKT_RESULT hr = CR_OK;

	CFileReader infReader;
	if ((hr = infReader.init(mapInfFile.c_str())) != CR_OK ||
		(hr = infReader.read()) != CR_OK)
		return hr;

	// load Terrain data
	if ((hr = loadTerrain(infReader)) != CR_OK)
		return hr;

	// load Ressource data
	if ((hr = loadRessource(infReader)) != CR_OK)
		return hr;

	// load Region names
	if ((hr = loadRegionNames(infReader)) != CR_OK)
		return hr;

	// load Warzone names
	if ((hr = loadWarzoneNames(infReader)) != CR_OK)
		return hr;

	// load Map data
	if ((hr = loadHeader(infReader)) != CR_OK)
		return hr;

	if ((hr = loadMapData(infReader)) != CR_OK)
		return hr;

	m_CursorTextureID = CTextureManager::instance()->load(infReader.getEntryAsString(L"CURSOR", L"FILE").c_str());
	if (m_CursorTextureID <= TR_OK)
	{
		return CR_FILENOTFOUND;
	}

	return CR_OK;
}

void CKT::CGameMap::release()
{
	if (m_pMapData)
	{
		delete[] m_pMapData;
		m_pMapData = NULL;
	}

	for each (CTerrain* t in m_TerrainMap)
	{
		CKT_RELEASE(t);
	}
	
	m_TerrainMap.clear();
}

CKT_RESULT CKT::CGameMap::move(float fTime)
{
	if (m_bUseKeyboard && !m_pKeyboard)
		return CR_USERINPUTKEY;

	if (m_bUseMouse && !m_pMouse)
		return CR_USERINPUTMOUSE;

	if (!m_bUseKeyboard && !m_bUseMouse)
		return CR_OK;

	static int iClickX = 0, iClickY = 0;

	if (m_pKeyboard->KeyPress(DIK_RIGHT))
		m_fOffX -= 100 * fTime;
	if (m_pKeyboard->KeyPress(DIK_LEFT))
		m_fOffX += 100 * fTime;
	if (m_pKeyboard->KeyPress(DIK_DOWN))
		m_fOffY -= 100 * fTime;
	if (m_pKeyboard->KeyPress(DIK_UP))
		m_fOffY += 100 * fTime;
	
	m_fOffX += m_pMouse->atEdge(ED_LEFT) * fTime;
	m_fOffX += m_pMouse->atEdge(ED_RIGHT) * fTime;
	m_fOffY += m_pMouse->atEdge(ED_TOP) * fTime;
	m_fOffY += m_pMouse->atEdge(ED_BOTTOM) * fTime;
	
	if (m_pMouse->WheelForward() > 0)
	{
		m_fScale += 0.5f;
	}

	if (m_pMouse->WheelBackward() > 0)
	{
		m_fScale -= 0.5f;
	}

	bool bClick = false;
	if (m_pMouse->KeyDown(CKT::MouseKeys::MB_Left))
	{
		iClickX = m_pMouse->X();
		iClickY = m_pMouse->Y();
		bClick = true;
	}

	for each (CTerrain* t in m_TerrainMap)
	{
		t->move(m_fOffX, m_fOffY, iClickX, iClickY, bClick, m_fScale);
	}

	return CR_OK;
}

CKT_RESULT CKT::CGameMap::draw()
{
	for each (CTerrain* t in m_TerrainMap)
	{
		t->draw();
	}

	return CR_OK;
}

void CKT::CGameMap::addElement(CKT::CSprite * elem)
{
}

void CKT::CGameMap::setController(CKeyboard * keyboard, CMouse * mouse)
{
	if (keyboard)
	{
		m_pKeyboard = keyboard;
		m_bUseKeyboard = true;
	}

	if (mouse)
	{
		m_pMouse = mouse;
		m_bUseMouse = true;
	}
}

CKT_RESULT CKT::CGameMap::loadTerrain(CFileReader & reader)
{
	CKT_RESULT hr;
	CFileReader dataReader = CFileReader();
	if ((hr = dataReader.init(reader.getEntryAsString(L"TERRAIN", L"FILE").c_str())) != CR_OK ||
		(hr = dataReader.read()) != CR_OK)
		return hr;

	int iDataCount = dataReader.getEntryList()[L"GRAPHIC"].size();
	if (dataReader.getEntryList()[L"NAME"].size() != iDataCount ||
		dataReader.getEntryList()[L"FLAG"].size() != iDataCount)
		return CR_FILEFORMAT;

	for (int i = 0; i < iDataCount; i++)
	{
		CTerrainData data;
		if ((hr = data.init(
			dataReader.getEntryAsString(toString(i), L"GRAPHIC"),
			dataReader.getEntryAsString(toString(i), L"NAME"),
			dataReader.getEntryAsInt(toString(i), L"FLAG"))) != CR_OK)
			return hr;

		m_TerrainData.push_back(data);
	}

	return CR_OK;
}

CKT_RESULT CKT::CGameMap::loadRessource(CFileReader & reader)
{
	CKT_RESULT hr;
	CFileReader dataReader = CFileReader();
	if ((hr = dataReader.init(reader.getEntryAsString(L"RESSOURCE", L"FILE").c_str())) != S_OK ||
		(hr = dataReader.read()) != CR_OK)
		return hr;

	int iDataCount = dataReader.getEntryList()[L"GRAPHIC"].size();
	if (dataReader.getEntryList()[L"NAME"].size() != iDataCount)
		return CR_FILEFORMAT;

	for (int i = 0; i < iDataCount; i++)
	{
		CRessourceData data;
		if ((hr = data.init(
			dataReader.getEntryAsString(toString(i), L"GRAPHIC"),
			dataReader.getEntryAsString(toString(i), L"NAME"))) != CR_OK)
			return hr;

		m_RessourceData.push_back(data);
	}

	return CR_OK;
}

CKT_RESULT CKT::CGameMap::loadRegionNames(CFileReader & reader)
{
	CKT_RESULT hr = CR_OK;
	CIndexFileReader nameReader = CIndexFileReader();
	if ((hr = nameReader.init(reader.getEntryAsString(L"REGION", L"FILE").c_str())) != CR_OK ||
		(hr = nameReader.read()))
		return hr;

	m_RegionNames = nameReader.getData();

	return CR_OK;
}

CKT_RESULT CKT::CGameMap::loadWarzoneNames(CFileReader & reader)
{
	CKT_RESULT hr = CR_OK;
	CIndexFileReader nameReader = CIndexFileReader();
	if ((hr = nameReader.init(reader.getEntryAsString(L"WARZONE", L"FILE").c_str())) != S_OK ||
		(hr = nameReader.read()))
		return hr;

	m_WarzoneNames = nameReader.getData();

	return CR_OK;
}

CKT_RESULT CKT::CGameMap::loadHeader(CFileReader& reader)
{
	CKT_RESULT hr = CR_OK;

	SMapHeader Header = { 0 };
	if ((hr = CFileHeaderReader::read(reader.getEntryAsString(L"MAP", L"FILE"), Header)) != CR_OK)
		return hr;

	if (Header.Identifier[0] != IDENTIFIER[0] ||
		Header.Identifier[1] != IDENTIFIER[1] ||
		Header.Identifier[2] != IDENTIFIER[2] ||
		Header.Identifier[3] != IDENTIFIER[3])
		return CR_FILEFORMAT;

	m_GameVersion = CVersion(Header.VersionGameMajor, Header.VersionGameMinor);
	m_MapVersion = CVersion(Header.VersionMapMajor, Header.VersionMapMinor);
	m_iMaxTilesX = Header.Width;
	m_iMaxTilesY = Header.Height;

	return hr;
}

CKT_RESULT CKT::CGameMap::loadMapData(CFileReader& reader)
{
	int sizeTile = sizeof(CMapTile::STile);
	m_iTileCount = m_iMaxTilesX * m_iMaxTilesY;
	int iCountTilesByte = m_iTileCount * sizeTile;

	std::fstream File = std::fstream();
	File.open(reader.getEntryAsString(L"MAP", L"FILE"));
	if (!File.is_open())
		return CR_FILENOTFOUND;

	File.seekg(sizeof(SMapHeader));
	if (File.eof())
		return CR_FILEFORMAT;

	m_pMapData = new CMapTile[m_iTileCount];

	std::streamsize sumRead = 0;
	for (int i = 0; i < m_iTileCount; i++)
	{
		CMapTile::STile TileData = { 0 };
		File.read((char*)&TileData, sizeTile);

		std::streamsize read = File.gcount();
		sumRead += read;

		if (read != sizeTile)
			return CR_FILEFORMAT;

		m_pMapData[i] = CMapTile(TileData);
	}

	if (sumRead != iCountTilesByte)
		return CR_FILEFORMAT;

	return CR_OK;
}

void CKT::CGameMap::SelectionChanged(CTerrain & curTerrain)
{
	OutputDebugString(L"Callback is called\n");
	STRING msg = L"TERRAIN: " + curTerrain.getTerrainName() +
		L"\nREGION : " + curTerrain.getRegionName() +
		L"\nWARZONE: " + curTerrain.getWarzoneName() +
		L"\nHAS RES: " + toString(curTerrain.hasResource()) + 
		L"\nRES    : " + curTerrain.getRessourceName() + L"\n";
	OutputDebugString(msg.c_str());
}

CKT_RESULT CKT::CGameMap::createMap()
{
	for (int y = 0; y < m_iMaxTilesY; y++)
	{
		for (int x = 0; x < m_iMaxTilesX; x++)
		{
			CMapTile tileData = m_pMapData[x + y * m_iMaxTilesX];

			CTerrain* t = new CTerrain();
			t->init(CBounds(x, y, 0, 0),
				m_TerrainData[tileData.Terrain()],
				m_RegionNames[tileData.RegionNameIndex()],
				m_WarzoneNames[tileData.WarzoneNameIndex()]);

			if (tileData.Ressource() != CMapTile::ERessource::NO_RESSOURCE)
			{
				t->initRessource(m_RessourceData[tileData.Ressource()], tileData.RessourceLevel());
			}

			t->setSpriteBatch(m_pSpriteBatch);
			t->setCursor(m_CursorTextureID, m_pSpriteBatch);
			t->setCallback(&SelectionChanged);
			m_TerrainMap.push_back(t);
		}
	}

	return CR_OK;
}
>>>>>>> origin/master

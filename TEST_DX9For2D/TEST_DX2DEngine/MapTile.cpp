#include "MapTile.h"

using namespace CKT;

CMapTile::CMapTile()
{
}


CKT::CMapTile::CMapTile(STile tileData)
{
	m_TileData = tileData;
	m_bIsPassable = !((m_TileData.Flags & EFlag::NO_PASSING) == 1);
	m_bIsSeaUnitPassable = ((m_TileData.Flags & EFlag::SEA_UNIT_PASS) == 1);
	m_bIsMoveCost50 = ((m_TileData.Flags & EFlag::MOVE_COST_50) == 1);
	m_bIsMoveCost100 = ((m_TileData.Flags & EFlag::MOVE_COST_100) == 1);
	m_bIsMoveCost200 = ((m_TileData.Flags & EFlag::MOVE_COST_200) == 1);
	m_bIsResScouted = ((m_TileData.Flags & EFlag::RES_SCOUTED) == 1);
	m_bIsConquerd = ((m_TileData.Flags & EFlag::CONQUERED) == 1);
}

CMapTile::~CMapTile()
{
}

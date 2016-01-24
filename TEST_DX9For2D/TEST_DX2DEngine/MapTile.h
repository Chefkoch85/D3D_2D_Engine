#pragma once

#include "Engine.h"

namespace CKT
{
	class CMapTile
	{
	public:
		struct STile
		{
			BYTE TerrainType;
			BYTE InitialFaction;
			BYTE CurrentFaction;
			BYTE ConquerFaction;
			BYTE RegionNameIndex;
			BYTE WarzoneNameIndex;
			WORD Flags;
			BYTE RessourceType;
			BYTE RessourceLevel;
			BYTE ModificationTyp;
			BYTE Reserved1;
			DWORD Reserved2;
		};

		enum ETerrain
		{
			NO_TERRAIN,
			GRASS1 = 1,
			GRASS2,
			FOREST,
			SEA,
			SAND,
			MOUNTAIN,
			HILL,
			SWAMP,
		};

		enum ERessource
		{
			NO_RESSOURCE,
			BARLEY = 1,
			CROP,
			WOOD,
			SHEEP,
			COW,
			OIL,
			TIN,
			COPPER,
			COAL,
			IRON,
			GOLD,
			GEM,
			APPLE,
		};

		enum EFlag
		{
			NONE			= 0x0000,
			NO_PASSING		= 0x0001,
			SEA_UNIT_PASS	= 0x0002,
			MOVE_COST_50	= 0x0004,
			MOVE_COST_100	= 0x0008,
			MOVE_COST_200	= 0x0010,
			NOT_USED_06		= 0x0020,
			NOT_USED_07		= 0x0040,
			NOT_USED_08		= 0x0080,
			NOT_USED_09		= 0x0100,
			NOT_USED_10		= 0x0200,
			NOT_USED_11		= 0x0400,
			NOT_USED_12		= 0x0800,
			NOT_USED_13		= 0x1000,
			NOT_USED_14		= 0x2000,
			RES_SCOUTED		= 0x4000,
			CONQUERED		= 0x8000,
		};

		enum EModification
		{
			NO_MODIFICATION	= 0x00,
			ROAD			= 0x01,
			RAIL			= 0x02,
			TRENCH			= 0x04,
			FORT			= 0x08,
		};

	private:
		STile m_TileData;

		bool m_bIsPassable = false;
		bool m_bIsSeaUnitPassable = false;
		bool m_bIsMoveCost50 = false;
		bool m_bIsMoveCost100 = false;
		bool m_bIsMoveCost200 = false;
		bool m_bIsResScouted = false;
		bool m_bIsConquerd = false;

	public:
		CMapTile();
		CMapTile(STile tileData);
		~CMapTile();

		ETerrain Terrain() { return (ETerrain)m_TileData.TerrainType; }
		ERessource Ressource() { return (ERessource)m_TileData.RessourceType; }
		BYTE InitialFaction() { return m_TileData.InitialFaction; }
		BYTE RegionNameIndex() { return m_TileData.RegionNameIndex; }
		BYTE WarzoneNameIndex() { return m_TileData.WarzoneNameIndex; }

		BYTE& Modification() { return m_TileData.ModificationTyp; }
		BYTE& CurrentFaction() { return m_TileData.CurrentFaction; }
		BYTE& ConquerFaction() { return m_TileData.ConquerFaction; }
		BYTE& RessourceLevel() { return m_TileData.RessourceLevel; }

		bool isPassable() { return m_bIsPassable; }
		bool isSeaUnitPassable() { return m_bIsSeaUnitPassable; }
		bool& isMoveCost50() { return m_bIsMoveCost50; }
		bool& isMoveCost100() { return m_bIsMoveCost100; }
		bool& isMoveCost200() { return m_bIsMoveCost200; }
		bool& isResScouted() { return m_bIsResScouted; }
		bool& isConquerd() { return m_bIsConquerd; }

	};
}

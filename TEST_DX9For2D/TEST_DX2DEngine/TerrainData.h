#pragma once

#include "Engine.h"
#include "TextureManager.h"

namespace CKT
{
	class CTerrainData
	{
	public:
		CTerrainData();
		~CTerrainData();

		CKT_RESULT init(const STRING& texture, const STRING& terrainName, int flags);
		void release();

		TEX_ID TextureID() { return m_TerrainTexID; }
		STRING RessourceName() { return m_TerrainName; }

	private:
		TEX_ID m_TerrainTexID = 0;
		STRING m_TerrainName;
		int m_iFlags;
		
	};
}

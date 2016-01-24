#include "TerrainData.h"

using namespace CKT;

CTerrainData::CTerrainData()
{
}


CTerrainData::~CTerrainData()
{
	release();
}

CKT_RESULT CKT::CTerrainData::init(const STRING & texture, const STRING & terrainName, int flags)
{
	m_TerrainTexID = CTextureManager::instance()->load(texture.c_str());
	if (m_TerrainTexID <= TR_OK)
	{
		CEngine::setErrorFile(texture.c_str());
		return CR_FILENOTFOUND;
	}

	m_TerrainName = terrainName;
	m_iFlags = flags;

	return CR_OK;
}

void CKT::CTerrainData::release()
{
}


#include "RessourceData.h"

using namespace CKT;

CRessourceData::CRessourceData()
{
}

CRessourceData::~CRessourceData()
{
	release();
}

CKT_RESULT CKT::CRessourceData::init(const STRING & texture, const STRING & terrainName)
{
	m_RessourceTexID = CTextureManager::instance()->load(texture.c_str());
	if (m_RessourceTexID <= TR_OK)
	{
		CEngine::setErrorFile(texture.c_str());
		return CR_FILENOTFOUND;
	}

	m_sRessourceName = terrainName;

	return CR_OK;
}

void CKT::CRessourceData::release()
{
}

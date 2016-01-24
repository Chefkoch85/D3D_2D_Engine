#include "Ressource.h"

using namespace CKT;

CRessource::CRessource()
{
}


CRessource::~CRessource()
{
}

CKT_RESULT CKT::CRessource::init(CRessourceData data, BYTE resLevel)
{
	m_TextureID = data.TextureID();
	m_sRessourceName = data.RessourceName();
	m_byRessourceLevel = resLevel;
	return CR_OK;
}

CKT_RESULT CKT::CRessource::draw()
{
	return CR_OK;
}

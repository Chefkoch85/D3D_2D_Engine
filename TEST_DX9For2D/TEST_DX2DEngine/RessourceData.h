#pragma once

#include "Engine.h"
#include "TextureManager.h"

namespace CKT
{
	class CRessourceData
	{
	public:
		CRessourceData();
		~CRessourceData();
		
		CKT_RESULT init(const STRING& texture, const STRING& terrainName);
		void release();

		TEX_ID TextureID() { return m_RessourceTexID; }
		STRING RessourceName() { return m_sRessourceName; }
		
	private:
		TEX_ID m_RessourceTexID = 0;
		STRING m_sRessourceName;
	};
}

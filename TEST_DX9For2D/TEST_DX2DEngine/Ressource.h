#pragma once

#include "Engine.h"
#include "RessourceData.h"

namespace CKT
{
	class CRessource
	{
	public:
		CRessource();
		~CRessource();

		CKT_RESULT init(CRessourceData data, BYTE resLevel = 0);

		CKT_RESULT draw();

		bool& isScouted() { return m_bScouted; }

		STRING& getRessourceName() { return m_sRessourceName; }
		int getRessourceLevel() { return m_byRessourceLevel; }

	private:
		TEX_ID m_TextureID = 0;;
		STRING m_sRessourceName;
		BYTE m_byRessourceLevel = 0;
		bool m_bScouted = false;
	};
}

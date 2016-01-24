#pragma once

#include "Engine.h"
#include "Bounds.h"
#include "TerrainData.h"
#include "Ressource.h"
#include "Sprite.h"

namespace CKT
{
	class CTerrain
	{
	private:
		typedef void (*Selected)(CTerrain& curTerrain);

	public:
		typedef Selected CALLBACK_SELECTED;

		CTerrain();
		~CTerrain();

		CKT_RESULT init(CBounds& bounds, CTerrainData data, STRING region, STRING warzone);
		CKT_RESULT initRessource(CRessourceData data, BYTE resLevel = 0);

		void release();

		CKT_RESULT move(float x, float y, int clickX, int clickY, bool click, float scale = 1.0f);
		CKT_RESULT draw();

		bool& selected() { return m_bIsSelected; }

		void setSpriteBatch(CKT::CSpriteBatch* batch) { m_pSprite->setSpriteBatch(batch); }
		void setCursor(TEX_ID cursor, CSpriteBatch* batch);
		void setCallback(CALLBACK_SELECTED func);

		STRING& getTerrainName() { return m_sTerrainName; }
		STRING& getRegionName() { return m_sRegionName; }
		STRING& getWarzoneName() { return m_sWarzoneName; }

		bool hasResource() { return m_bHasRessource; }
		bool isRessourceVisible() { return m_bHasRessource && m_Ressource.isScouted(); }

		STRING& getRessourceName() { return m_Ressource.getRessourceName(); }
		int getRessourceLevel() { return m_Ressource.getRessourceLevel(); }

	private:
		bool m_bHasRessource = false;
		CRessource m_Ressource;
		TEX_ID m_TextureID = 0;
		CSprite* m_pSprite = NULL;
		CSprite* m_pCursor = NULL;

		int m_iWidth = 0, m_iHeight = 0;
		int m_iX = 0, m_iY = 0;
		float m_fDrawX = 0.0f, m_fDrawY = 0.0f;
		STRING m_sTerrainName, m_sRegionName, m_sWarzoneName;

		bool m_bIsSelected = false;

		CALLBACK_SELECTED m_CallbackSelected = NULL;
	};
}

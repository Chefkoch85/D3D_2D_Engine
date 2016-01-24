#include "Terrain.h"

using namespace CKT;

CTerrain::CTerrain()
{
}


CTerrain::~CTerrain()
{
	release();
}

CKT_RESULT CKT::CTerrain::init(CBounds & bounds, CTerrainData data, STRING region, STRING warzone)
{
	m_iX = bounds.X();
	m_iY = bounds.Y();

	m_TextureID = data.TextureID();
	m_sTerrainName = data.RessourceName();
	m_sRegionName = region;
	m_sWarzoneName = warzone;

	m_iWidth = CKT::CTextureManager::instance()->getTexture(m_TextureID)->Width;
	m_iHeight = CKT::CTextureManager::instance()->getTexture(m_TextureID)->Height;

	m_fDrawX = m_iX * m_iWidth;
	m_fDrawY = m_iY * m_iHeight;

	m_pSprite = new CSprite();
	m_pSprite->init(m_TextureID, m_fDrawX, m_fDrawY);

	return CR_OK;
}

CKT_RESULT CKT::CTerrain::initRessource(CRessourceData data, BYTE resLevel)
{
	CKT_RESULT hr = CR_OK;

	if ((hr = m_Ressource.init(data, resLevel)) != CR_OK)
		return hr;

	m_bHasRessource = true;
	return hr;
}

void CKT::CTerrain::release()
{
	CKT_RELEASE(m_pSprite);
}

CKT_RESULT CTerrain::move(float x, float y, int clickX, int clickY, bool click, float scale)
{
	float fWidth = m_iWidth * scale;
	float fHeight = m_iHeight * scale;

	m_fDrawX = m_iX * fWidth;
	m_fDrawY = m_iY * fHeight;

	m_pSprite->X() = m_fDrawX + x;
	m_pSprite->Y() = m_fDrawY + y;
	m_pSprite->Scale() = scale;

	// check is selected?
	if (m_pCursor && click)
	{
		m_bIsSelected = false;

		float fClickX = clickX - x;
		float fClickY = clickY - y;

		if (fClickX >= m_fDrawX && fClickY >= m_fDrawY &&
			fClickX < m_fDrawX + fWidth && fClickY < m_fDrawY + fHeight)
		{
			m_bIsSelected = true;

			if (m_CallbackSelected)
				m_CallbackSelected(*this);
		}
	}

	// move selection cursor
	if (m_pCursor && m_bIsSelected)
	{
		m_pCursor->X() = m_fDrawX + x;
		m_pCursor->Y() = m_fDrawY + y;
		m_pCursor->Scale() = scale;
	}

	return CR_OK;
}

CKT_RESULT CTerrain::draw()
{
	// draw terrain
	if (!m_pSprite)
		return CR_DRAW;

	m_pSprite->draw();

	// draw selection cursor
	if (m_bIsSelected)
		m_pCursor->draw();

	// draw ressource
	if (m_bHasRessource && m_Ressource.isScouted())
		m_Ressource.draw();

	return CR_OK;
}

void CKT::CTerrain::setCursor(TEX_ID cursor, CSpriteBatch* batch)
{
	m_pCursor = new CSprite();
	m_pCursor->init(cursor, m_fDrawX, m_fDrawY);
	m_pCursor->setSpriteBatch(batch);
}

void CKT::CTerrain::setCallback(CALLBACK_SELECTED func)
{
	m_CallbackSelected = func;
}

#include "Sprite.h"

using namespace CKT;

CSprite::CSprite()
{
}


CSprite::~CSprite()
{
}

<<<<<<< HEAD
HRESULT CSprite::init(const TCHAR* filename)
{
	m_TextureID = CTextureManager::instance()->load(filename);
	if (m_TextureID <= TR_OK)
		return E_FAIL;
=======
CKT_RESULT CSprite::init(const TCHAR* filename)
{
	m_TextureID = CTextureManager::instance()->load(filename);
	if (m_TextureID <= TR_OK)
		return CR_FILENOTFOUND;
>>>>>>> origin/master

	m_iWidth = CTextureManager::instance()->getTexture(m_TextureID)->Width;
	m_iHeight = CTextureManager::instance()->getTexture(m_TextureID)->Height;

	m_rClip.left = 0;
	m_rClip.top = 0;
	m_rClip.right = CDirect3D::instance()->Width();
	m_rClip.bottom = CDirect3D::instance()->Height();

<<<<<<< HEAD
	return S_OK;
}
HRESULT CSprite::init(const TCHAR* filename, float x, float y)
{
	if (init(filename) != S_OK)
		return E_FAIL;
=======
	return CR_OK;
}
CKT_RESULT CSprite::init(const TCHAR* filename, float x, float y)
{
	if (init(filename) != CR_OK)
		return CR_FILENOTFOUND;
>>>>>>> origin/master

	m_fX = x;
	m_fY = y;

<<<<<<< HEAD
	return S_OK;
}
HRESULT CSprite::init(const TCHAR* filename, float x, float y, float scale, float rot)
{
	if (init(filename) != S_OK)
		return E_FAIL;
=======
	return CR_OK;
}
CKT_RESULT CSprite::init(const TCHAR* filename, float x, float y, float scale, float rot)
{
	if (init(filename) != S_OK)
		return CR_FILENOTFOUND;

	m_fX = x;
	m_fY = y;
	m_fScale = scale;
	m_fRotation = rot;

	return CR_OK;
}

CKT_RESULT CKT::CSprite::init(const TEX_ID texID)
{
	m_TextureID = texID;

	m_iWidth = CTextureManager::instance()->getTexture(m_TextureID)->Width;
	m_iHeight = CTextureManager::instance()->getTexture(m_TextureID)->Height;

	m_rClip.left = 0;
	m_rClip.top = 0;
	m_rClip.right = CDirect3D::instance()->Width();
	m_rClip.bottom = CDirect3D::instance()->Height();

	return CR_OK;
}

CKT_RESULT CKT::CSprite::init(const TEX_ID texID, float x, float y)
{
	if (init(texID) != S_OK)
		return CR_FILENOTFOUND;

	m_fX = x;
	m_fY = y;

	return CR_OK;
}

CKT_RESULT CKT::CSprite::init(const TEX_ID texID, float x, float y, float scale, float rot)
{
	if (init(texID) != S_OK)
		return CR_FILENOTFOUND;
>>>>>>> origin/master

	m_fX = x;
	m_fY = y;
	m_fScale = scale;
	m_fRotation = rot;

<<<<<<< HEAD
	return S_OK;
=======
	return CR_OK;
>>>>>>> origin/master
}

void CSprite::release()
{

}

<<<<<<< HEAD
HRESULT CSprite::draw()
=======
CKT_RESULT CSprite::draw()
>>>>>>> origin/master
{
	if (m_pSpriteBatch)
	{
		//m_pSpriteBatch->setClip((int)m_fX, (int)m_fY, CDirect3D::instance()->Width() + (int)m_fX, CDirect3D::instance()->Height() + (int)m_fY);

<<<<<<< HEAD
		if (m_fX >= m_rClip.left - m_iWidth && m_fX <= m_rClip.right &&
			m_fY >= m_rClip.top - m_iHeight && m_fY <= m_rClip.bottom)
=======
		float fWidth = m_iWidth * m_fScale;
		float fHieght = m_iHeight * m_fScale;

		if (m_fX >= m_rClip.left - fWidth && m_fX <= m_rClip.right &&
			m_fY >= m_rClip.top - fHieght && m_fY <= m_rClip.bottom)
>>>>>>> origin/master
		{
			m_pSpriteBatch->setRotationCenter(
				CTextureManager::instance()->getTexture(m_TextureID)->Width * m_fScale / 2.0f,
				CTextureManager::instance()->getTexture(m_TextureID)->Height * m_fScale / 2.0f);

			m_pSpriteBatch->setTransform(m_fX, m_fY, m_fScale, m_fRotation);

			m_pSpriteBatch->draw(m_TextureID);
<<<<<<< HEAD
			return S_OK;
		}
	}

	return E_FAIL;
=======
			return CR_OK;
		}
	}

	return CR_DRAW;
>>>>>>> origin/master
}
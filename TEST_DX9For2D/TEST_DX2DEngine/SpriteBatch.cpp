#include "SpriteBatch.h"

#include "Direct3D.h"

using namespace CKT;

D3DXMATRIX CSpriteBatch::m_mIdentity = D3DXMATRIX(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

CSpriteBatch::CSpriteBatch()
{

}


CSpriteBatch::~CSpriteBatch()
{
}


<<<<<<< HEAD
HRESULT CSpriteBatch::init()
=======
CKT_RESULT CSpriteBatch::init()
>>>>>>> origin/master
{
	D3DXMatrixIdentity(&m_mWorld);
	D3DXMatrixIdentity(&m_mIdentity);
	m_rClip = { 0, 0, 800, 600 };

<<<<<<< HEAD
	return D3DXCreateSprite(CDirect3D::instance()->getDevice(), &m_pSpriteBatch);
=======
	HRESULT hr = D3DXCreateSprite(CDirect3D::instance()->getDevice(), &m_pSpriteBatch);

	return (hr != S_OK) ? CR_SPRITEBATCH : CR_OK;;
>>>>>>> origin/master
}

void CSpriteBatch::release()
{
	if (m_pSpriteBatch)
		m_pSpriteBatch->Release();
}

<<<<<<< HEAD
HRESULT CSpriteBatch::begin(DWORD flags)
{
	return m_pSpriteBatch->Begin(flags);
}
HRESULT CSpriteBatch::end()
{
	return m_pSpriteBatch->End();
=======
CKT_RESULT CSpriteBatch::begin(DWORD flags)
{
	HRESULT hr = m_pSpriteBatch->Begin(flags);
	return (hr != S_OK) ? CR_DRAWBEGINN : CR_OK;;
}
CKT_RESULT CSpriteBatch::end()
{
	HRESULT hr = m_pSpriteBatch->End();
	return (hr != S_OK) ? CR_DRAWEND : CR_OK;
>>>>>>> origin/master
}

void CSpriteBatch::setTransform(float x, float y, float scale, float rot)
{
	D3DXVECTOR2 vTranslation;
	vTranslation.x = x;
	vTranslation.y = y;
	D3DXMatrixAffineTransformation2D(&m_mWorld, scale, &m_vRotCenter, rot, &vTranslation);
	setTransform();
}
void CSpriteBatch::setTransform(D3DXMATRIX world)
{
	m_mWorld = world;
	setTransform();
}

void CSpriteBatch::setClip(int left, int top, int right, int bottom)
{
	m_rClip.left = left;
	m_rClip.top = top;
	m_rClip.right = right;
	m_rClip.bottom = bottom;
}

<<<<<<< HEAD
HRESULT CSpriteBatch::draw(TEX_ID texture)
{
	return m_pSpriteBatch->Draw(
		CTextureManager::instance()->getTexture(texture)->pTextrueData,
		NULL, NULL, NULL, 0xFFFFFFFF);

=======
CKT_RESULT CSpriteBatch::draw(TEX_ID texture)
{
	HRESULT hr = m_pSpriteBatch->Draw(
		CTextureManager::instance()->getTexture(texture)->pTextrueData,
		NULL, NULL, NULL, 0xFFFFFFFF);
	 
	return (hr != S_OK) ? CR_DRAW : CR_OK;
>>>>>>> origin/master
}


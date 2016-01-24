#include "TextureManager.h"


using namespace CKT;


CTextureManager* CTextureManager::m_pInstance = NULL;

CTextureManager::CTextureManager()
{
}


CTextureManager::~CTextureManager()
{
	releaseAll();
}

void CTextureManager::releaseAll()
{
	for each (std::pair<TEX_ID, Texture> pair in m_TextureMap)
	{
		pair.second.pTextrueData->Release();
		pair.second.pTextrueData = NULL;
	}

	m_TextureMap.clear();
}

CTextureManager* CTextureManager::instance()
{
	if (m_pInstance)
		return m_pInstance;

	m_pInstance = new CTextureManager();
	return m_pInstance;
}

CKT::TEX_ID CTextureManager::load(const TCHAR* filename)
{
	LPDIRECT3DTEXTURE9 pTex = NULL;
	D3DSURFACE_DESC sDesc;

	std::wstring temp = filename;
	for each (std::pair<TEX_ID, Texture> pair in m_TextureMap)
	{
		if (temp.compare(pair.second.TexName) == 0)
		{
			return pair.first;
		}
	}

	HRESULT hr = D3DXCreateTextureFromFile(CDirect3D::instance()->getDevice(), filename, &pTex);
	if (hr != S_OK)
		return TR_ERRLOAD;

	pTex->GetLevelDesc(0, &sDesc);

	Texture Tex;
	// +1 so the first tex_id is 0xFF01 because map is empty at this point in the first call
	Tex.IDTextrue = m_TextureMap.size() + 1 + TR_OK;	
	Tex.pTextrueData = pTex;
	Tex.TexName = filename;
	Tex.Width = sDesc.Width;
	Tex.Height = sDesc.Height;

	std::pair<TEX_ID, Texture> pair(Tex.IDTextrue, Tex);
	m_TextureMap.insert(pair);

	return Tex.IDTextrue;
}

CKT::CTextureManager::Texture* CTextureManager::getTexture(TEX_ID texture)
{
	try
	{
		Texture& tex = m_TextureMap.at(texture);
		return &tex;
	}
	catch (std::out_of_range ex)
	{
		return NULL;
	}

}
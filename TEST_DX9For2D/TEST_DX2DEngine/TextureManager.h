#pragma once

#include "Direct3D.h"
#include <map>

namespace CKT
{
	typedef unsigned int TEX_ID;

	enum TexResult
	{
		TR_OK = 0xFF00,
		TR_ERRLOAD = 0x0100,
		TR_ERRNOTFOUND = 0x0200,
	};

	class CTextureManager
	{
	private:
		struct Texture
		{
			TEX_ID IDTextrue;
			int Width, Height;
			std::wstring TexName;
			LPDIRECT3DTEXTURE9 pTextrueData;
		};

	public:
		static CTextureManager* instance();
		~CTextureManager();

		void releaseAll();

		TEX_ID load(const TCHAR* filename);
		Texture* getTexture(TEX_ID texture);

	private:
		static CTextureManager* m_pInstance;
		std::map<TEX_ID, Texture> m_TextureMap;

		CTextureManager();
	};
}

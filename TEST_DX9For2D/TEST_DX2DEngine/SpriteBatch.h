#pragma once

#include <d3dx9math.h>
#include "TextureManager.h"

namespace CKT
{
	class CSpriteBatch
	{
	public:
		CSpriteBatch();
		~CSpriteBatch();

<<<<<<< HEAD
		HRESULT init();
		void release();

		HRESULT begin(DWORD flags);
		HRESULT end();
		HRESULT draw(TEX_ID textureL);
=======
		CKT_RESULT init();
		void release();

		CKT_RESULT begin(DWORD flags);
		CKT_RESULT end();
		CKT_RESULT draw(TEX_ID textureL);
>>>>>>> origin/master

		void setRotationCenter(float x, float y) { m_vRotCenter.x = x; m_vRotCenter.y = y; }
		void setTransform(float x, float y, float scale = 0.0f, float rot = 0.0f);
		void setTransform(D3DXMATRIX world);
		void setClip(int left, int top, int right, int bottom);

		LPD3DXSPRITE getD3DXSprite() { return m_pSpriteBatch; }

		static D3DXMATRIX identity() { return m_mIdentity; }

	private:
		LPD3DXSPRITE m_pSpriteBatch = NULL;
		D3DXMATRIX m_mWorld;
		D3DXVECTOR2 m_vRotCenter;

		static D3DXMATRIX m_mIdentity;
		RECT m_rClip;

		void setTransform() { m_pSpriteBatch->SetTransform(&m_mWorld); }
	};
}

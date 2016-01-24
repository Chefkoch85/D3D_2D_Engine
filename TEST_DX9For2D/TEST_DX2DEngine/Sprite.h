#pragma once

#include "SpriteBatch.h"
#include "TextureManager.h"

namespace CKT
{
	class CSprite
	{
	public:
		CSprite();
		~CSprite();

<<<<<<< HEAD
		virtual HRESULT init(const TCHAR* filename);
		virtual HRESULT init(const TCHAR* filename, float x, float y);
		virtual HRESULT init(const TCHAR* filename, float x, float y, float scale, float rot = 0.0f);
		void release();

		void setSpriteBatch(CSpriteBatch* batch) { m_pSpriteBatch = batch; }
		virtual HRESULT draw();
=======
		virtual CKT_RESULT init(const TCHAR* filename);
		virtual CKT_RESULT init(const TCHAR* filename, float x, float y);
		virtual CKT_RESULT init(const TCHAR* filename, float x, float y, float scale, float rot = 0.0f);
		virtual CKT_RESULT init(const TEX_ID texID);
		virtual CKT_RESULT init(const TEX_ID texID, float x, float y);
		virtual CKT_RESULT init(const TEX_ID texID, float x, float y, float scale, float rot = 0.0f);
		void release();

		void setSpriteBatch(CSpriteBatch* batch) { m_pSpriteBatch = batch; }
		virtual CKT_RESULT draw();
>>>>>>> origin/master

		float& X() { return m_fX; }
		float& Y() { return m_fY; }
		float& Rot() { return m_fRotation; }
		float& Scale() { return m_fScale; }

	private:
		TEX_ID m_TextureID = 0;

		CSpriteBatch* m_pSpriteBatch = NULL;

	protected:
		float m_fX = 0.0f, m_fY = 0.0f;
		float m_fRotation = 0.0f;
		float m_fScale = 1.0f;

		int m_iWidth = 0, m_iHeight = 0;
		RECT m_rClip;
		
	};
}

#pragma once

#include "Direct3D.h"

namespace CKT
{
	class CDX2D
	{
	public:
		CDX2D();
		~CDX2D();

<<<<<<< HEAD
		HRESULT init(CDirect3D* pD3D);
=======
		CKT_RESULT init(CDirect3D* pD3D);
>>>>>>> origin/master
		void release();

	private:
		CDirect3D* m_pD3D = NULL;
		LPD3DXSPRITE m_pSpriteBatch = NULL;

	};
}

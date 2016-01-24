#pragma once

#include <d3d9.h>

#include <D3dx9math.h>

#include "FrameTimer.h"
#include "FpsCounter.h"
<<<<<<< HEAD
=======
#include "Engine.h"
>>>>>>> origin/master

namespace CKT
{

	class CDirect3D
	{
	public:
		~CDirect3D();

		static CDirect3D* instance();

<<<<<<< HEAD
		HRESULT init(HWND hWnd);
=======
		CKT_RESULT init(HWND hWnd);
>>>>>>> origin/master
		
		void release();

		void initD3DParams();
		D3DPRESENT_PARAMETERS&	D3DParams() { return m_D3DParams; }

		LPDIRECT3D9				getD3D() { return m_pD3D; }
		LPDIRECT3DDEVICE9		getDevice() { return m_pD3dDevice; }

		void setMatrixWorld(D3DXMATRIX mWorld) { m_mWorld = mWorld; }
		void setMatrixProjection(D3DXMATRIX mProj) { m_mProjection = mProj; }
		void setMatrixView(D3DXMATRIX mView) { m_mView = mView; }

		int Width() { return m_iWidth; }
		int Height() { return m_iHeight; }
		
	private:
		static CDirect3D* m_pInstance;

		LPDIRECT3D9				m_pD3D = NULL; // Used to create the D3DDevice
		LPDIRECT3DDEVICE9		m_pD3dDevice = NULL; // Our rendering device
		D3DPRESENT_PARAMETERS	m_D3DParams;
		HWND					m_hwWindow = NULL;

		D3DXMATRIX m_mIdentity;
		D3DXMATRIX m_mWorld;
		D3DXMATRIX m_mProjection;
		D3DXMATRIX m_mView;
		
		int m_iWidth = 0, m_iHeight = 0;

		bool m_ParamsInit = false;

		CDirect3D();
	};

#define CKT_RELEASE(x) if(x) x->release(); x = NULL;

}

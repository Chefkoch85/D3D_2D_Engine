#include "Direct3D.h"

using namespace CKT;

CDirect3D* CDirect3D::m_pInstance = NULL;

CDirect3D* CDirect3D::instance()
{
	if (m_pInstance)
		return m_pInstance;

	m_pInstance = new CDirect3D();
	return m_pInstance;
}

CDirect3D::CDirect3D()
{
}


CDirect3D::~CDirect3D()
{
	this->release();
}

void CDirect3D::initD3DParams()
{
	// Set up the structure used to create the D3DDevice. Most parameters are
	// zeroed out. We set Windowed to TRUE, since we want to do D3D in a
	// window, and then set the SwapEffect to "discard", which is the most
	// efficient method of presenting the back buffer to the display.  And 
	// we request a back buffer format that matches the current desktop display 
	// format.
	ZeroMemory(&m_D3DParams, sizeof(D3DPRESENT_PARAMETERS));
	m_D3DParams.Windowed = true;
	m_D3DParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_D3DParams.BackBufferFormat = D3DFMT_UNKNOWN;
	m_D3DParams.BackBufferWidth = m_iWidth;
	m_D3DParams.BackBufferHeight = m_iHeight;
	m_D3DParams.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	//m_D3DParams.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	m_ParamsInit = true;
}

//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
<<<<<<< HEAD
HRESULT CDirect3D::init(HWND hWnd)
{
	// Create the D3D object, which is needed to create the D3DDevice.
	if (NULL == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;
=======
CKT_RESULT CDirect3D::init(HWND hWnd)
{
	// Create the D3D object, which is needed to create the D3DDevice.
	if (NULL == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return CR_D3DINIT;
>>>>>>> origin/master

	m_hwWindow = hWnd;
	RECT r;
	GetClientRect(m_hwWindow, &r);
	
	m_iWidth = r.right - r.left;
	m_iHeight = r.bottom - r.top;

	if (!m_ParamsInit)
		initD3DParams();

	// Create the Direct3D device. Here we are using the default adapter (most
	// systems only have one, unless they have multiple graphics hardware cards
	// installed) and requesting the HAL (which is saying we want the hardware
	// device rather than a software one). Software vertex processing is 
	// specified since we know it will work on all cards. On cards that support 
	// hardware vertex processing, though, we would see a big performance gain 
	// by specifying hardware vertex processing.
	if (FAILED(m_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT, 
		D3DDEVTYPE_HAL,
		m_hwWindow,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&m_D3DParams, 
		&m_pD3dDevice)))
	{
<<<<<<< HEAD
		return E_FAIL;
=======
		return CR_D3DINIT;
>>>>>>> origin/master
	}

	// Device state would normally be set here


	D3DXMatrixIdentity(&m_mIdentity);

<<<<<<< HEAD
	return S_OK;
=======
	return CR_OK;
>>>>>>> origin/master
}

//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
void CDirect3D::release()
{
	if (m_pD3dDevice != NULL)
		m_pD3dDevice->Release();

	if (m_pD3D != NULL)
		m_pD3D->Release();
}


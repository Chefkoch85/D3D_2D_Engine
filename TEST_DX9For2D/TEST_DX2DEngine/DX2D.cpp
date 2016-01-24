#include "DX2D.h"

using namespace CKT;

CDX2D::CDX2D()
{
}


CDX2D::~CDX2D()
{
}

<<<<<<< HEAD
HRESULT CDX2D::init(CKT::CDirect3D* pD3D)
{
	if (pD3D == NULL)
		return E_FAIL;

	m_pD3D = pD3D;
	
	return S_OK;
=======
CKT_RESULT CDX2D::init(CKT::CDirect3D* pD3D)
{
	if (pD3D == NULL)
		return CR_D3D2DINIT;

	m_pD3D = pD3D;
	
	return CR_OK;
>>>>>>> origin/master
}

void CDX2D::release()
{
}
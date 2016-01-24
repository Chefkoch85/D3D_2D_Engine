#include "Input.h"

using namespace CKT;

LPDIRECTINPUT8 CKT::CInput::m_pDInput = NULL;

CInput::CInput()
{
}

CInput::~CInput()
{
	if (m_pDInput)
	{
		m_pDInput->Release();
		m_pDInput = NULL;
	}
}

LPDIRECTINPUT8 CInput::Instance()
{
	if (m_pDInput)
		return m_pDInput;

	HRESULT hr;
	hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDInput, NULL);
	if (FAILED(hr))
	{
		return NULL;
	}

	return m_pDInput;
}
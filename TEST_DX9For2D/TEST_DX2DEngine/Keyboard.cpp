#include "Keyboard.h"

using namespace CKT;

CKeyboard::CKeyboard()
{
	memset(m_byKeys, 0, MAX_KEYBOARD_KEYS);
	memset(m_byOldKeys, 0, MAX_KEYBOARD_KEYS);
}


CKeyboard::~CKeyboard()
{
	release();
}


<<<<<<< HEAD
HRESULT CKeyboard::init(HWND hWnd)
=======
CKT_RESULT CKeyboard::init(HWND hWnd)
>>>>>>> origin/master
{
	m_hWnd = hWnd;

	HRESULT hr = S_OK;
	hr = CInput::Instance()->CreateDevice(GUID_SysKeyboard, &m_pDiKeyboard, NULL);
	if (FAILED(hr))
	{
<<<<<<< HEAD
		return hr;
=======
		return CR_USERINPUTKEYINIT;
>>>>>>> origin/master
	}

	m_pDiKeyboard->SetDataFormat(&c_dfDIKeyboard);
	m_pDiKeyboard->SetCooperativeLevel(m_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

<<<<<<< HEAD
	return hr;
=======
	return CR_OK;
>>>>>>> origin/master
}

void CKeyboard::release()
{
	if (m_pDiKeyboard)
	{
		m_pDiKeyboard->Unacquire();
		m_pDiKeyboard->Release();
		m_pDiKeyboard = NULL;
	}
}

bool CKeyboard::aquire()
{
	// If input is lost then acquire and keep trying until we get it back 
	HRESULT hr = m_pDiKeyboard->Acquire();
	while (hr == DIERR_INPUTLOST)
	{
		OutputDebugString(L"Input lost\n");
		hr = m_pDiKeyboard->Acquire();
	}
	// Could be we failed for some other reason
	if (FAILED(hr))
	{
		//ErrorMessage(L"Can not acquire Keyboard!\n");
		OutputDebugString(L"Can not aquire Keyboard\n");
		return true;
	}

	return false;
}

bool CKeyboard::getState(BYTE keys[256])
{
	HRESULT hr = m_pDiKeyboard->GetDeviceState(sizeof(BYTE) * 256, keys);

	if (FAILED(hr))
	{
		OutputDebugString(L"CKeyboard::getState() failed!\n");
		return true;
	}

	return false;
}

int CKeyboard::update()
{
	for (int i = 0; i < MAX_KEYBOARD_KEYS; i++)
		m_byOldKeys[i] = m_byKeys[i];

	if (aquire())
		return S_OK;

	if (getState(m_byKeys))
		return E_FAIL;

	return S_OK;
}

bool CKeyboard::KeyDown(int keyCode)
{
	return m_byKeys[keyCode] && !m_byOldKeys[keyCode];
}
bool CKeyboard::KeyUp(int keyCode)
{
	return !m_byKeys[keyCode] && m_byOldKeys[keyCode];
}
bool CKeyboard::KeyPress(int keyCode)
{
	return m_byKeys[keyCode];
}
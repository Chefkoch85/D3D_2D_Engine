#include "Mouse.h"
#include "Direct3D.h"

using namespace CKT;

CMouse::CMouse()
{
}


CMouse::~CMouse()
{
	release();
}


<<<<<<< HEAD
HRESULT CMouse::init(HWND hWnd)
=======
CKT_RESULT CMouse::init(HWND hWnd)
>>>>>>> origin/master
{
	m_hWnd = hWnd;

	HRESULT hr = S_OK;
	hr = CInput::Instance()->CreateDevice(GUID_SysMouse, &m_pDiMouse, NULL);
	if (FAILED(hr))
	{
<<<<<<< HEAD
		return hr;
=======
		return CR_USERINPUTMOUSEINIT;
>>>>>>> origin/master
	}

	m_pDiMouse->SetDataFormat(&c_dfDIMouse2);
	m_pDiMouse->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

<<<<<<< HEAD
	return hr;
=======
	return CR_OK;
>>>>>>> origin/master
}

void CMouse::release()
{
	if (m_pDiMouse)
	{
		m_pDiMouse->Unacquire();
		m_pDiMouse->Release();
		m_pDiMouse = NULL;
	}
}

bool CMouse::aquire()
{
	bool first = true;

	// If input is lost then acquire and keep trying until we get it back 
	HRESULT hr = m_pDiMouse->Acquire();

	while (hr == DIERR_INPUTLOST)
	{
		OutputDebugString(L"Input lost\n");
		hr = m_pDiMouse->Acquire();
	}
	// Could be we failed for some other reason
	if (FAILED(hr))
	{
		//ErrorMessage(L"Can not acquire Keyboard!\n");
		OutputDebugString(L"Can not aquire Mouse\n");
		return true;
	}

	return false;
}

bool CMouse::getState(DIMOUSESTATE2& mouse)
{
	HRESULT hr = m_pDiMouse->GetDeviceState(sizeof(DIMOUSESTATE2), &mouse);

	if (FAILED(hr))
	{
		OutputDebugString(L"CMouse::getState() failed!\n");
		return true;
	}

	return false;
}

int CMouse::update()
{
	for (int i = 0; i < MAX_MOUSE_KEYS; i++)
		m_OldMouse.rgbButtons[i] = m_Mouse.rgbButtons[i];

	m_OldMouse.lX = m_Mouse.lX;
	m_OldMouse.lY = m_Mouse.lY;
	m_OldMouse.lZ = m_Mouse.lZ;

	if (aquire())
		return S_OK;

	if (getState(m_Mouse))
		return E_FAIL;

	GetCursorPos(&m_MouseStartPos);
	ScreenToClient(m_hWnd, &m_MouseStartPos);
	m_iAbsX = m_MouseStartPos.x;
	m_iAbsY = m_MouseStartPos.y;

	return S_OK;
}

bool CMouse::KeyDown(MouseKeys keyCode)
{
	return (m_Mouse.rgbButtons[keyCode] & 0x80) && !(m_OldMouse.rgbButtons[keyCode] & 0x80);
}
bool CMouse::KeyUp(MouseKeys keyCode)
{
	return !(m_Mouse.rgbButtons[keyCode] & 0x80) && (m_OldMouse.rgbButtons[keyCode] & 0x80);
}
bool CMouse::KeyPress(MouseKeys keyCode)
{
	return m_Mouse.rgbButtons[keyCode] & 0x80;
}

int CMouse::Wheel()
{
	return m_Mouse.lZ;
}
int CMouse::WheelForward()
{
	if (m_Mouse.lZ > 0)
		return m_Mouse.lZ;

	return 0;
}
int CMouse::WheelBackward()
{
	if (m_Mouse.lZ < 0)
		return -m_Mouse.lZ;

	return 0;
}

int CMouse::X()
{
	return m_iAbsX;
}
int CMouse::Y()
{
	return m_iAbsY;
}

int CMouse::relX()
{
	return m_Mouse.lX;
}
int CMouse::relY()
{
	return m_Mouse.lY;
}

POINT CMouse::Pos()
{
	POINT p;
	p.x = m_iAbsX;
	p.y = m_iAbsY;
	return p;
}
POINT CMouse::relPos()
{
	POINT p;
	p.x = m_Mouse.lX;
	p.y = m_Mouse.lY;
	return p;
}

bool CMouse::isInWindow()
{
	if (m_iAbsX < 0 || m_iAbsY < 0)
		return false;

	if (m_iAbsX >= CDirect3D::instance()->Width() || m_iAbsY >= CDirect3D::instance()->Height())
		return false;

	return true;
}

<<<<<<< HEAD
=======
bool CKT::CMouse::isAtEdge(EEdge witch, int dist)
{
	if (!isInWindow())
		return false;

	switch (witch)
	{
	case ED_TOP:
		if (m_iAbsY <= (0 + dist))
			return true;

		break;

	case ED_BOTTOM:
		if (m_iAbsY >= (CDirect3D::instance()->Height() - dist))
			return true;

		break;

	case ED_LEFT:
		if (m_iAbsX <= (0 + dist))
			return true;

		break;

	case ED_RIGHT:
		if (m_iAbsX >= (CDirect3D::instance()->Width() - dist))
			return true;

		break;
	}

	return false;
}

float CKT::CMouse::atEdge(EEdge witch, float min, float max, int dist)
{
	if (!isInWindow())
		return 0.0f;

	float diff = 0.0f;
	switch (witch)
	{
	case ED_TOP:
		if (m_iAbsY <= (0 + dist))
			diff = (dist - m_iAbsY);

		break;

	case ED_BOTTOM:
		if (m_iAbsY >= (CDirect3D::instance()->Height() - dist))
			diff = -(dist - (CDirect3D::instance()->Height() - m_iAbsY));

		break;

	case ED_LEFT:
		if (m_iAbsX <= (0 + dist))
			diff = (dist - m_iAbsX);

		break;

	case ED_RIGHT:
		if (m_iAbsX >= (CDirect3D::instance()->Width() - dist))
			diff = -(dist - (CDirect3D::instance()->Width() - m_iAbsX));

		break;
	}

	return diff * max / min;
}

>>>>>>> origin/master

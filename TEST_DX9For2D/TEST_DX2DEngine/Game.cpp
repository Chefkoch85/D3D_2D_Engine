#include "Game.h"

using namespace CKT;

CGame::CGame(HWND hWnd, CFileReader& iniReader)
	:
	m_StartupReader(iniReader)
{
	m_hWnd = hWnd;
	m_bHasFileReader = iniReader.hasRead();
}


CGame::~CGame()
{
}

<<<<<<< HEAD
HRESULT CGame::initD3D()
{
	HRESULT hr = S_OK;
=======
CKT_RESULT CGame::initD3D()
{
	CKT_RESULT hr = CR_OK;
>>>>>>> origin/master

	m_pD3D = CDirect3D::instance();

	m_pD3D->initD3DParams();
	UserD3DParams();

<<<<<<< HEAD
	if ((hr = m_pD3D->init(m_hWnd)) != S_OK)
=======
	if ((hr = m_pD3D->init(m_hWnd)) != CR_OK)
>>>>>>> origin/master
	{
		return hr;
	}

<<<<<<< HEAD
	return S_OK;
}

HRESULT CGame::init()
{
	HRESULT hr = S_OK;

	if ((hr = initD3D()) != S_OK)
=======
	return CR_OK;
}

CKT_RESULT CGame::init()
{
	CKT_RESULT hr = CR_OK;

	if ((hr = initD3D()) != CR_OK)
>>>>>>> origin/master
	{
		return hr;
	}

<<<<<<< HEAD
	if ((hr = initSubSystem()) != S_OK)
=======
	if ((hr = initSubSystem()) != CR_OK)
>>>>>>> origin/master
	{
		release();
		return hr;
	}

<<<<<<< HEAD
	if ((hr = loadContent()) != S_OK)
=======
	if ((hr = loadContent()) != CR_OK)
>>>>>>> origin/master
	{
		release();
		return hr;
	}

	m_FpsCounter.Initialize();
	m_FrameTimer.Initialize();

	return hr;
}

void CGame::release()
{
	unloadContent();

	releaseSubSystem();

	if (m_pD3D)
		CKT_RELEASE(m_pD3D);
}


//-----------------------------------------------------------------------------
// Name: Run()
// Desc: Runs the Game
// TODO: move this funktion in the GameClass
//-----------------------------------------------------------------------------
<<<<<<< HEAD
HRESULT CGame::run()
{
	if (!m_bIsActiv)
		return S_OK;
=======
CKT_RESULT CGame::run()
{
	if (!m_bIsActiv)
		return CR_OK;
>>>>>>> origin/master

	m_FpsCounter.Frame();
	m_FrameTimer.FrameBeginn();

	this->move(m_FrameTimer.GetTimeS());

	LPDIRECT3DDEVICE9 dev = m_pD3D->getDevice();

	if (NULL == dev)
<<<<<<< HEAD
		return E_FAIL;
=======
		return CR_D3DRUN;
>>>>>>> origin/master

	// Clear the backbuffer to a blue color
	dev->Clear(0, NULL, D3DCLEAR_TARGET, m_ClearColor, 1.0f, 0);

	// Begin the scene
	if (SUCCEEDED(dev->BeginScene()))
	{
		// Rendering of scene objects can happen here
		this->render();

		// End the scene
		dev->EndScene();
	}

	// Present the backbuffer contents to the display
	dev->Present(NULL, NULL, NULL, NULL);

	m_FrameTimer.FrameEnd();

<<<<<<< HEAD
	return S_OK;
=======
	return CR_OK;
>>>>>>> origin/master
}

void CGame::activate(bool activ)
{
	m_bIsActiv = activ;
}

<<<<<<< HEAD
LRESULT CGame::GameLoop()
{
	// Initialize Direct3D
	if (SUCCEEDED(this->init()))
=======
CKT_RESULT CGame::GameLoop()
{
	CKT_RESULT hr = CR_OK;
	// Initialize Direct3D
	if ((hr = init()) == CR_OK)
>>>>>>> origin/master
	{
		// Show the window
		ShowWindow(m_hWnd, SW_SHOWDEFAULT);
		UpdateWindow(m_hWnd);

		// Enter the message loop
		MSG msg = {};
		while (msg.message != WM_QUIT)
		{
			if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				this->run();
			}
		}
	}
	else
	{
		//TODO: show startup error message
<<<<<<< HEAD
		return E_FAIL;	// error during initialize
	}

	return S_OK;
=======
		return hr;	// error during initialize
	}

	return CR_OK;
>>>>>>> origin/master
}

LRESULT CGame::messageProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	RECT* rSizing;
	static RECT rWindowRect;

	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_ACTIVATE:
		GetWindowRect(hWnd, &rWindowRect);

		if (LOWORD(wParam) > 0)
		{
			OutputDebugString(L"ACTIVE\n");
			this->activate();
		}
		else
		{
			OutputDebugString(L"PAUSED\n");
			this->activate(false);
		}
		return 0;

	case WM_SIZING:
		// to prevent the resizing of the window
		rSizing = (RECT*)lParam;
		*rSizing = rWindowRect;
		return 0;
	}
	
	return 0;
}

<<<<<<< HEAD
void CKT::CGame::showErrorDialog(STRING errCaption, STRING errClass, STRING errDesc)
{
	STRING sMessage = L"ERROR - CLASS:\n" + errClass + L"\n\nERROR - DESCRIPTION:\n" + errDesc;
	MessageBox(m_hWnd, sMessage.c_str(), (L"ERROR: " + errCaption).c_str(), MB_OK);
}

=======
>>>>>>> origin/master

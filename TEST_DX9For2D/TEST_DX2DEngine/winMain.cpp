
#include <Windows.h>
#include <Windowsx.h>

#include "MyGame.h"
#include <string>

//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
CKT::CGame* g_pGame = NULL;

//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (g_pGame != NULL && g_pGame->messageProc(hWnd, msg, wParam, lParam) > 0)
	{
		return 0;
	}
	else
	{
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
}




//-----------------------------------------------------------------------------
// Name: wWinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, INT)
{
	UNREFERENCED_PARAMETER(hInst);

	CKT::CFileReader* pIniReader = NULL;
	pIniReader = new CKT::CFileReader();
	pIniReader->init(L"..\\RES\\STARTUP.INI");
	pIniReader->read();

	// Register the window class
	WNDCLASSEX wc =
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		MsgProc,
		0L,
		0L,
		GetModuleHandle(NULL),
		NULL,
		NULL,
		NULL,
		NULL,
		CKT::CEngine::WINDOW_CLASS_NAME,
		NULL
	};
	RegisterClassEx(&wc);

	// choose only, from graphicscard, supported Resolution
	RECT winRect;
	winRect.left = 8;
	winRect.right = 800 + winRect.left;
	winRect.top = 31;
	winRect.bottom = 600 + winRect.top;
	if (pIniReader && pIniReader->hasRead())
	{
		winRect.right = winRect.left + pIniReader->getEntryAsInt(L"WIDTH", L"GRAPHIC");
		winRect.bottom = winRect.top + pIniReader->getEntryAsInt(L"HEIGHT", L"GRAPHIC");
	}

	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, false);

	std::wstring sAppName = L"CKT - ENGINE : Test";
	if (pIniReader && pIniReader->hasRead())
	{
		sAppName = pIniReader->getEntryAsString(L"APPNAME", L"GENERAL");
	}

	// Create the application's window
	HWND hWnd = CreateWindow(
		CKT::CEngine::WINDOW_CLASS_NAME,
		sAppName.c_str(),
		WS_OVERLAPPEDWINDOW,
		winRect.left,
		winRect.top,
		winRect.right,
		winRect.bottom,
		NULL,
		NULL,
		wc.hInstance,
		NULL);

	g_pGame = new CMyGame(hWnd, *pIniReader);

	g_pGame->GameLoop();

	CKT_RELEASE(g_pGame);
	if (pIniReader)
	{
		delete pIniReader;
		pIniReader = NULL;
	}

	UnregisterClass(CKT::CEngine::WINDOW_CLASS_NAME, wc.hInstance);

	return 0;
}



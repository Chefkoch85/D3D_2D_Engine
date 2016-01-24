//-----------------------------------------------------------------------------
// File: CreateDevice.cpp
//
// Desc: This is the first tutorial for using Direct3D. In this tutorial, all
//       we are doing is creating a Direct3D device and using it to clear the
//       window.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------
//#define D3D_DEBUG_INFO
#include <d3d9.h>
#include <D3dx9math.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 )

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>

#include <Windowsx.h>

#include <fstream>
using namespace std;

#include "FpsCounter.h"
#include "FrameTimer.h"
#include "TextInput.h"

//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
LPDIRECT3D9				g_pD3D = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9		g_pd3dDevice = NULL; // Our rendering device

LPDIRECTINPUT8			g_pDInput = NULL;
LPDIRECTINPUTDEVICE8	g_pDiKeyboard = NULL;
LPDIRECTINPUTDEVICE8	g_pDiMouse = NULL;

LPD3DXSPRITE g_pSpriteBatch = NULL;
LPD3DXSPRITE g_pSpriteBatch2 = NULL;
LPDIRECT3DTEXTURE9 g_pTexture = NULL;
LPDIRECT3DTEXTURE9 g_pPlayerTex = NULL;
LPDIRECT3DTEXTURE9 g_pDebugTex = NULL;
LPD3DXFONT g_pFont = NULL;
LPD3DXFONT g_pDebugFont = NULL;

bool g_bPaused = false;
bool g_bDebug = false;
#ifdef _DEBUG
bool g_bDebugMode = true;
#else
bool g_bDebugMode = false;
#endif

CFpsCounter g_Fps;
int g_fps[100] = { 0 };
CFrameTimer g_FrameTimer;

bool g_bError = false;
D3DXVECTOR2 g_vPos = { 300, 200 };
D3DXVECTOR2 g_vAcc = {};
D3DXVECTOR2 g_vScale = { 1.0f, 1.0f };
float g_rotAcc = 0;
float g_curRot = 0;

TCHAR g_aText[17] = { 0 };

D3DXMATRIX g_mIdentity;
D3DXMATRIX g_mWorld1;



//-----------------------------------------------------------------------------
// Name: ErrorMessage()
// Desc: displays an error message to the output and set error signal
//-----------------------------------------------------------------------------
void ErrorMessage(PTCHAR msg)
{
	OutputDebugString(msg);
	g_bError = true;
}



//-----------------------------------------------------------------------------
// Name: Initialize2D()
// Desc: Initializes 2D Rendering
//-----------------------------------------------------------------------------
void Initialize2D(HWND hWnd)
{
	HRESULT hr;
	hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pDInput, NULL);
	if (FAILED(hr))
	{
		ErrorMessage(L"Error creating DINPUT!\n");
	}
	hr = g_pDInput->CreateDevice(GUID_SysKeyboard, &g_pDiKeyboard, NULL);
	if (FAILED(hr))
	{
		ErrorMessage(L"Error creating Keyboard device!\n");
	}
	hr = g_pDInput->CreateDevice(GUID_SysMouse, &g_pDiMouse, NULL);
	if (FAILED(hr))
	{
		ErrorMessage(L"Error creating Keyboard device!\n");
	}

	g_pDiKeyboard->SetDataFormat(&c_dfDIKeyboard);
	g_pDiKeyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	g_pDiMouse->SetDataFormat(&c_dfDIMouse2);
	g_pDiMouse->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);


	D3DXCreateSprite(g_pd3dDevice, &g_pSpriteBatch);

	g_Fps.Initialize();
	g_FrameTimer.Initialize();

	hr = D3DXCreateTextureFromFile(g_pd3dDevice, L"../RES/FIRE.dds", &g_pTexture);
	if (FAILED(hr))
	{
		ErrorMessage(L"Error loading Texture \" ../RES/FIRE.dds \"!\n");
	}
	hr = D3DXCreateTextureFromFile(g_pd3dDevice, L"../RES/PLAYER.png", &g_pPlayerTex);
	if (FAILED(hr))
	{
		ErrorMessage(L"Error loading Texture \" ../RES/PLAYER.png \"!\n");
	}
	hr = D3DXCreateTextureFromFile(g_pd3dDevice, L"../RES/DEBUG.png", &g_pDebugTex);
	if (FAILED(hr))
	{
		ErrorMessage(L"Error loading Texture \" ../RES/DEBUG.png \"!\n");
	}
	hr = D3DXCreateFont(g_pd3dDevice, 16, 0, 0, 0, FALSE,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		L"Consolas",
		&g_pDebugFont);
	if (FAILED(hr))
	{
		ErrorMessage(L"Error loading Font!\n");
	}

	hr = D3DXCreateFont(g_pd3dDevice, 24, 0, FW_BOLD, 0, FALSE,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		L"Consolas",
		&g_pFont);
	if (FAILED(hr))
	{
		ErrorMessage(L"Error loading Font!\n");
	}

	D3DXMatrixIdentity(&g_mIdentity);
}



//-----------------------------------------------------------------------------
// Name: AcqiureInputDevices()
// Desc: Acqures the input devices
//-----------------------------------------------------------------------------
bool AcquireInputDevices()
{
	//OutputDebugString(L"Acquire()\n");

	// If input is lost then acquire and keep trying until we get it back 
	HRESULT hr = g_pDiKeyboard->Acquire();
	while (hr == DIERR_INPUTLOST)
	{
		OutputDebugString(L"Input lost\n");
		hr = g_pDiKeyboard->Acquire();
	}
	// Could be we failed for some other reason
	if (FAILED(hr))
	{
		//ErrorMessage(L"Can not acquire Keyboard!\n");
		OutputDebugString(L"Can not aquire Keyboard\n");
		return true;
	}

	hr = g_pDiMouse->Acquire();
	while (hr == DIERR_INPUTLOST)
	{
		OutputDebugString(L"Input lost\n");
		hr = g_pDiMouse->Acquire();
	}
	// Could be we failed for some other reason
	if (FAILED(hr))
	{
		//ErrorMessage(L"Can not acquire Keyboard!\n");
		OutputDebugString(L"Can not aquire Mouse\n");
		return true;
	}
	//OutputDebugString(L"Acquire() succeeded!\n");
	return false;
}



//-----------------------------------------------------------------------------
// Name: AcqiureInputDevices()
// Desc: Acqures the input devices
//-----------------------------------------------------------------------------
bool GetInputStates(BYTE keys[256], DIMOUSESTATE2& mouse)
{
	//OutputDebugString(L"GetInputStates()!\n");
	// Now read the state again
	HRESULT hr = g_pDiKeyboard->GetDeviceState(sizeof(BYTE) * 256, keys);

	if (FAILED(hr))
	{
		OutputDebugString(L"GetInputStates() Keyboard failed!\n");
		return true;
	}

	hr = g_pDiMouse->GetDeviceState(sizeof(DIMOUSESTATE2), &mouse);

	if (FAILED(hr))
	{
		OutputDebugString(L"GetInputStates() Mouse failed!\n");
		return true;
	}

	//TCHAR buf[64] = { 0 };
	//swprintf_s(buf, 64, L"X=%i Y=%i Z=%i\n", mouse.lX, mouse.lY, mouse.lZ);
	//OutputDebugString(buf);

	//OutputDebugString(L"GetInputStates() succeeded!\n");
	return false;
}



//-----------------------------------------------------------------------------
// Name: Update()
// Desc: Update the scene
//-----------------------------------------------------------------------------
void Update(float time)
{
	BYTE Keys[256] = { 0 };
	DIMOUSESTATE2 Mouse = {};

	if (AcquireInputDevices())
		return;

	if (GetInputStates(Keys, Mouse))
		return;

	static bool enter = false;
	if (Keys[DIK_TAB] && !enter)
	{
		g_bDebug = !g_bDebug;
		enter = true;
	}
	else if (!Keys[DIK_TAB] && enter)
	{
		enter = false;
	}

	if (g_bDebug)
		return;

	if (Keys[DIK_A] & 0x80)
	{
		g_vAcc.x -= 5 * time;
	}
	else if (Keys[DIK_D] & 0x80)
	{
		g_vAcc.x += 5 * time;
	}
	else
	{
		if (g_vAcc.x > 0)
		{
			g_vAcc.x -= 3 * time;

			if (g_vAcc.x < 0)
				g_vAcc.x = 0;
		}
		else if (g_vAcc.x < 0)
		{
			g_vAcc.x += 3 * time;

			if (g_vAcc.x > 0)
				g_vAcc.x = 0;
		}
	}

	if (Keys[DIK_W])
	{
		g_vAcc.y -= 5 * time;
	}
	else if (Keys[DIK_S])
	{
		g_vAcc.y += 5 * time;
	}
	else
	{
		if (g_vAcc.y > 0)
		{
			g_vAcc.y -= 3 * time;

			if (g_vAcc.y < 0)
				g_vAcc.y = 0;
		}
		else if (g_vAcc.y < 0)
		{
			g_vAcc.y += 3 * time;

			if (g_vAcc.y > 0)
				g_vAcc.y = 0;
		}
	}

	if (g_vAcc.x < -5)
		g_vAcc.x = -5;
	if (g_vAcc.x > 5)
		g_vAcc.x = 5;
	if (g_vAcc.y < -5)
		g_vAcc.y = -5;
	if (g_vAcc.y > 5)
		g_vAcc.y = 5;

	g_vPos.x += g_vAcc.x;
	g_vPos.y += g_vAcc.y;

	if (g_vPos.x < 0)
	{
		g_vPos.x = 0;
		g_vAcc.x = 0;
	}
	else if (g_vPos.x > 750)
	{
		g_vPos.x = 750;
		g_vAcc.x = 0;
	}

	if (g_vPos.y < 0)
	{
		g_vPos.y = 0;
		g_vAcc.y = 0;
	}
	else if (g_vPos.y > 550)
	{
		g_vPos.y = 550;
		g_vAcc.y = 0;
	}

	if (Keys[DIK_Q])
	{
		g_rotAcc -= 5 * time;
	}
	else if (Keys[DIK_E])
	{
		g_rotAcc += 5 * time;
	}
	else
	{
		if (g_rotAcc > 0)
		{
			g_rotAcc -= 3 * time;

			if (g_rotAcc < 0)
				g_rotAcc = 0;
		}
		else if (g_rotAcc < 0)
		{
			g_rotAcc += 3 * time;

			if (g_rotAcc > 0)
				g_rotAcc = 0;
		}
	}

	if (g_rotAcc < -5)
		g_rotAcc = -5;
	if (g_rotAcc > 5)
		g_rotAcc = 5;

	g_curRot += g_rotAcc;
	if (g_curRot >= 360)
		g_curRot -= 360;
	if (g_curRot <= -360)
		g_curRot += 360;

	if (Mouse.lZ < 0)
	{
		g_vScale.x -= 5 * time;
		g_vScale.y -= 5 * time;
	}
	else if (Mouse.lZ > 0)
	{
		g_vScale.x += 5 * time;
		g_vScale.y += 5 * time;
	}

	if (g_vScale.x <= 0.2f)
	{
		g_vScale.x = 0.2f;
	}
	if (g_vScale.y <= 0.2f)
	{
		g_vScale.y = 0.2f;
	}

	D3DXMATRIX mCenter = {};
	D3DXMatrixTranslation(&mCenter, -16, -16, 0);

	D3DXMATRIX mScale = {};
	D3DXMatrixScaling(&mScale, g_vScale.x, g_vScale.y, 0);
	D3DXMATRIX mRotZ = {};
	D3DXMatrixRotationZ(&mRotZ, D3DXToRadian(g_curRot));
	D3DXMATRIX mTran = {};
	D3DXMatrixTranslation(&mTran, g_vPos.x, g_vPos.y, 0);

	g_mWorld1 = mCenter * mRotZ * mScale * mTran;
}



//-----------------------------------------------------------------------------
// Name: Render2D()
// Desc: Render the scene
//-----------------------------------------------------------------------------
void Render2D()
{
	static TCHAR buf[64];

	g_pSpriteBatch->Begin(D3DXSPRITE_ALPHABLEND);

	if (!g_bError)
	{
		g_pSpriteBatch->SetTransform(&g_mIdentity);
		D3DXVECTOR3 pos = { 250, 50, 0 };
		g_pSpriteBatch->Draw(g_pTexture, NULL, NULL, &pos, 0xFFFFFFFF);

		g_pSpriteBatch->SetTransform(&g_mWorld1);
		g_pSpriteBatch->Draw(g_pPlayerTex, NULL, NULL, NULL, 0xFFFFFFFF);

		g_pSpriteBatch->SetTransform(&g_mIdentity);
		if (g_bDebug)
		{
			RECT rDebug = { 0, 0, 799, 20 };
			g_pSpriteBatch->Draw(g_pDebugTex, &rDebug, NULL, NULL, 0xFFFFFFFF);
			RECT rDebugText = { 5, 2, 799, 0 };
			rDebugText.bottom = rDebugText.top + 20;
			g_pDebugFont->DrawTextW(g_pSpriteBatch, L">", -1, &rDebugText, 0, D3DCOLOR_ARGB(0xA0, 200, 200, 200));
			rDebugText.left = rDebugText.left + 10;
			g_pDebugFont->DrawTextW(g_pSpriteBatch, g_aText, -1, &rDebugText, 0, D3DCOLOR_ARGB(0xA0, 200, 200, 200));
		}

		RECT rText = { 5, 5, 799, 0 };
		//rText.right = rText.left + 200;
		rText.bottom = rText.top + 24;
		g_pFont->DrawTextW(g_pSpriteBatch, L"Hello DirectX 9", -1, &rText, DT_CENTER, D3DCOLOR_ARGB(255, 255, 0, 0));

		rText.top += 26;
		rText.bottom = rText.top + 24;
		swprintf_s(buf, 64, L"FPS = %i\n", g_Fps.getCurFps());
		g_pFont->DrawTextW(g_pSpriteBatch, buf, -1, &rText, DT_CENTER, D3DCOLOR_ARGB(255, 255, 0, 0));

		rText.top += 26;
		rText.bottom = rText.top + 24;
		swprintf_s(buf, 64, L"TEXT: %s", g_aText);
		g_pFont->DrawTextW(g_pSpriteBatch, buf, -1, &rText, DT_CENTER, D3DCOLOR_ARGB(255, 255, 0, 0));

		rText.top += 26;
		rText.bottom = rText.top + 24;
		swprintf_s(buf, 64, L"DEBUG CONSOLE: %s", g_bDebug ? L"YES" : L"NO");
		g_pFont->DrawTextW(g_pSpriteBatch, buf, -1, &rText, DT_CENTER, D3DCOLOR_ARGB(255, 255, 0, 0));

		rText.top += 26;
		rText.bottom = rText.top + 24;
		swprintf_s(buf, 64, L"DEBUG MODE: %s", g_bDebugMode ? L"YES" : L"NO");
		g_pFont->DrawTextW(g_pSpriteBatch, buf, -1, &rText, DT_CENTER, D3DCOLOR_ARGB(255, 255, 0, 0));
	}

	g_pSpriteBatch->End();
}



//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
HRESULT InitD3D(HWND hWnd)
{
	// Create the D3D object, which is needed to create the D3DDevice.
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	// Set up the structure used to create the D3DDevice. Most parameters are
	// zeroed out. We set Windowed to TRUE, since we want to do D3D in a
	// window, and then set the SwapEffect to "discard", which is the most
	// efficient method of presenting the back buffer to the display.  And 
	// we request a back buffer format that matches the current desktop display 
	// format.
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = true;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	//d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	// Create the Direct3D device. Here we are using the default adapter (most
	// systems only have one, unless they have multiple graphics hardware cards
	// installed) and requesting the HAL (which is saying we want the hardware
	// device rather than a software one). Software vertex processing is 
	// specified since we know it will work on all cards. On cards that support 
	// hardware vertex processing, though, we would see a big performance gain 
	// by specifying hardware vertex processing.
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice)))
	{
		return E_FAIL;
	}

	// Device state would normally be set here

	return S_OK;
}




//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID Cleanup()
{
	if (g_pFont)
		g_pFont->Release();

	if (g_pDebugFont)
		g_pDebugFont->Release();

	if (g_pPlayerTex)
		g_pPlayerTex->Release();

	if (g_pDebugTex)
		g_pDebugTex->Release();

	if (g_pTexture)
		g_pTexture->Release();

	if (g_pSpriteBatch)
		g_pSpriteBatch->Release();

	if (g_pDiMouse)
	{
		g_pDiMouse->Unacquire();
		g_pDiMouse->Release();
	}

	if (g_pDiKeyboard)
	{
		g_pDiKeyboard->Unacquire();
		g_pDiKeyboard->Release();
	}

	if (g_pDInput)
		g_pDInput->Release();

	if (g_pd3dDevice != NULL)
		g_pd3dDevice->Release();

	if (g_pD3D != NULL)
		g_pD3D->Release();
}




//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
VOID Render()
{
	if (NULL == g_pd3dDevice)
		return;

	// Clear the backbuffer to a blue color
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	// Begin the scene
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		// Rendering of scene objects can happen here
		Render2D();

		// End the scene
		g_pd3dDevice->EndScene();
	}

	// Present the backbuffer contents to the display
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}



//-----------------------------------------------------------------------------
// Name: Run()
// Desc: Runs the Game
//-----------------------------------------------------------------------------
void Run()
{
	g_Fps.Frame();
	g_FrameTimer.FrameBeginn();

	Update(g_FrameTimer.GetTimeS());
	Render();

	g_FrameTimer.FrameEnd();

	//TCHAR buf[64];
	//swprintf_s(buf, 64, L"frame time = %f\n", g_FrameTimer.GetTimeS());
	//OutputDebugString(buf);

}



//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static int index = 0;
	static TextInputServer textServ(0);

	switch (msg)
	{
	case WM_DESTROY:
		Cleanup();
		PostQuitMessage(0);
		return 0;

	case WM_ACTIVATE:
		if (LOWORD(wParam) > 0)
		{
			OutputDebugString(L"ACTIVE\n");
			g_bPaused = false;
		}
		else
		{
			OutputDebugString(L"PAUSED\n");
			g_bPaused = true;
		}
		return 0;

	case WM_CHAR:
		textServ.putChar(wParam);
		/*if (wParam == 8)
		{
			if (index > 0)
			{
				index--;
				g_aText[index] = ' ';
			}

			return 0;
		}
		g_aText[index++] = (char)wParam;
		index %= 16;*/
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}




//-----------------------------------------------------------------------------
// Name: wWinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, INT)
{
	UNREFERENCED_PARAMETER(hInst);

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
		L"D3D Tutorial",
		NULL
	};
	RegisterClassEx(&wc);

	RECT winRect;
	winRect.left = 8;
	winRect.right = 800 + winRect.left;
	winRect.top = 31;
	winRect.bottom = 600 + winRect.top;

	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, false);

	// Create the application's window
	HWND hWnd = CreateWindow(
		L"D3D Tutorial",
		L"D3D Tutorial 01: CreateDevice",
		WS_OVERLAPPEDWINDOW,
		winRect.left,
		winRect.top,
		winRect.right,
		winRect.bottom,
		NULL,
		NULL,
		wc.hInstance,
		NULL);

	// Initialize Direct3D
	if (SUCCEEDED(InitD3D(hWnd)))
	{
		Initialize2D(hWnd);

		// Show the window
		ShowWindow(hWnd, SW_SHOWDEFAULT);
		UpdateWindow(hWnd);

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
				if (!g_bPaused)
					Run();
			}
		}
	}

	TCHAR buf[64];
	wsprintf(buf, L"average FPS = %i", g_Fps.getAverageFps());
	MessageBox(NULL, buf, L"INFO", 0);

	UnregisterClass(L"D3D Tutorial", wc.hInstance);
	return 0;
}




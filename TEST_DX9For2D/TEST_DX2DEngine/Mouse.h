#pragma once

#include "Input.h"

#include <string.h>

namespace CKT
{
	enum MouseKeys
	{
		MB_Left = 0,
		MB_Right = 1,
		MB_Middle = 2,
	};

<<<<<<< HEAD
=======
	enum EEdge
	{
		ED_NONE		= 0x00,
		ED_TOP		= 0x01,
		ED_BOTTOM	= 0x02,
		ED_LEFT		= 0x04,
		ED_RIGHT	= 0x08,
	};

>>>>>>> origin/master
	class CMouse
	{
	public:
		CMouse();
		~CMouse();

<<<<<<< HEAD
		HRESULT init(HWND hWnd);
=======
		CKT_RESULT init(HWND hWnd);
>>>>>>> origin/master
		void release();

		int update();

		bool KeyDown(MouseKeys keyCode);
		bool KeyUp(MouseKeys keyCode);
		bool KeyPress(MouseKeys keyCode);

		int WheelForward();
		int WheelBackward();
		int Wheel();

		int X();
		int Y();

		int relX();
		int relY();

		POINT Pos();
		POINT relPos();

		bool isInWindow();
<<<<<<< HEAD
=======
		bool isAtEdge(EEdge witch, int dist = 20);
		float atEdge(EEdge witch, float min = 1.0f, float max = 10.0f, int dist = 60);
>>>>>>> origin/master

		void setMouseCursor();

	private:
		HWND m_hWnd = NULL;
		LPDIRECTINPUTDEVICE8 m_pDiMouse = NULL;

#define MAX_MOUSE_KEYS 8
		DIMOUSESTATE2 m_Mouse;
		DIMOUSESTATE2 m_OldMouse;

		POINT m_MouseStartPos;
		int m_iAbsX = 0, m_iAbsY = 0;

		bool aquire();
		bool getState(DIMOUSESTATE2& mouse);

	public:

		void ToString()
		{
			TCHAR str[1024] = L"MOUSE_STATE:\n";
			TCHAR tmp[64] = { 0 };

			wsprintf(tmp, L"rX=%04d, rY=%04d | ", m_Mouse.lX, m_Mouse.lY);
			wcscat_s(str, tmp);
			wsprintf(tmp, L"aX=%04d, aY=%04d | ", m_iAbsX, m_iAbsY);
			wcscat_s(str, tmp);
			wsprintf(tmp, L"Wheel=%04d\n", m_Mouse.lZ);
			wcscat_s(str, tmp);

			for (int i = 0; i < MAX_MOUSE_KEYS; i += 4)
			{
				wsprintf(tmp, L"B%02d: %s | B%02d: %s | ", i + 1, KeyPress((CKT::MouseKeys)i) ? L"TRUE" : L"FALSE", 
															i + 2, KeyPress((CKT::MouseKeys)(i + 1)) ? L"TRUE" : L"FALSE");
				wcscat_s(str, tmp);
				
				wsprintf(tmp, L"B%02d: %s | B%02d: %s\n", i + 3, KeyPress((CKT::MouseKeys)(i + 2)) ? L"TRUE" : L"FALSE",
															i + 4, KeyPress((CKT::MouseKeys)(i + 3)) ? L"TRUE" : L"FALSE");
				wcscat_s(str, tmp);
			}

			wsprintf(tmp, L"in Window: %s\n", isInWindow() ? L"YES" : L"NO");
			wcscat_s(str, tmp);

			OutputDebugString(str);
		}
	};
}

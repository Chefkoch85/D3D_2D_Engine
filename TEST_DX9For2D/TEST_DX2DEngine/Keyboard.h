#pragma once

#include "Input.h"

namespace CKT
{
	class CKeyboard
	{
	public:
		CKeyboard();
		~CKeyboard();

<<<<<<< HEAD
		HRESULT init(HWND hWnd);
=======
		CKT_RESULT init(HWND hWnd);
>>>>>>> origin/master
		void release();

		int update();

		bool KeyDown(int keyCode);
		bool KeyUp(int keyCode);
		bool KeyPress(int keyCode);

	private:
		HWND m_hWnd = NULL;
		LPDIRECTINPUTDEVICE8 m_pDiKeyboard = NULL;

#define MAX_KEYBOARD_KEYS 256
		BYTE m_byKeys[MAX_KEYBOARD_KEYS];
		BYTE m_byOldKeys[MAX_KEYBOARD_KEYS];

		bool aquire();
		bool getState(BYTE keys[256]);
	};
}

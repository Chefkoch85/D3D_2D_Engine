#pragma once

#include <dinput.h>
<<<<<<< HEAD
=======
#include "Engine.h"
>>>>>>> origin/master

namespace CKT
{
	class CInput
	{
	public:
		~CInput();
		static LPDIRECTINPUT8 Instance();

	private:
		CInput();

		static LPDIRECTINPUT8 m_pDInput;
	};
}

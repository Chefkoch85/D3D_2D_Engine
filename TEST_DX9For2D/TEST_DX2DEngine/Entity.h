#pragma once

#include "Sprite.h"
#include "Mouse.h"
#include "Keyboard.h"

namespace CKT
{
	class CEntity : public CKT::CSprite
	{
	public:
		CEntity();
		~CEntity();

<<<<<<< HEAD
		HRESULT move(float fTime);
=======
		CKT_RESULT move(float fTime);
>>>>>>> origin/master

		void setControler(CKeyboard* keyboard = NULL, CMouse* mouse = NULL);

	private:
		CKeyboard* m_pKeyboard = NULL;
		CMouse* m_pMouse = NULL;

		bool m_bUseKeyboard = false, m_bUseMouse = false;
	};
}

#include "Entity.h"

using namespace CKT;

CEntity::CEntity()
{
}


CEntity::~CEntity()
{
}

void CEntity::setControler(CKeyboard* keyboard, CMouse* mouse)
{
	if (keyboard)
	{
		m_pKeyboard = keyboard;
		m_bUseKeyboard = true;
	}

	if (mouse)
	{
		m_pMouse = mouse;
		m_bUseMouse = true;
	}
}

<<<<<<< HEAD
HRESULT CEntity::move(float fTime)
{
	if (m_bUseKeyboard && !m_pKeyboard)
		return E_FAIL;

	if (m_bUseMouse && !m_pMouse)
		return E_FAIL;

	if (!m_bUseKeyboard && !m_bUseMouse)
		return S_OK;
=======
CKT_RESULT CEntity::move(float fTime)
{
	if (m_bUseKeyboard && !m_pKeyboard)
		return CR_USERINPUTKEY;

	if (m_bUseMouse && !m_pMouse)
		return CR_USERINPUTMOUSE;

	if (!m_bUseKeyboard && !m_bUseMouse)
		return CR_OK;
>>>>>>> origin/master

	if (m_pKeyboard->KeyPress(DIK_RIGHT))
		m_fX += 100 * fTime;
	if (m_pKeyboard->KeyPress(DIK_LEFT))
		m_fX -= 100 * fTime;
	if (m_pKeyboard->KeyPress(DIK_DOWN))
		m_fY += 100 * fTime;
	if (m_pKeyboard->KeyPress(DIK_UP))
		m_fY -= 100 * fTime;
	
	if (m_pMouse->WheelForward() > 0)
	{
		if (m_pKeyboard->KeyPress(DIK_RSHIFT))
			m_fScale += 0.5f;
		else
			m_fRotation += 0.3f;
	}

	if (m_pMouse->WheelBackward() > 0)
	{
		if (m_pKeyboard->KeyPress(DIK_RSHIFT))
			m_fScale -= 0.5f;
		else
			m_fRotation -= 0.3f;
	}

<<<<<<< HEAD
	return S_OK;
=======
	return CR_OK;
>>>>>>> origin/master
}
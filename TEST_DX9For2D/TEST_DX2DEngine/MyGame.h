#pragma once

#include "Game.h"
#include "DX2D.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "DXFont.h"
#include "SpriteBatch.h"
#include "TextureManager.h"
#include "MouseCursorManager.h"
#include "Sprite.h"
#include "Entity.h"
#include "FileReader.h"
#include "FileWriter.h"
<<<<<<< HEAD
=======
#include "GameMap.h"
>>>>>>> origin/master

class CMyGame :	public CKT::CGame
{
public:
	CMyGame(HWND hWnd, CKT::CFileReader& iniReader);
	~CMyGame();

<<<<<<< HEAD
	HRESULT CKT::CGame::initSubSystem();
	void CKT::CGame::releaseSubSystem();

	HRESULT CKT::CGame::loadContent();
	void CKT::CGame::unloadContent();


	HRESULT CKT::CGame::move(float fTime);
	HRESULT CKT::CGame::render();

	HRESULT messageProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
=======
	CKT::CKT_RESULT CKT::CGame::initSubSystem();
	void CKT::CGame::releaseSubSystem();

	CKT::CKT_RESULT CKT::CGame::loadContent();
	void CKT::CGame::unloadContent();


	CKT::CKT_RESULT CKT::CGame::move(float fTime);
	CKT::CKT_RESULT CKT::CGame::render();

	LRESULT messageProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
>>>>>>> origin/master

private:
	void UserD3DParams();

	CKT::CDX2D* m_pDX2D = NULL;
	CKT::CKeyboard* m_pKeyboard = NULL;
	CKT::CMouse* m_pMouse = NULL;

	CKT::CSpriteBatch* m_pSprBaUI = NULL;
	CKT::CSpriteBatch* m_pSprBaGame = NULL;

	static const int MAX_DRAWABLE = 10;
	static const int MAX_MOVEABLE = 10;
	CKT::CSprite* m_pDrawable = NULL;
	CKT::CEntity* m_pMoveable = NULL;

	CKT::CFileWriter* m_pFileWriter = NULL;
	CKT::CFileReader* m_pFontReader = NULL;
	CKT::CFileReader* m_pFilesReader = NULL;
	CKT::CFileReader* m_pKeyMapReader = NULL;
<<<<<<< HEAD
=======

	CKT::CGameMap* m_pGameMap = NULL;
>>>>>>> origin/master
};


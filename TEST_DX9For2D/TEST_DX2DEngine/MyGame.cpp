#include "MyGame.h"

using namespace CKT;

CMyGame::CMyGame(HWND hWnd, CFileReader& iniReader) : CKT::CGame(hWnd, iniReader)
{
}

CMyGame::~CMyGame()
{
}

void CMyGame::UserD3DParams()
{
	m_pD3D->D3DParams().PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
}

std::wstring result = L"TEST";
<<<<<<< HEAD
HRESULT CMyGame::initSubSystem()
{
	HRESULT hr = S_OK;

	// init 2D engine
	m_pDX2D = new CDX2D();
	if ((hr = m_pDX2D->init(m_pD3D)) != S_OK)
=======
CKT_RESULT CMyGame::initSubSystem()
{
	CKT_RESULT hr = CR_OK;

	// init 2D engine
	m_pDX2D = new CDX2D();
	if ((hr = m_pDX2D->init(m_pD3D)) != CR_OK)
>>>>>>> origin/master
	{
		return hr;
	}

	// init Input
	m_pKeyboard = new CKeyboard();
<<<<<<< HEAD
	if ((hr = m_pKeyboard->init(m_hWnd)) != S_OK)
=======
	if ((hr = m_pKeyboard->init(m_hWnd)) != CR_OK)
>>>>>>> origin/master
	{
		return hr;
	}

	m_pMouse = new CMouse();
<<<<<<< HEAD
	if ((hr = m_pMouse->init(m_hWnd)) != S_OK)
=======
	if ((hr = m_pMouse->init(m_hWnd)) != CR_OK)
>>>>>>> origin/master
	{
		return hr;
	}

	m_pFontReader = new CFileReader();
<<<<<<< HEAD
	if ((hr = m_pFontReader->init(m_StartupReader.getEntryAsString(L"INI_FONT", L"CONFIG_FILE").c_str())) != S_OK ||
		(hr = m_pFontReader->read()) != S_OK)
	{
		showErrorDialog(L"initSubsystem()", L"CFileReader::init()\nCFileReader::read()", L"Failed to create a filereader \"m_pFontReader\"!");
=======
	if ((hr = m_pFontReader->init(m_StartupReader.getEntryAsString(L"INI_FONT", L"CONFIG_FILE").c_str())) != CR_OK ||
		(hr = m_pFontReader->read()) != CR_OK)
	{
		CEngine::showErrorDialog(L"CMyGame::initSubsystem()", L"CFileReader::init()\nCFileReader::read()", hr, L"Failed to create a filereader \"m_pFontReader\"!");
>>>>>>> origin/master
		return hr;
	}

	m_pFilesReader = new CFileReader();
<<<<<<< HEAD
	if ((hr = m_pFilesReader->init(m_StartupReader.getEntryAsString(L"INI_FILES", L"CONFIG_FILE").c_str())) != S_OK ||
		(hr = m_pFilesReader->read()) != S_OK)
	{
		showErrorDialog(L"initSubsystem()", L"CFileReader::init()\nCFileReader::read()", L"Failed to create a filereader \"m_pFilesReader\"!");
=======
	if ((hr = m_pFilesReader->init(m_StartupReader.getEntryAsString(L"INI_FILES", L"CONFIG_FILE").c_str())) != CR_OK ||
		(hr = m_pFilesReader->read()) != CR_OK)
	{
		CEngine::showErrorDialog(L"CMyGame::initSubsystem()", L"CFileReader::init()\nCFileReader::read()", hr, L"Failed to create a filereader \"m_pFilesReader\"!");
>>>>>>> origin/master
		return hr;
	}

	return hr;
}

void CMyGame::releaseSubSystem()
{
	CKT_RELEASE(m_pDX2D);
	CKT_RELEASE(m_pKeyboard);
	CKT_RELEASE(m_pMouse);
}

int cursor = 0;
<<<<<<< HEAD
HRESULT CMyGame::loadContent()
{
	HRESULT hr = S_OK;
=======
CKT_RESULT CMyGame::loadContent()
{
	CKT_RESULT hr = CR_OK;
>>>>>>> origin/master

	cursor = CMouseManager::loadCursor(m_pFilesReader->getEntryAsString(L"ICON1", L"ICON").c_str(), CColor(1.0f, 0.0f, 1.0f).toColorRef());
	CMouseManager::setCursor(cursor);

	m_pSprBaUI = new CKT::CSpriteBatch();
	hr = m_pSprBaUI->init();
<<<<<<< HEAD
	if (hr != S_OK)
		showErrorDialog(L"loadContent()", L"CSpriteBatch::init()", L"Failed to create a spritebatch \"m_pSprBaUI\"!");

	m_pSprBaGame = new CKT::CSpriteBatch();
	hr = m_pSprBaGame->init();
	if (hr != S_OK)
		showErrorDialog(L"loadContent()", L"CSpriteBatch::init()", L"Failed to create a spritebatch \"m_pSprBaGame\"!");

	CKT::tDXFONT font = CDXFont::instance()->create(m_pFontReader->getEntryAsInt(L"HEIGHT", L"FONT_1"),
													m_pFontReader->getEntryAsInt(L"WIDTH", L"FONT_1"),
													m_pFontReader->getEntryAsInt(L"FLAG", L"FONT_1"),
													m_pFontReader->getEntryAsString(L"FAMILY", L"FONT_1").c_str());
	if (font <= FR_OK)
		showErrorDialog(L"loadContent()", L"CDXFont::create()", L"Failed to create a font!");
=======
	if (hr != CR_OK)
		CEngine::showErrorDialog(L"CMyGame::loadContent()", L"CSpriteBatch::init()", hr, L"Failed to create a spritebatch \"m_pSprBaUI\"!");

	m_pSprBaGame = new CKT::CSpriteBatch();
	hr = m_pSprBaGame->init();
	if (hr != CR_OK)
		CEngine::showErrorDialog(L"CMyGame::loadContent()", L"CSpriteBatch::init()", hr, L"Failed to create a spritebatch \"m_pSprBaGame\"!");

	CKT::tDXFONT font = CDXFont::instance()->create(m_pFontReader->getEntryAsInt(L"HEIGHT", L"FONT_1"),
		m_pFontReader->getEntryAsInt(L"WIDTH", L"FONT_1"),
		m_pFontReader->getEntryAsInt(L"FLAG", L"FONT_1"),
		m_pFontReader->getEntryAsString(L"FAMILY", L"FONT_1").c_str());
	if (font <= FR_OK)
		CEngine::showErrorDialog(L"CMyGame::loadContent()", L"CDXFont::create()", CR_FONTINIT, L"Failed to create a font!");
>>>>>>> origin/master

	CDXFont::instance()->setTarget(m_pSprBaUI);
	CDXFont::instance()->setWriteFont(font);
	CDXFont::instance()->setTextColor(0.2f, 0.9f, 0.2f);

<<<<<<< HEAD
	m_pDrawable = new CSprite[MAX_DRAWABLE];
	m_pDrawable[0].setSpriteBatch(m_pSprBaGame);
	m_pDrawable[0].init(m_pFilesReader->getEntryAsString(L"SPR_WORLD", L"SPRITE").c_str());
=======
	m_pGameMap = new CGameMap();
	if ((hr = hr = m_pGameMap->init(m_pFilesReader->getEntryAsString(L"MAP1", L"MAP"))) != CR_OK)
		CEngine::showErrorDialog(L"CMyGame::loadContent()", L"CGameMap::init()", hr, L"Failed to create game map!");

	m_pGameMap->setSpriteBatch(m_pSprBaGame);
	m_pGameMap->setController(m_pKeyboard, m_pMouse);

	if ((hr = m_pGameMap->createMap()) != CR_OK)
		CEngine::showErrorDialog(L"CMyGame::loadContent()", L"CGameMap::init()", hr, L"Failed to create game map!");

	m_pDrawable = new CSprite[MAX_DRAWABLE];
	//m_pDrawable[0].setSpriteBatch(m_pSprBaGame);
	//m_pDrawable[0].init(m_pFilesReader->getEntryAsString(L"SPR_WORLD", L"SPRITE").c_str());
>>>>>>> origin/master

	m_pMoveable = new CEntity[MAX_MOVEABLE];
	/*m_pMoveable[0].setSpriteBatch(m_pSprBaGame);
	m_pMoveable[0].init(m_pFilesReader->getEntryAsString(L"SPR_PLAYER", L"SPRITE").c_str());
	m_pMoveable[0].setControler(m_pKeyboard, m_pMouse);*/

<<<<<<< HEAD
	return hr;
=======
	return CR_OK;
>>>>>>> origin/master
}

void CMyGame::unloadContent()
{
	CKT::CTextureManager::instance()->releaseAll();
	CKT::CDXFont::instance()->releaseAll();
	CKT_RELEASE(m_pSprBaGame);
	CKT_RELEASE(m_pSprBaUI);
	CKT_RELEASE(m_pKeyboard);
	CKT_RELEASE(m_pMouse);
	CKT_RELEASE(m_pDX2D);
	CKT::CMouseManager::setCursor(CKT::CMouseManager::STD_MOUSECUR_ID);
}

float time = 0.0f;
<<<<<<< HEAD
HRESULT CMyGame::move(float fTime)
=======
int x = 0, y = 0;
float scale = 1.0f;
CKT_RESULT CMyGame::move(float fTime)
>>>>>>> origin/master
{
	if (m_pMouse->isInWindow())
	{
		if (CMouseManager::getCursor() != cursor)
			CMouseManager::setCursor(cursor);
	}

	time = fTime;
	if (m_pKeyboard->update() || m_pMouse->update())
<<<<<<< HEAD
		return E_FAIL;
=======
		return CR_USERINPUT;
>>>>>>> origin/master

	if (m_pKeyboard->KeyUp(DIK_ESCAPE) ||
		(m_pMouse->KeyUp(CKT::MB_Middle) && m_pMouse->isInWindow()))
	{
		OutputDebugString(L"ESCAPE Pressed!\n");
		SendMessage(m_hWnd, WM_CLOSE, 0, 0);
<<<<<<< HEAD
		return S_OK;
	}

	for (int i = 0; i < MAX_MOVEABLE; i++)
		m_pMoveable[i].move(fTime);

	static float x = 10, y = 10, z = 1;
	if (m_pKeyboard->KeyPress(DIK_LEFT))
		x += 100 * fTime;
		else if (m_pKeyboard->KeyPress(DIK_RIGHT))
		x -= 100 * fTime;
		if (m_pKeyboard->KeyPress(DIK_UP))
		y += 100 * fTime;
		else if (m_pKeyboard->KeyPress(DIK_DOWN))
		y -= 100 * fTime;
		if (m_pMouse->WheelForward())
		z -= 10 * fTime;
		else if (m_pMouse->WheelBackward())
		z += 100 * fTime;

		m_pDrawable[0].X() = x;
		m_pDrawable[0].Y() = y;
		m_pDrawable[0].Scale() = z;

	return S_OK;
}

HRESULT CMyGame::render()
{
	m_pSprBaGame->begin(D3DXSPRITE_ALPHABLEND);

	for (int i = 0; i < MAX_DRAWABLE; i++)
		m_pDrawable[i].draw();

	for (int i = 0; i < MAX_MOVEABLE; i++)
		m_pMoveable[i].draw();

	m_pSprBaGame->end();

=======
		return CR_OK;
	}

	if (m_pMouse->KeyDown(CKT::MouseKeys::MB_Left))
	{
		x = m_pMouse->X();
		y = m_pMouse->Y();
	}

	if (m_pMouse->WheelForward() > 0)
	{
		scale += 0.5f;
	}

	if (m_pMouse->WheelBackward() > 0)
	{
		scale -= 0.5f;
	}

	m_pGameMap->move(fTime);
	
	return CR_OK;
}

CKT_RESULT CMyGame::render()
{
	m_pSprBaGame->begin(D3DXSPRITE_ALPHABLEND);

	m_pGameMap->draw();

	m_pSprBaGame->end();


>>>>>>> origin/master
	m_pSprBaUI->begin(D3DXSPRITE_ALPHABLEND);

	CDXFont::instance()->write(4, 0, CKT::FA_Left | CKT::FA_Bottom, L"FPS: %d", getCurrentFPS());
	CDXFont::instance()->write(4, 560, CKT::FA_Left | CKT::FA_Top, L"FTI: %f", time);
<<<<<<< HEAD
	CDXFont::instance()->write(4, 520, CKT::FA_Left | CKT::FA_Top, L"D0S: %f", m_pDrawable[0].Scale());

	m_pSprBaUI->end();

	return S_OK;
}

HRESULT CMyGame::messageProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
=======

	CDXFont::instance()->write(4, 530, CKT::FA_Left | CKT::FA_Top, L"CLICK      : X=%d;Y=%d", x, y);
	CDXFont::instance()->write(4, 510, CKT::FA_Left | CKT::FA_Top, L"CLICK SCALE: X=%d;Y=%d", (int)(x * scale), (int)(y * scale));

	m_pSprBaUI->end();

	return CR_OK;
}

LRESULT CMyGame::messageProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
>>>>>>> origin/master
{
	int result = -1;
	switch (msg)
	{
	case WM_CLOSE:
		result = MessageBox(hWnd, L"Want to quit the Game?", L"Closing", MB_ICONASTERISK | MB_YESNO);

		if (result == IDNO)
			return 1;
		else
			return 0;

	case WM_SETCURSOR:
		//!! Wichtig Nachricht abfangen sonst wird der normale Cursor wieder gesetzt
		return 0;
	}

	CGame::messageProc(hWnd, msg, wParam, lParam);

	return 0;
}

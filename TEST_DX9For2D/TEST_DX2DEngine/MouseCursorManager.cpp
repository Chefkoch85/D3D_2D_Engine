//////////////////////////////////////////////////////////////////////
//  ColorCursor.cpp : implementation of the CColorCursor class.
//  Author		    : Jiju George T (NeST)
//////////////////////////////////////////////////////////////////////

#include "MouseCursorManager.h"

#include <string>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CKT::CMouseCursorManager::tCursorList CKT::CMouseCursorManager::_m_MouseCursorList;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CKT::CMouseCursorManager::CMouseCursorManager()
{
}

CKT::CMouseCursorManager::~CMouseCursorManager()
{

}

//////////////////////////////////////////////////////////////////////
//  CreateCursorFromBitmap 
//  Function to create a cursor from HBITMAP. 
//  Pass bitmaps having standard cursor sizes like 16*16, 32*32...
//////////////////////////////////////////////////////////////////////
HCURSOR CKT::CMouseCursorManager::CreateCursorFromBitmap(HBITMAP hSourceBitmap, COLORREF clrTransparent, DWORD xHotspot, DWORD yHotspot)
{
	HCURSOR hRetCursor = NULL;

	if (xHotspot == 0 || yHotspot == 0)
	{
		//Get the dimensions of the source bitmap
		BITMAP bm;
		::GetObject(hSourceBitmap, sizeof(BITMAP), &bm);
	
		if (xHotspot == 0)
		{
			xHotspot = bm.bmWidth / 2;
		}
		
		if (yHotspot == 0)
		{
			yHotspot = bm.bmHeight / 2;
		}

	}

	do
	{
		if(NULL == hSourceBitmap)
		{
			break;
		}

		//Create the AND and XOR masks for the bitmap
		HBITMAP hAndMask = NULL;
		HBITMAP hXorMask = NULL;
		GetMaskBitmaps(hSourceBitmap,clrTransparent,hAndMask,hXorMask);
		if(NULL == hAndMask || NULL == hXorMask)
		{
			break;
		}

		//Create the cursor using the masks and the hotspot values provided
		ICONINFO iconinfo = {0};
		iconinfo.fIcon		= FALSE;
		iconinfo.xHotspot	= xHotspot;
		iconinfo.yHotspot	= yHotspot;
		iconinfo.hbmMask	= hAndMask;
		iconinfo.hbmColor	= hXorMask;

		hRetCursor = ::CreateIconIndirect(&iconinfo);

	}
	while(0);

	return hRetCursor;
}

HCURSOR CKT::CMouseCursorManager::CreateCursorFromFile(const wchar_t* file, COLORREF clrTransparent, DWORD xHotspot, DWORD yHotspot)
{
	HBITMAP hbmp = (HBITMAP)LoadImage(NULL, file, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTCOLOR | LR_SHARED);

	if (!hbmp)
	{
		OutputDebugString(L"Error : Load Bitmap file, BitmapInfoHeader to big (0x0E: soll=0x28, ist=0x6C)!");
		return 0;
	}

	return CreateCursorFromBitmap(hbmp, clrTransparent, xHotspot, yHotspot);
}


int CKT::CMouseCursorManager::loadCursor(const wchar_t* file, COLORREF clrTransparent, DWORD xHotspot, DWORD yHotspot)
{
	HCURSOR cursorNew = CreateCursorFromFile(file, clrTransparent, xHotspot, yHotspot);

	if (_m_MouseCursorList.size() == 0)
	{
		_m_MouseCursorList.push_back(LoadCursor(NULL, IDC_ARROW));
		_m_MouseCursorList.push_back(LoadCursor(NULL, IDC_WAIT));
	}

	if (cursorNew)
	{
		_m_MouseCursorList.push_back(cursorNew);
		return _m_MouseCursorList.size() + 0xFF;
	}

	return -1;
}

HCURSOR CKT::CMouseCursorManager::getHandleCursor(int cursorID)
{
	if ((unsigned int)cursorID - 0xFF < _m_MouseCursorList.size())
	{
		return _m_MouseCursorList[cursorID - 0xFF];
	}

	return 0;
}
int CKT::CMouseCursorManager::setCursor(int cursorID)
{
	if ((unsigned int)cursorID - 0x100 < _m_MouseCursorList.size())
	{
		SetCursor(_m_MouseCursorList[cursorID - 0x100]);
		return 0;
	}

	return -1;
}
int CKT::CMouseCursorManager::getCursor()
{
	HCURSOR hc = GetCursor();

	for (unsigned int i = 0; i < _m_MouseCursorList.size(); i++)
	{
		if (_m_MouseCursorList[i] == hc)
		{
			return i + 0x100;
		}
	}

	return -1;
}
//////////////////////////////////////////////////////////////////////
//  GetMaskBitmaps
//  Function to AND and XOR masks for a cursor from a HBITMAP. 
//////////////////////////////////////////////////////////////////////
void CKT::CMouseCursorManager::GetMaskBitmaps(HBITMAP hSourceBitmap, COLORREF clrTransparent, HBITMAP &hAndMaskBitmap, HBITMAP &hXorMaskBitmap)
{
	HDC hDC					= ::GetDC(NULL);
	HDC hMainDC				= ::CreateCompatibleDC(hDC); 
	HDC hAndMaskDC			= ::CreateCompatibleDC(hDC); 
	HDC hXorMaskDC			= ::CreateCompatibleDC(hDC); 

	//Get the dimensions of the source bitmap
	BITMAP bm;
	::GetObject(hSourceBitmap,sizeof(BITMAP),&bm);

	
	hAndMaskBitmap	= ::CreateCompatibleBitmap(hDC,bm.bmWidth,bm.bmHeight);
	hXorMaskBitmap	= ::CreateCompatibleBitmap(hDC,bm.bmWidth,bm.bmHeight);

	//Select the bitmaps to DC
	HBITMAP hOldMainBitmap = (HBITMAP)::SelectObject(hMainDC,hSourceBitmap);
	HBITMAP hOldAndMaskBitmap	= (HBITMAP)::SelectObject(hAndMaskDC,hAndMaskBitmap);
	HBITMAP hOldXorMaskBitmap	= (HBITMAP)::SelectObject(hXorMaskDC,hXorMaskBitmap);

	//Scan each pixel of the souce bitmap and create the masks
	COLORREF MainBitPixel;
	for(int x=0;x<bm.bmWidth;++x)
	{
		for(int y=0;y<bm.bmHeight;++y)
		{
			MainBitPixel = ::GetPixel(hMainDC,x,y);
			if(MainBitPixel == clrTransparent)
			{
				::SetPixel(hAndMaskDC,x,y,RGB(255,255,255));
				::SetPixel(hXorMaskDC,x,y,RGB(0,0,0));
			}
			else
			{
				::SetPixel(hAndMaskDC,x,y,RGB(0,0,0));
				::SetPixel(hXorMaskDC,x,y,MainBitPixel);
			}
		}
	}
	
	::SelectObject(hMainDC,hOldMainBitmap);
	::SelectObject(hAndMaskDC,hOldAndMaskBitmap);
	::SelectObject(hXorMaskDC,hOldXorMaskBitmap);

	::DeleteDC(hXorMaskDC);
	::DeleteDC(hAndMaskDC);
	::DeleteDC(hMainDC);

	::ReleaseDC(NULL,hDC);
}

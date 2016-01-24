//////////////////////////////////////////////////////////////////////
// ColorCursor.h	: interface for the CColorCursor class.
// Author		    : Jiju George T (NeST)
// -------------------------------------------------------------------
// Hint				: Cursor werden wie Icons behandelt und geladen
//////////////////////////////////////////////////////////////////////

#pragma once

#include <Windows.h>
#include <vector>

namespace CKT
{
	class CMouseCursorManager
	{
	private:
		typedef std::vector<HCURSOR> tCursorList;

		static tCursorList _m_MouseCursorList;

		CMouseCursorManager();
		virtual ~CMouseCursorManager();
		static void GetMaskBitmaps(HBITMAP hSourceBitmap, COLORREF clrTransparent, HBITMAP &hAndMaskBitmap, HBITMAP &hXorMaskBitmap);

	public:
		static const int STD_MOUSECUR_ID = 256;
		static const int STD_WAITCUR_ID = 257;

		static HCURSOR CreateCursorFromBitmap(HBITMAP hSourceBitmap, COLORREF clrTransparent, DWORD xHotspot, DWORD yHotspot);
		static HCURSOR CreateCursorFromFile(const wchar_t* file, COLORREF clrTransparent, DWORD xHotspot = 0, DWORD yHotspot = 0);

		static int loadCursor(const wchar_t* file, COLORREF clrTransparent, DWORD xHotspot = 0, DWORD yHotspot = 0);
		static HCURSOR getHandleCursor(int cursorID);
		static int setCursor(int cursorID);
		static int getCursor();
	};

	typedef CKT::CMouseCursorManager CMouseManager;

}

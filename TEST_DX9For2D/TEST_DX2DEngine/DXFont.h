#pragma once

#include "Direct3D.h"

#include "Color.h"
#include "SpriteBatch.h"

#include <vector>


namespace CKT
{
	enum FontFlags
	{
		FF_DontCare		= 0x00,
		FF_Bold			= 0x01,
		FF_Italic		= 0x02,
	};

	enum FontAllign
	{
		FA_Left			= DT_LEFT,
		FA_Center		= DT_CENTER,
		FA_Right		= DT_RIGHT,
		FA_Top			= DT_TOP,
		FA_VCenter		= DT_VCENTER,
		FA_Bottom		= DT_BOTTOM,
		FA_NoClip		= DT_NOCLIP,
		FA_RightToLeft	= DT_RTLREADING,
		FA_SingleLine	= DT_SINGLELINE,
	};

	enum FontResult
	{
		FR_OK = 0xFF00,
		FR_LoadErr = 0xF100,
		FR_NotLoaded = 0xF200,
		FR_NoTarget = 0xF300,
		FR_NoFont = 0xF400,
	};

	typedef int tDXFONT;

	class CDXFont
	{
	public:

		static CDXFont* instance();
		~CDXFont();
		
		int create(int height, int width, int flags, const TCHAR* fontFamily);

		int release(int index);

		void releaseAll();

		void setTarget(CSpriteBatch* target);
		int setWriteFont(int font);

		void setTextColor(float r, float g, float b, float a = 1.0f);
		void setTextColor(CColor color);
		
		int CDXFont::write(int x, int y, int allign, TCHAR* fmt, ...);
		int CDXFont::write(int x, int y, int allign, CColor col, TCHAR* fmt, ...);
		int write(TCHAR* text, int x, int y, int allign, CColor col, int font, CSpriteBatch* target);

	private:
		struct SFont
		{
			bool bIsUsed;
			int iFontHeight;
			LPD3DXFONT pFont;
		};

		static CDXFont* m_pInstance;

		int m_iFirstFreePlace = -1;
		std::vector<SFont> m_FontList;

		CColor m_TextColor = CColor(0, 0, 0);
		int m_iWriteFont = 0;
		CSpriteBatch* m_pTargetSurface = NULL;

		CDXFont();
		bool checkIndex(int& index);
	};

}

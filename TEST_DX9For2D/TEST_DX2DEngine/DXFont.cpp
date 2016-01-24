#include "DXFont.h"

#include<cstdarg>

using namespace CKT;

CDXFont* CDXFont::m_pInstance = NULL;

CDXFont::CDXFont()
{

}

CDXFont* CDXFont::instance()
{
	if (m_pInstance)
		return m_pInstance;

	m_pInstance = new CDXFont();
	return m_pInstance;
}

CDXFont::~CDXFont()
{
	releaseAll();
}

int CDXFont::create(int height, int width, int flags, const TCHAR* fontFamily)
{
	int iWeight = (flags & FF_Bold) ? FW_BOLD : FW_DONTCARE;
	bool bItalic = (flags & FF_Italic);
	
	SFont font;

	HRESULT hr = D3DXCreateFont(CDirect3D::instance()->getDevice(), 
								height, 
								width, 
								iWeight, 
								0, 
								bItalic,
								DEFAULT_CHARSET,
								OUT_DEFAULT_PRECIS,
								DEFAULT_QUALITY,
								DEFAULT_PITCH | FF_DONTCARE,
								fontFamily,
								&font.pFont);

	if (hr != S_OK)
		return FR_LoadErr;

	font.bIsUsed = true;
	font.iFontHeight = height;

	if (m_iFirstFreePlace >= 0)
	{
		m_FontList[m_iFirstFreePlace] = font;
	}
	else
	{
		m_FontList.push_back(font);
	}

	return m_FontList.size() + FR_OK;
}

int CDXFont::release(int index)
{
	if (checkIndex(index))
	{
		m_FontList[index].pFont->Release();
		m_FontList[index].pFont = NULL;
		m_FontList[index].bIsUsed = false;
		m_iFirstFreePlace = index;

		return FR_OK;
	}
	else
		return FR_NotLoaded;
}
void CDXFont::releaseAll()
{
	for each (SFont font in m_FontList)
	{
		font.bIsUsed = false;
		font.pFont->Release();
		font.pFont = NULL;
	}

	m_FontList.clear();
	m_iFirstFreePlace = -1;
}

bool CDXFont::checkIndex(int& index)
{
	index = index - (FR_OK + 1);

	if (index < 0 || (unsigned int)index >= m_FontList.size())
		return false;

	if (!m_FontList[index].bIsUsed)
		return false;

	return true;
}

void CDXFont::setTextColor(float r, float g, float b, float a)
{
	m_TextColor = CColor(r, g, b, a);
}
void CDXFont::setTextColor(CColor color)
{
	m_TextColor = color;
}

int CDXFont::setWriteFont(int font)
{
	int paraFont = font;
	if (checkIndex(font))
	{
		m_iWriteFont = paraFont;
		return FR_OK;
	}

	return FR_NotLoaded;
}
void CDXFont::setTarget(CSpriteBatch* target)
{
	m_pTargetSurface = target;
}


int CDXFont::write(int x, int y, int allign, TCHAR* fmt ...)
{
	va_list varList;
	TCHAR buffer[1024] = { 0 };

	va_start(varList, fmt);
	vswprintf_s(buffer, fmt, varList);
	va_end(varList);

	return write(buffer, x, y, allign, m_TextColor, m_iWriteFont, m_pTargetSurface);
}
int CDXFont::write(int x, int y, int allign, CColor col, TCHAR* fmt, ...)
{
	va_list varList;
	TCHAR buffer[1024] = { 0 };

	va_start(varList, fmt);
	vswprintf_s(buffer, fmt, varList);
	va_end(varList);

	return write(buffer, x, y, allign, col, m_iWriteFont, m_pTargetSurface);
}
int CDXFont::write(TCHAR* text, int x, int y, int allign, CColor col, int font, CSpriteBatch* target)
{
	if (checkIndex(font))
	{
		int r = 0;
		RECT pos;
		pos.left = x;
		pos.top = y;
		//pos.bottom = pos.top + m_FontList[font].iFontHeight;
		pos.bottom = CDirect3D::instance()->Height();
		pos.right = CDirect3D::instance()->Width();
		if (target)
		{
			target->setTransform(CSpriteBatch::identity());
			m_FontList[font].pFont->DrawText(target->getD3DXSprite(), text, -1, &pos, allign, col.toD3DColor());
		}
		else if (m_pTargetSurface)
		{
			m_FontList[font].pFont->DrawText(m_pTargetSurface->getD3DXSprite(), text, -1, &pos, allign, col.toD3DColor());
		}
		else
			return FR_NoTarget;

		return FR_OK;
	}
	else
		return FR_NotLoaded;
}


#include "Color.h"

using namespace CKT;

CColor::CColor(float r, float g, float b, float a)
{
	m_fRed = r;
	m_fGreen = g;
	m_fBlue = b;
	m_fAlpha = a;

	m_fAlpha = m_fAlpha < 0 ? 0 : m_fAlpha;
	m_fAlpha = m_fAlpha > 1.0f ? 1.0f : m_fAlpha;
	m_fRed = m_fRed < 0 ? 0 : m_fRed;
	m_fRed = m_fRed > 1.0f ? 1.0f : m_fRed;
	m_fGreen = m_fGreen < 0 ? 0 : m_fGreen;
	m_fGreen = m_fGreen > 1.0f ? 1.0f : m_fGreen;
	m_fBlue = m_fBlue < 0 ? 0 : m_fBlue;
	m_fBlue = m_fBlue > 1.0f ? 1.0f : m_fBlue;
}
CColor::CColor(D3DCOLOR col)
{
	int r, g, b, a;

	a = (col & 0xFF000000) >> 24;
	r = (col & 0x00FF0000) >> 16;
	g = (col & 0x0000FF00) >> 8;
	b = (col & 0x000000FF);

	m_fAlpha = a / 255.0f;
	m_fRed = r / 255.0f;
	m_fGreen = g / 255.0f;
	m_fBlue = b / 255.0f;

	m_fAlpha = m_fAlpha < 0 ? 0 : m_fAlpha;
	m_fAlpha = m_fAlpha > 1.0f ? 1.0f : m_fAlpha;
	m_fRed = m_fRed < 0 ? 0 : m_fRed;
	m_fRed = m_fRed > 1.0f ? 1.0f : m_fRed;
	m_fGreen = m_fGreen < 0 ? 0 : m_fGreen;
	m_fGreen = m_fGreen > 1.0f ? 1.0f : m_fGreen;
	m_fBlue = m_fBlue < 0 ? 0 : m_fBlue;
	m_fBlue = m_fBlue > 1.0f ? 1.0f : m_fBlue;
}
CColor::~CColor()
{

}

D3DCOLOR CColor::toD3DColor()
{
	return D3DCOLOR_ARGB((int)(255 * m_fAlpha), (int)(255 * m_fRed), (int)(255 * m_fGreen), (int)(255 * m_fBlue));
}
COLORREF CColor::toColorRef()
{
	return RGB((int)(255 * m_fRed), (int)(255 * m_fGreen), (int)(255 * m_fBlue));
}

CColor CColor::add(CColor col)
{
	m_fAlpha += col.m_fAlpha;
	m_fRed += col.m_fRed;
	m_fGreen += col.m_fGreen;
	m_fBlue += col.m_fBlue;

	m_fAlpha = m_fAlpha < 0 ? 0 : m_fAlpha;
	m_fAlpha = m_fAlpha > 1.0f ? 1.0f : m_fAlpha;
	m_fRed = m_fRed < 0 ? 0 : m_fRed;
	m_fRed = m_fRed > 1.0f ? 1.0f : m_fRed;
	m_fGreen = m_fGreen < 0 ? 0 : m_fGreen;
	m_fGreen = m_fGreen > 1.0f ? 1.0f : m_fGreen;
	m_fBlue = m_fBlue < 0 ? 0 : m_fBlue;
	m_fBlue = m_fBlue > 1.0f ? 1.0f : m_fBlue;

	return *this;
}
CColor CColor::complement()
{
	return CColor(1.0f - m_fRed, 1.0f - m_fGreen, 1.0f - m_fBlue);
}
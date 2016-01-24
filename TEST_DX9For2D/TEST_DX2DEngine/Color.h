#pragma once

#include <d3d9.h>

namespace CKT
{
	class CColor
	{
	public:
		CColor(float r, float g, float b, float a = 1.0f);
		CColor(D3DCOLOR col);
		~CColor();

		D3DCOLOR toD3DColor();
		COLORREF toColorRef();

		CColor add(CColor col);
		CColor complement();

		float Red() { return m_fRed; }
		float Green() { return m_fGreen; }
		float Blue() { return m_fBlue; }
		float Alpha() { return m_fAlpha; }

		int RedInt() { return (int)(255 * m_fRed); }
		int GreenInt() { return (int)(255 * m_fGreen); }
		int BlueInt() { return (int)(255 * m_fBlue); }
		int AlphaInt() { return (int)(255 * m_fAlpha); }

	private:
		float m_fRed = 0.0f;
		float m_fGreen = 0.0f;
		float m_fBlue = 0.0f;
		float m_fAlpha = 0.0f;
	};
}

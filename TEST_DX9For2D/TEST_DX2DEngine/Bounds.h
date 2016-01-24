#pragma once

namespace CKT
{
	class CBounds
	{
	public:
		CBounds();
		CBounds(int x, int y, int width, int height);
		~CBounds();

		int& X() { return m_iX; }
		int& Y() { return m_iY; }

		int& W() { return m_iWidth; }
		int& H() { return m_iHeight; }

	private:
		int m_iX = 0, m_iY = 0;
		int m_iWidth = 0, m_iHeight = 0;
	};
}

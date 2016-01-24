#include "Bounds.h"

using namespace CKT;

CBounds::CBounds()
{
}

CKT::CBounds::CBounds(int x, int y, int width, int height)
{
	m_iX = x;
	m_iY = y;
	m_iWidth = width;
	m_iHeight = height;
}


CBounds::~CBounds()
{
}

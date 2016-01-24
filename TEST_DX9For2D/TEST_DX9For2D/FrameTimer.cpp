#include "FrameTimer.h"


CFrameTimer::CFrameTimer()
{
}


CFrameTimer::~CFrameTimer()
{
}

void CFrameTimer::Initialize()
{
	m_curFrameTimeMS = 1;
	m_curFrameTimeS = 0.001f;
}

void CFrameTimer::FrameBeginn()
{
	m_startFrameTime = timeGetTime();
}

int CFrameTimer::FrameEnd()
{
	m_curFrameTimeMS = timeGetTime() - m_startFrameTime;

	m_curFrameTimeS = m_curFrameTimeMS / 1000.0f;
	if (m_curFrameTimeS == 0.0f)
		m_curFrameTimeS = 0.000001f;

	return m_curFrameTimeMS;
}

float CFrameTimer::GetTimeS()
{
	return m_curFrameTimeS;
}
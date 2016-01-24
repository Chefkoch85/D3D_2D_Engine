#include "FpsCounter.h"


CFpsCounter::CFpsCounter()
{
}

CFpsCounter::CFpsCounter(const CFpsCounter& other)
{
}

CFpsCounter::~CFpsCounter()
{
}


void CFpsCounter::Initialize()
{
	m_fps = 0;
	m_count = 0;
	m_startTime = timeGetTime();
	memset(m_aFpsList, 0, sizeof(int) * MAX_FPS_COUNT);
	return;
}

void CFpsCounter::Frame()
{
	m_count++;

	if (timeGetTime() >= (m_startTime + 1000))
	{
		m_fps = m_count;
		m_count = 0;

		m_aFpsList[m_FpsListIndex++] = m_fps;
		m_FpsListIndex %= MAX_FPS_COUNT;

		m_startTime = timeGetTime();
	}
}

int CFpsCounter::getCurFps()
{
	return m_fps;
}

int CFpsCounter::getAverageFps()
{
	int sum = 0;
	int i = 0;
	for (; i < MAX_FPS_COUNT; i++)
	{
		if (m_aFpsList[i] == 0)
			break;

		sum += m_aFpsList[i];
	}

	if (i > 0)
		return sum / i;

	return -1;
}
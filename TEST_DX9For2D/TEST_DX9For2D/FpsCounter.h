#pragma once

#pragma comment(lib, "winmm.lib")

#include <windows.h>
#include <mmsystem.h>

class CFpsCounter
{
public:
	CFpsCounter();
	CFpsCounter(const CFpsCounter&);
	~CFpsCounter();

	void Initialize();
	void Frame();
	int getCurFps();
	int getAverageFps();

private:
#define MAX_FPS_COUNT 100

	int m_fps, m_count;
	int m_aFpsList[MAX_FPS_COUNT], m_FpsListIndex = 0;
	unsigned long m_startTime;
};

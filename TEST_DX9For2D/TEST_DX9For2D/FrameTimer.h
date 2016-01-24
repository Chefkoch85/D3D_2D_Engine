#pragma once

#pragma comment(lib, "winmm.lib")

#include <windows.h>
#include <mmsystem.h>

class CFrameTimer
{
public:
	CFrameTimer();
	~CFrameTimer();

	void Initialize();

	void FrameBeginn();
	int FrameEnd();
	int GetTimeMS();
	float GetTimeS();

private:
	int m_curFrameTimeMS;
	float m_curFrameTimeS;
	int m_startFrameTime;
};


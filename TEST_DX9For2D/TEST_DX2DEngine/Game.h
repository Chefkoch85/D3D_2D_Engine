#pragma once

#include "Direct3D.h"
#include "Engine.h"
#include "FileReader.h"

namespace CKT
{
	class CGame
	{
	public:
		CGame(HWND hWnd, CFileReader& iniReader);
		virtual ~CGame();

<<<<<<< HEAD
		HRESULT init();
=======
		CKT_RESULT init();
>>>>>>> origin/master
		void release();

		void activate(bool activ = true);

<<<<<<< HEAD
		HRESULT run();
		virtual HRESULT move(float fTime) = 0;
		virtual HRESULT render() = 0;


		virtual LRESULT GameLoop();
		virtual LRESULT messageProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

		bool hasIniReader() { return m_bHasFileReader; }

		void showErrorDialog(STRING errCaption, STRING errClass, STRING errDesc);

=======
		CKT_RESULT run();
		virtual CKT_RESULT move(float fTime) = 0;
		virtual CKT_RESULT render() = 0;


		virtual CKT_RESULT GameLoop();
		virtual LRESULT messageProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

		bool hasIniReader() { return m_bHasFileReader; }
		
>>>>>>> origin/master
	protected:
		HWND m_hWnd = NULL;
		CDirect3D* m_pD3D;
		D3DCOLOR m_ClearColor = D3DCOLOR_XRGB(0, 0, 255);
		CFileReader& m_StartupReader;

		virtual void UserD3DParams() {};
<<<<<<< HEAD
		virtual HRESULT initSubSystem() = 0;
		virtual HRESULT loadContent() = 0;
=======
		virtual CKT_RESULT initSubSystem() = 0;
		virtual CKT_RESULT loadContent() = 0;
>>>>>>> origin/master
		virtual void unloadContent() = 0;
		virtual void releaseSubSystem() = 0;

		CFileReader& getIniFile() { return m_StartupReader; }
		int getAverageFPS() { return m_FpsCounter.getAverageFps(); }
		int getCurrentFPS() { return m_FpsCounter.getCurFps(); }

	private:
<<<<<<< HEAD
		virtual HRESULT initD3D();
=======
		virtual CKT_RESULT initD3D();
>>>>>>> origin/master

		CFrameTimer m_FrameTimer;
		CFpsCounter m_FpsCounter;
		bool m_bIsActiv = false;
		bool m_bHasFileReader = false;

	};


}
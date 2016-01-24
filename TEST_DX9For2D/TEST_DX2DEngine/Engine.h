#pragma once

#include <Windows.h>
#include <string>


namespace CKT
{
#ifdef _UNICODE
	typedef std::wstring STRING;
	#define	toString(val) std::to_wstring(val)
	#define toFloat(str) std::wcstof(str)
<<<<<<< HEAD
	#define toInt(str) (int)std::wcstol(str)
=======
	#define toInt(str) (int)std::wcstol(str, NULL, 10)
>>>>>>> origin/master
#elif
	typedef std::string STRING;
	#define toString(val) std::to_string(val)
	#define toFloat(str) std::stof(str)
	#define toInt(str) (int)std::stol(str)
#endif

<<<<<<< HEAD
=======
	enum CKT_RESULT
	{
		CR_OK,
		CR_NOTIMPLEMENTED,
		CR_FILENOTFOUND,
		CR_FILEFORMAT,
		CR_D3DINIT,
		CR_D3DRUN,
		CR_D3D2DINIT,
		CR_USERINPUT,
		CR_USERINPUTKEYINIT,
		CR_USERINPUTMOUSEINIT,
		CR_USERINPUTKEY,
		CR_USERINPUTMOUSE,
		CR_DRAW,
		CR_DRAWBEGINN,
		CR_DRAWEND,
		CR_SPRITEBATCH,
		CR_INDEXNOTFOUNT,
		CR_FONTINIT,
		SIZE_OF_ENUM
	};

	static const TCHAR* CKT_RESULT_NAMES[SIZE_OF_ENUM] = {
		L"CR_OK", L"CR_NOTIMPLEMENTED", L"CR_FILENOTFOUND", L"CR_FILEFORMAT",
		L"CR_D3DINIT", L"CR_D3DRUN", L"CR_D3D2DINIT", 
		L"CR_USERINPUT", L"CR_USERINPUTKEYINIT", L"CR_USERINPUTMOUSEINIT", L"CR_USERINPUTKEY", L"CR_USERINPUTMOUSE",
		L"CR_DRAW", L"CR_DRAWBEGINN", L"CR_DRAWEND", L"CR_SPRITEBATCH", 
		L"CR_INDEXNOTFOUNT", L"CR_FONTINIT"
	};

	STRING ResultToString(CKT_RESULT result);


>>>>>>> origin/master
	class CFileReader;

	class CEngine
	{
	public:
		static CFileReader DUMMY_INIREADER;

		static const TCHAR* WINDOW_CLASS_NAME;
<<<<<<< HEAD
=======

		static void setErrorFile(STRING errorFile);
		static void showErrorDialog(STRING errCaption, STRING errClass, CKT_RESULT result, STRING errDesc);

	private:
		static STRING m_sErrorFile;

>>>>>>> origin/master
	};

}

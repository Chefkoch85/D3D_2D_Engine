#pragma once

#include "Direct3D.h"

#include "Engine.h"
#include "FileReader.h"
#include <map>

namespace CKT
{
	class CFileWriter
	{
	public:
		CFileWriter();
		~CFileWriter();

<<<<<<< HEAD
		HRESULT init(TCHAR* file, CFileTypedef::CAPTION_MAP& entryList);
		HRESULT init(TCHAR* file, CFileTypedef::CAPTION_MAP& entryList, bool newfile);
		void release();

		HRESULT write(STRING caption, STRING entry, STRING value);
		HRESULT write(STRING caption, STRING entry, int value);
		HRESULT write(STRING caption, STRING entry, float value);
		HRESULT write(STRING caption, STRING entry, bool value);

		HRESULT flush();
	private:
		HRESULT init(TCHAR* file, bool newFile);
=======
		CKT_RESULT init(TCHAR* file, CFileTypedef::CAPTION_MAP& entryList);
		CKT_RESULT init(TCHAR* file, CFileTypedef::CAPTION_MAP& entryList, bool newfile);
		void release();

		CKT_RESULT write(STRING caption, STRING entry, STRING value);
		CKT_RESULT write(STRING caption, STRING entry, int value);
		CKT_RESULT write(STRING caption, STRING entry, float value);
		CKT_RESULT write(STRING caption, STRING entry, bool value);

		CKT_RESULT flush();
	private:
		CKT_RESULT init(TCHAR* file, bool newFile);
>>>>>>> origin/master

		CFileTypedef::CAPTION_MAP _DUMMYLIST;

		CFileTypedef::CAPTION_MAP& m_EntryList;
		CFileTypedef::CAPTION_MAP m_NewEntryList;

		STRING m_sFilename;

		int m_iChangedEntrys = 0;
	};
}

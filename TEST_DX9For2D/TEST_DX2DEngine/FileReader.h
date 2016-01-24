#pragma once

#include "Direct3D.h"
#include "FileTypedef.h"
<<<<<<< HEAD
=======
#include "Engine.h"
>>>>>>> origin/master

namespace CKT
{
	class CFileReader
	{
	public:
		CFileReader();
		~CFileReader();

<<<<<<< HEAD
		HRESULT init(const TCHAR* file);
		void release();

		HRESULT read();
=======
		CKT_RESULT init(const TCHAR* file);
		void release();

		CKT_RESULT read();
>>>>>>> origin/master
		bool hasRead() { return m_bReadAndParseDone; }

		STRING getEntryAsString(STRING entry, STRING caption);
		int getEntryAsInt(STRING entry, STRING caption);
		float getEntryAsFloat(STRING entry, STRING caption);
		bool getEntryAsBool(STRING entry, STRING caption);

		CFileTypedef::CAPTION_MAP getEntryList() { return m_EntryList; }

	private:
		CFileTypedef::CAPTION_MAP m_EntryList;

		STRING m_sFilename;

		bool m_bReadAndParseDone = false;

	};
}

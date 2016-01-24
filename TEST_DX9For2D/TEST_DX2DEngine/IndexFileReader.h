#pragma once

#include "Engine.h"
#include <vector>

namespace CKT
{
	class CIndexFileReader
	{
	public:
		CIndexFileReader();
		~CIndexFileReader();

		CKT_RESULT init(const TCHAR* file);
		void release();

		CKT_RESULT read();

		STRING getEntryAsString(int index);
		int getEntryAsInt(STRING entry, STRING caption);
		float getEntryAsFloat(STRING entry, STRING caption);
		bool getEntryAsBool(STRING entry, STRING caption);

		std::vector<STRING> getData() { return m_DataList; }

	private:
		std::vector<STRING> m_DataList;

		STRING m_sFilename;
	};
}

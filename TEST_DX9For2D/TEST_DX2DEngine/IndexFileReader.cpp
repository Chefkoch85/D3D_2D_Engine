#include "IndexFileReader.h"

#include <fstream>

using namespace CKT;
using namespace std;

CIndexFileReader::CIndexFileReader()
{
}


CIndexFileReader::~CIndexFileReader()
{
	release();
}

CKT_RESULT CKT::CIndexFileReader::init(const TCHAR * file)
{
	wfstream FileStream;
	FileStream.open(file, ios::in);

	if (!FileStream.is_open())
	{
		CEngine::setErrorFile(file);
		return CR_FILENOTFOUND;
	}

	FileStream.close();

	m_sFilename = STRING(file);
	return CR_OK;
}

void CKT::CIndexFileReader::release()
{
	m_DataList.clear();
}

CKT_RESULT CKT::CIndexFileReader::read()
{
	wfstream File;
	File.open(m_sFilename, ios::in);

	if (!File.is_open())
	{
		CEngine::setErrorFile(m_sFilename);
		return CR_FILENOTFOUND;
	}

	while (!File.eof())
	{
		TCHAR caLine[256] = { 0 };
		File.getline(caLine, 256);
		STRING sLine = STRING(caLine);
		if (sLine == L"" || (sLine[0] == '/' && sLine[1] == '/'))
			continue;

		if (sLine == L"[END]")
			break;

		if (File.eof())
		{
			CEngine::setErrorFile(m_sFilename);
			return CR_FILEFORMAT;
		}

		m_DataList.push_back(sLine);
	}

	File.close();
	return CR_OK;
}

STRING CKT::CIndexFileReader::getEntryAsString(int index)
{
	if (index >= 0 && index < m_DataList.size())
		return m_DataList[index];

	return STRING();
}
